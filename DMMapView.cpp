// DMMapView.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMMapView.h"
#include "DMPlaceEdit.h"
#include "Sphere.h"
#include "ZoneEdit.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMMapView

IMPLEMENT_DYNCREATE(CDMMapView, CScrollView)

CDMMapView::CDMMapView():
m_zoneeditor(IDS_ZONES)
{
	m_bGrid = TRUE;
	m_layer = NULL;
	m_size = 10;
	m_layer_id  = 0;
	m_bDragging = FALSE;
}

CDMMapView::~CDMMapView()
{
	delete m_layer;
}

BEGIN_MESSAGE_MAP(CDMMapView, CScrollView)
	//{{AFX_MSG_MAP(CDMMapView)
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_ZOOMOUT, OnZoomout)
	ON_COMMAND(IDM_ZOOMIN, OnZoomin)
	ON_COMMAND(IDM_VIEWPLACE, OnView)
	ON_COMMAND(IDM_DELETEPLACE, OnDelete)
	ON_COMMAND(IDM_MOVEPLACE, OnMove)
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDM_SETZONE, OnSetzone)
	ON_COMMAND(IDM_NEWZONE, OnNewzone)
	ON_COMMAND(IDM_DELZONE, OnDelzone)
	ON_COMMAND(IDM_ZONEEDITR, OnZoneEditR)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDM_GRIDONOFF, OnGridOnOff)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMMapView drawing

void CDMMapView::OnDraw(CDC* pDC)
{
	static CPoint last_pnt;
	CDMJournalDoc* pDoc = GetDocument();

	if(m_layer)
	{
		CRect r; 
		pDC->GetClipBox(&r); 
		pDC->LPtoDP(&r); 

		CPoint pnt = GetScrollPosition();

		r.left += pnt.x;
		r.top += pnt.y;
		r.right += pnt.x;
		r.bottom += pnt.y;

		m_layer->DrawLayer(pDC->m_hDC, r.left, r.top, r, m_size, pDoc->m_journal.GetLayer(m_layer_id), pDoc->m_journal.GetZones());
		
		last_pnt = pnt;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDMMapView diagnostics

#ifdef _DEBUG
void CDMMapView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDMMapView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDMJournalDoc* CDMMapView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMJournalDoc)));
	return (CDMJournalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMMapView message handlers

void CDMMapView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	SetRedraw(FALSE);
	CDMJournalDoc* pDoc = GetDocument();
	int w, h;
	pDoc->m_journal.GetMapSize(w, h);
	
	delete m_layer;
	m_layer = new CMapLayer(w, h);	
	m_layer->m_bGrid = m_bGrid;
	
	int dw = m_layer->GetWidth(m_size);
	int dh = m_layer->GetHeight(m_size);
	SetScrollSizes(MM_TEXT, CSize(dw, dh), CSize(30, 16), CSize(15, 8));
	RECT r;
	GetClientRect(&r);
	ScrollToPosition(CPoint((dw - r.right)/2, (dh - r.bottom)/2));	
	Invalidate();
	SetRedraw(TRUE);
}

void CDMMapView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bDragging)
	{
		ReleaseCapture ();
		m_bDragging = FALSE;
		m_pDragImage->DragLeave (GetDesktopWindow ());
		m_pDragImage->EndDrag ();
		delete m_pDragImage;
		m_pDragImage = 0;

		CPoint pt(point);           //get our current mouse coordinates
		ClientToScreen(&pt);        //convert to screen coordinates
		m_pDropWnd = WindowFromPoint (pt);
		ASSERT(m_pDropWnd); //make sure we have a window


		if(m_pDropWnd->m_hWnd == m_hWnd)
		{
			// Convert from screen coordinates to drop target client coordinates
			ScreenToClient(&pt);
			SendMessage(WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));

			MovePlace(m_nDragIndex);			
		}
		else
		{
			CDMJournalDoc* pDoc = GetDocument();
			pDoc->m_journal.GetLayer(m_layer_id)->Delete(m_nDragIndex);
			pDoc->m_journal.GetNewPlaces()->Sort();
			pDoc->UpdateAllViews(this);
			GetDocument()->SetModifiedFlag();
		}
		Invalidate();
	}
}

BOOL CDMMapView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE; //CScrollView::OnEraseBkgnd(pDC);
}

void CDMMapView::OnMouseMove(UINT nFlags, CPoint point) 
{	
	static CPoint prev_pnt(0,0);	
	if (m_bDragging)
	{
		CPoint pt(point);           //get our current mouse coordinates
		ClientToScreen(&pt);        //convert to screen coordinates

		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT(pDropWnd); //make sure we have a window

		m_pDropWnd = pDropWnd;
		m_pDragImage->DragMove(pt);
		m_pDragImage->DragShowNolock(true);
		return;
	}	

	CDMJournalDoc* pDoc = GetDocument();
	IMapLayer *ml = pDoc->m_journal.GetLayer(m_layer_id);

	if(nFlags&MK_MBUTTON || (ml->GetPlaces()->GetSelectedID() == -1 && nFlags&MK_LBUTTON && !m_zoneeditor.m_hWnd))
	{
		ScrollToPosition(GetScrollPosition() + (prev_pnt - point));
		prev_pnt = point;
		return;
	}


	RECT r;
	GetClientRect(&r);	
	CPoint pnt = GetScrollPosition();

	r.left += pnt.x;
	r.top += pnt.y;
	r.right += pnt.x;
	r.bottom += pnt.y;
	
	CPoint cur, ne;
	CPoint last_pnt;

	m_layer->GetCurPoint(cur);
	last_pnt = cur;

	m_layer->Map2Disp(last_pnt, m_size);
	ne = GetScrollPosition();
	last_pnt -= ne;


	m_layer->SelectCell(r, m_size, point.x, point.y);
	m_layer->GetCurPoint(ne);

	if(ne != cur)
	{		
		m_ToolTip.Activate(FALSE);
		InvalidateRect(CRect(last_pnt.x - 4*m_size, last_pnt.y - 4*m_size, last_pnt.x + 4*m_size, last_pnt.y + 4*m_size), FALSE);		
		
		if(m_zoneeditor.m_hWnd)
		{
			if(nFlags&MK_LBUTTON)
			{
				OnLButtonDown(nFlags, point);
				return;
			}
			if(nFlags&MK_RBUTTON)
			{
				OnRButtonDown(nFlags, point);
				return;
			}
		}

		CString str;
		
		IPlace *p = ml->GetPlace(ne.x, ne.y);
		IPlace *z = pDoc->m_journal.GetZones()->GetPlace(m_layer_id, ne.x, ne.y);

		if(!m_zoneeditor.m_hWnd)
			pDoc->m_journal.GetZones()->Select(m_layer_id, ne.x, ne.y);
		CString csZone;
		if(z)
		{
			csZone.LoadString(IDS_ZONE);
			csZone += _T(" - ") + z->GetTitleCS(); 
		}
		if(!p)
		{
			ml->GetPlaces()->Select(-1);
			str.Format(_T("%s (%d, %d)"), csZone, ne.x, ne.y);
		}
		else
		{
			ml->GetPlaces()->Select(p->GetID());
			str.Format(_T("%s: %s (%d, %d)"), p->GetTitleCS(), csZone, ne.x, ne.y);			
		}

		InvalidateRect(CRect(point.x - 2*m_size, point.y - 2*m_size, point.x + 2*m_size, point.y + 2*m_size), FALSE);

		CFrameWnd* frame = GetParentFrame();
		if(frame)
			frame->SetMessageText(str);
	}
	else
	{
		m_ToolTip.Activate(TRUE);
	}


	if(nFlags&MK_LBUTTON)
		BeginDrag();

	prev_pnt = point;

	CScrollView::OnMouseMove(nFlags, point);
}

void CDMMapView::AddPlace(int id)
{
	CDMJournalDoc* pDoc = GetDocument();
	CPoint cur;
	m_layer->GetCurPoint(cur);
	pDoc->m_journal.GetLayer(m_layer_id)->Add(id, cur.x, cur.y);
	pDoc->m_journal.GetLayer(m_layer_id)->GetPlaces()->Select(id);
	InvalidateRect(0, FALSE);
}

BOOL CDMMapView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	BOOL rez = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	if (m_ToolTip.Create(this, TTS_ALWAYSTIP) && m_ToolTip.AddTool(this, LPSTR_TEXTCALLBACK))
    {
        m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, SHRT_MAX);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_AUTOPOP, SHRT_MAX);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_INITIAL, 200);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_RESHOW, 200);
    }

	return rez;
}

void CDMMapView::OnZoomout() 
{
	if(m_size > 4)
		Zoom(m_size - 2);
}

void CDMMapView::OnZoomin() 
{
	if(m_size < 50)
		Zoom(m_size + 2);
}

void CDMMapView::Zoom(int new_size)
{

	CPoint pnt = GetScrollPosition();
	CSize  sz  = GetTotalSize();
	CRect rc;
	GetClientRect(&rc);

	double dx = double(pnt.x + rc.right/2) / double(sz.cx);
	double dy = double(pnt.y + rc.bottom/2) / double(sz.cy);

	m_size = new_size;
	
	int dw = m_layer->GetWidth(m_size);
	int dh = m_layer->GetHeight(m_size);
	
	SetRedraw(FALSE);
	SetScrollSizes(MM_TEXT, CSize(dw, dh), CSize(30, 16), CSize(15, 8));
	
	pnt.x = dw * dx - rc.right/2;
	pnt.y = dh * dy - rc.bottom/2;
	ScrollToPosition(pnt);
	SetRedraw(TRUE);
	Invalidate(FALSE);
}

BOOL CDMMapView::OnMouseWheel(UINT fFlags, short zDelta, CPoint point)
{
	//return DoMouseWheel(fFlags, zDelta, point);
	if(zDelta > 0)
		OnZoomin();
	else
		OnZoomout();
	return TRUE;
}

BOOL CDMMapView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll) 
{
	BOOL rez = CScrollView::OnScrollBy(sizeScroll, bDoScroll);

	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	SendMessage(WM_MOUSEMOVE, 0, MAKELPARAM(point.x, point.y));

	return rez;
}

void CDMMapView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(m_zoneeditor.m_hWnd)
	{
		CDMJournalDoc* pDoc = GetDocument();
		CPoint cur;
		m_layer->GetCurPoint(cur);
		pDoc->m_journal.GetZones()->Add(-1, m_layer_id, cur.x, cur.y);
		pDoc->SetModifiedFlag();
		InvalidateRect(CRect(point.x - 2*m_size, point.y - 2*m_size, point.x + 2*m_size, point.y + 2*m_size), FALSE);
	}
	else
	{
		CPoint pnt(point);
		ClientToScreen(&pnt);
		SendMessage(WM_MOUSEMOVE, 0, MAKELPARAM(point.x, point.y));
		TrackMenu(pnt);
		CScrollView::OnRButtonDown(nFlags, point);
	}
}

void CDMMapView::TrackMenu(POINT &point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MAP);	
	CMenu *sub = menu.GetSubMenu(0);


	CPoint cur;
	m_layer->GetCurPoint(cur);

	CDMJournalDoc* pDoc = GetDocument();
	IMapLayer *ml = pDoc->m_journal.GetLayer(m_layer_id);
	IPlace *p = ml->GetPlace(cur.x, cur.y);
	if(!p)
	{
		menu.EnableMenuItem(IDM_DELETEPLACE, MF_BYCOMMAND|MF_GRAYED);
		menu.EnableMenuItem(IDM_VIEWPLACE, MF_BYCOMMAND|MF_GRAYED);
		menu.EnableMenuItem(IDM_MOVEPLACE, MF_BYCOMMAND|MF_GRAYED);
	}
	else
	{
		menu.EnableMenuItem(IDM_DELETEPLACE, MF_BYCOMMAND|MF_ENABLED);
		menu.EnableMenuItem(IDM_VIEWPLACE, MF_BYCOMMAND|MF_ENABLED);
		menu.EnableMenuItem(IDM_MOVEPLACE, MF_BYCOMMAND|MF_ENABLED);
	}

#ifndef _WIN32_WCE
	sub->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, this);
#else
	sub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
#endif
}


void CDMMapView::OnView() 
{	
	CDMJournalDoc* pDoc = GetDocument();
	IPlaceList *pl = pDoc->m_journal.GetLayer(m_layer_id)->GetPlaces();
	if(pl && pl->GetSelectedID() >= 0)
	{
		CDMPlaceEdit edit(IDS_PLACEEDIT, this);
		edit.SetPlaceList(pl);		
		if(edit.DoModal() == IDOK)
		{
			pDoc->UpdateAllViews(this);
			GetDocument()->SetModifiedFlag();
		}
		return;
	}

	IPlaceList *z = pDoc->m_journal.GetZones()->GetPlaces();
	if(z && z->GetSelectedID() >= 0)
	{
		OnSetzone();
	}
}

void CDMMapView::OnDelete() 
{
	CDMJournalDoc* pDoc = GetDocument();
	IPlaceList *pl = pDoc->m_journal.GetLayer(m_layer_id)->GetPlaces();
	if(pl)
	{
		int id = pl->GetSelectedID();
		if(id > 0)
		{
			pDoc->m_journal.GetLayer(m_layer_id)->Delete(id);
			Invalidate(FALSE);
			pDoc->UpdateAllViews(this);
			GetDocument()->SetModifiedFlag();
		}
	}
}

void CDMMapView::OnMove() 
{
	BeginDrag();
}


void CDMMapView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	OnView();
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CDMMapView::BeginDrag()
{
#ifndef _WIN32_WCE
	CDMJournalDoc* pDoc = GetDocument();
	IPlaceList *pl = pDoc->m_journal.GetLayer(m_layer_id)->GetPlaces();
	if(pl)
	{
		m_nDragIndex = pl->GetSelectedID();
		if(m_nDragIndex > 0)
		{
			POINT pt;
			int nOffset = m_size; //offset in pixels for drag image (up and to the left)
			pt.x = nOffset;
			pt.y = nOffset;

/*
			{
				int drag_size = m_size * COS_30 * 2;
				CDC *pDC = GetDC();
				CDC pMDC;
				CBitmap bmp;
				bmp.CreateCompatibleBitmap(pDC, drag_size, drag_size);
				pMDC.CreateCompatibleDC(pDC);
				pMDC.SelectObject(bmp);
				pMDC.FillSolidRect(0, 0, drag_size, drag_size, RGB(0,0,0));
				CSphere::DrawSphere(pMDC.m_hDC, 0, 0, drag_size, drag_size, pl->GetSelected()->GetColor(), TRUE);
				DeleteDC(pMDC);
				
				m_pDragImage = new CImageList();
				m_pDragImage->Create(drag_size, drag_size, ILC_MASK|ILC_COLOR, 0, 1); 

				m_pDragImage->Add(&bmp, RGB(0,0,0));
				
				ReleaseDC(pDC);
			}
*/
			m_pDragImage = CreateDragImage(pl->GetSelected());
			CPoint pnt;
			GetCursorPos(&pnt);
			m_pDragImage->BeginDrag(0, CPoint(nOffset, nOffset));
			m_pDragImage->DragEnter(GetDesktopWindow (), pnt);

			m_bDragging = TRUE;
			SetCapture ();
		}
	}
#endif
}


CImageList *CDMMapView::CreateDragImage(IPlace *p)
{
	CImageList *drag_image;
	int drag_size = m_size * COS_30 * 2;
	CDC *pDC = GetDC();
	CDC pMDC;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, drag_size, drag_size);
	pMDC.CreateCompatibleDC(pDC);
	pMDC.SelectObject(bmp);
	pMDC.FillSolidRect(0, 0, drag_size, drag_size, RGB(0,0,0));
	CSphere::DrawSphere(pMDC.m_hDC, 0, 0, drag_size, drag_size, p->GetColor(), FALSE);
	DeleteDC(pMDC);
	pMDC.m_hDC = NULL;
	
	drag_image = new CImageList();
	drag_image->Create(drag_size, drag_size, ILC_MASK|ILC_COLORDDB, 0, 1); 

	drag_image->Add(&bmp, RGB(0,0,0));
	
	ReleaseDC(pDC);

	return drag_image;
}

void CDMMapView::MovePlace(int id)
{
	CDMJournalDoc* pDoc = GetDocument();
	CPoint cur;
	m_layer->GetCurPoint(cur);
	if(!pDoc->m_journal.GetLayer(m_layer_id)->GetPlace(cur.x, cur.y))
	{
		pDoc->m_journal.GetLayer(m_layer_id)->Delete(m_nDragIndex);
		pDoc->m_journal.GetLayer(m_layer_id)->Add(id, cur.x, cur.y);
		pDoc->m_journal.GetLayer(m_layer_id)->GetPlaces()->Select(id);
		InvalidateRect(0, FALSE);
		GetDocument()->SetModifiedFlag();
	}
}

void CDMMapView::SetLayer(int id)
{
	if(GetDocument()->m_journal.GetLayer(id))
		m_layer_id  = id;
	Invalidate();
}

void CDMMapView::OnSetzone() 
{
	CDMJournalDoc* pDoc = GetDocument();
	IPlaceList *z = pDoc->m_journal.GetZones()->GetPlaces();
	if(z)
	{
		CZoneEdit ze(IDS_ZONES, this);
		ze.SetPlaceList(z);
		if(ze.DoModal() == IDOK)
		{
			CPoint cur;
			m_layer->GetCurPoint(cur);
			int id = z->GetSelectedID();
			if(id >= 0)
			{
				pDoc->m_journal.GetZones()->Add(id, m_layer_id, cur.x, cur.y);
				pDoc->SetModifiedFlag();
				Invalidate();
			}
		}
	}
	
}

void CDMMapView::OnNewzone() 
{
	CDMJournalDoc* pDoc = GetDocument();
	IPlaceList *z = pDoc->m_journal.GetZones()->GetPlaces();
	if(z)
	{
		CDMPlaceEdit edit(IDS_ZONEEDIT, this);
		z->Select(-1);
		edit.SetPlaceList(z);
		edit.DoModal();
/*
		{
			CPoint cur;
			m_layer->GetCurPoint(cur);
			int id = z->GetSelectedID();
			if(id >= 0)
			{
				pDoc->m_journal.GetZones()->Add(id, m_layer_id, cur.x, cur.y);
				pDoc->SetModifiedFlag();
			}
		}
*/
	}	
}

void CDMMapView::OnDelzone() 
{
	CDMJournalDoc* pDoc = GetDocument();
	CPoint cur;
	m_layer->GetCurPoint(cur);
	IPlaceList *z = pDoc->m_journal.GetZones()->GetPlaces();
	int id = z->GetSelectedID();
	if(id >= 0)
	{
		pDoc->m_journal.GetZones()->Add(-1, m_layer_id, cur.x, cur.y);
		pDoc->SetModifiedFlag();
	}		
}

void CDMMapView::OnZoneEditR() 
{
	CDMJournalDoc* pDoc = GetDocument();
	CMenu *menu = theApp.m_mainframe->GetMenu();	
	IPlaceList *z = pDoc->m_journal.GetZones()->GetPlaces();
	if(!m_zoneeditor.m_hWnd)	
	{
		m_zoneeditor.Create(this, WS_SYSMENU | DS_SETFONT | WS_VISIBLE | WS_CAPTION | WS_SIZEBOX, WS_EX_TOOLWINDOW);
		m_zoneeditor.SetPlaceList(z);
	}
	else
	{
		m_zoneeditor.DestroyWindow();		
	}
}

void CDMMapView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_zoneeditor.m_hWnd && m_zoneeditor.IsWindowVisible())
	{
		CDMJournalDoc* pDoc = GetDocument();
		IPlaceList *z = pDoc->m_journal.GetZones()->GetPlaces();		
		CPoint cur;
		m_layer->GetCurPoint(cur);
		int id = z->GetSelectedID();
		if(id >= 0)
		{
			pDoc->m_journal.GetZones()->Add(id, m_layer_id, cur.x, cur.y);
			pDoc->SetModifiedFlag();
			InvalidateRect(CRect(point.x - 2*m_size, point.y - 2*m_size, point.x + 2*m_size, point.y + 2*m_size), FALSE);
		}
	}
	else
	{
		CScrollView::OnLButtonDown(nFlags, point);
	}
}

void CDMMapView::OnGridOnOff() 
{
	// TODO: Add your command handler code here
	m_bGrid = !m_bGrid;
	CFrameWnd *cf = GetParentFrame();
	if(cf)
	{
		CMenu *menu = cf->GetMenu();
		if(menu)
		{
			menu->CheckMenuItem(IDM_GRIDONOFF, (m_bGrid)?MF_CHECKED:MF_UNCHECKED);
		}
	}

	if(m_layer)
	{
		m_layer->m_bGrid = m_bGrid;
		Invalidate();
	}
}

BOOL CDMMapView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

    if (::IsWindow(m_ToolTip.m_hWnd) && pMsg->hwnd == m_hWnd)
    {
        switch(pMsg->message)
        {
        case WM_LBUTTONDOWN:    
        case WM_MOUSEMOVE:
        case WM_LBUTTONUP:    
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:    
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            m_ToolTip.RelayEvent(pMsg);
            break;
        }
    }

	return CScrollView::PreTranslateMessage(pMsg);
}


BOOL CDMMapView::OnToolTipText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	BOOL bHandledNotify = FALSE;

	CPoint CursorPos;
	VERIFY(::GetCursorPos(&CursorPos));
	ScreenToClient(&CursorPos);

	CRect ClientRect;
	GetClientRect(ClientRect);

	// Удостовериться, что курсор попадает в клиентскую область окна,
	// потому что библиотека тоже хочет получать эти сообщения для
	// показа подсказок на панели инструментов.
	if (ClientRect.PtInRect(CursorPos))
	{
		TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;

		CPoint cur;
		if(m_layer)
		{
			m_layer->GetCurPoint(cur);
			CString str;
			CDMJournalDoc* pDoc = GetDocument();
			IMapLayer *ml = pDoc->m_journal.GetLayer(m_layer_id);
			if(ml)
			{
				IPlace *p = ml->GetPlace(cur.x, cur.y);
				IPlace *z = pDoc->m_journal.GetZones()->GetPlace(m_layer_id, cur.x, cur.y);
				if(p || z)
				{		
					CString csZone;
					CString csDirection;
					
					if(p)
					{
						str.Format(_T("%s\n"), p->GetTitleCS());
					}
					if(z)
					{
						csZone.LoadString(IDS_ZONE);
						str += csZone + _T(":") + z->GetTitleCS() + _T("\n"); 
					}

					if(!cur.y && !cur.x)
					{
						csDirection.LoadString(IDS_CENTER);	str += csDirection;						
					}
					else
					{
						if(!cur.x)
						{
							if(cur.y<0)
							{
								csDirection.LoadString(IDS_SOUTH);	str += csDirection;
							}
							else
							{
								csDirection.LoadString(IDS_NORTH);	str += csDirection;
							}
						}
						else
						{
							if(cur.y)
							{
								if(cur.y<0)
								{
									csDirection.LoadString(IDS_SOUTH2);	str += csDirection;
								}
								else
								{
									csDirection.LoadString(IDS_NORTH2);	str += csDirection;
								}
							}

							if(cur.x<0)
							{
								csDirection.LoadString(IDS_WEST);	str += csDirection;
							}
							else
							{
								csDirection.LoadString(IDS_EAST);	str += csDirection;
							}							
						}
					}

					ASSERT(str.GetLength() < sizeof(pTTT->szText));
					_tcscpy(pTTT->szText, str);
					return TRUE;
				}
			}
		}
		pTTT->szText[0] = 0;
	}
	return TRUE;
}
