// DMPlaceListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMPlaceListCtrl.h"
#include "DMPlaceEdit.h"
#include "Sphere.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListCtrl

CDMPlaceListCtrl::CDMPlaceListCtrl()
{
	isZone = FALSE;
	m_plist = NULL;

#ifndef _WIN32_WCE
	m_bDragging = FALSE;
#endif
}

CDMPlaceListCtrl::~CDMPlaceListCtrl()
{
}


BEGIN_MESSAGE_MAP(CDMPlaceListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CDMPlaceListCtrl)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, OnItemactivate)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListCtrl message handlers

void CDMPlaceListCtrl::SetPList(IPlaceList *l)
{
	m_plist = l;

	if(m_plist)
	{
		int ni = m_plist->GetSelectedPos();
		if(ni < 0)
			EnsureVisible(0, FALSE);
		else
		{
			SetSelectionMark(ni);
			SetItemState(ni, LVIS_FOCUSED|LVIS_SELECTED, LVIS_SELECTED|LVIS_FOCUSED);
			EnsureVisible(ni, FALSE);
		}
	}
	Update();
}

void CDMPlaceListCtrl::Update()
{
	if(!m_plist)
	{
		if(m_hWnd)
		{
			SetItemCountEx(0);
			Invalidate();
		}
		return;
	}
	if(m_hWnd) 
		SetItemCountEx(m_plist->GetCount());

	OnSelectItem();
	Invalidate();
}

void CDMPlaceListCtrl::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

BOOL CDMPlaceListCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{

	cs.style = (cs.style & ~LVS_TYPEMASK) | LVS_REPORT | LVS_OWNERDATA | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_OWNERDRAWFIXED;

	return CListCtrl::PreCreateWindow(cs);
}

void CDMPlaceListCtrl::OnUpdate()
{
	Update();
}


int CDMPlaceListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitColumns();

	DWORD dwExStyle = GetExtendedStyle();
#ifndef _WIN32_WCE
		dwExStyle |= LVS_EX_GRIDLINES;
#endif
	SetExtendedStyle(dwExStyle|LVS_EX_FULLROWSELECT);


	return 0;
}


void CDMPlaceListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   ASSERT(lpDrawItemStruct->CtlType == ODT_LISTVIEW);
   CDC dc;


   if(!m_plist)
	   return;
   IPlace *p = m_plist->GetPlaceByPos(lpDrawItemStruct->itemID);
   if(!p)
	   return;

   CString str = p->GetTitle();

   COLORREF color;
   p->GetColor(color);
  
   int w0 = GetColumnWidth(0);
   int w1 = GetColumnWidth(1);

   RECT rc = lpDrawItemStruct->rcItem;
   RECT rc1 = lpDrawItemStruct->rcItem;

   rc1.right = rc.left + w0 - 1;
   rc1.left+=2;
   rc1.top++;
   rc1.bottom--;
   rc.left += w0 + 2;
   rc.right = w0 + w1;
   rc.bottom--;

   dc.Attach(lpDrawItemStruct->hDC);


   // Save these value to restore them when done drawing.
   COLORREF crOldTextColor = dc.GetTextColor();
   COLORREF crOldBkColor = dc.GetBkColor();

   // If this item is selected, set the background color 
   // and the text color to appropriate values. Also, erase
   // rect by filling it with the background color.
   if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
      (lpDrawItemStruct->itemState & ODS_SELECTED))
   {
      dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
      dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
      dc.FillSolidRect(&rc1, crOldBkColor);
	  dc.FillSolidRect(&rc/*&lpDrawItemStruct->rcItem*/, 
         ::GetSysColor(COLOR_HIGHLIGHT));
   }
   else
      dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);

   if(isZone)
   {
	   dc.FillSolidRect(&rc1, color);
   }
   else
   {
	   CSphere::DrawSphere(dc.m_hDC, rc1.left, rc1.top, 
		   rc1.right, rc1.bottom, color);
   }

   // If this item has the focus, draw a red frame around the
   // item's rect.
   if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
      (lpDrawItemStruct->itemState & ODS_FOCUS))
   {
      CBrush br(::GetSysColor(COLOR_BTNFACE));
      dc.DrawFocusRect(&rc);
   }

   rc.left++;
   // Draw the text.
#ifndef _WIN32_WCE
   dc.DrawText(str, &rc, DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
#else
   dc.DrawText(str, &rc, DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOCLIP);
#endif
   // Reset the background color and the text color back to their
   // original values.
   dc.SetTextColor(crOldTextColor);
   dc.SetBkColor(crOldBkColor);

   dc.Detach();
}

/*
BOOL CDMPlaceListCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	dwStyle = (dwStyle & ~LVS_TYPEMASK) | LVS_REPORT | LVS_OWNERDATA | LVS_SINGLESEL | LVS_SHOWSELALWAYS;

	
	BOOL rez = CListCtrl::Create(dwStyle, rect, pParentWnd, nID);

	return rez;
}
*/

void CDMPlaceListCtrl::InitColumns()
{
	CString str; 
	str.LoadString(IDS_TITLE);

	LVCOLUMN col;
	col.mask = LVCF_WIDTH;	
	col.cx = 16;

	InsertColumn(0, &col);
	InsertColumn(1, str, LVCFMT_LEFT, 100, 1);
}

void CDMPlaceListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	SetColumnWidth(1, cx - GetColumnWidth(0) - 1);	

	
}

void CDMPlaceListCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CDMPlaceListCtrl::OnSelectItem(int n)
{
	if(!m_plist || !m_hWnd)
		return;
	if(n == -1)
		n = GetSelectionMark();
	if(n>=0)
	{
		IPlace *p = m_plist->GetPlaceByPos(n);
		if(p)
		{
			int id = p->GetID();
			m_plist->Select(id);
		}
		EnsureVisible(n, FALSE);
	}
}

void CDMPlaceListCtrl::OnItemactivate(NMHDR* pNMHDR, LRESULT* pResult)
{
	CDMPlaceEdit edit((isZone)?IDS_ZONEEDIT:IDS_PLACEEDIT, this);
	OnSelectItem();
	edit.SetPlaceList(m_plist);
	if(edit.DoModal() == IDOK)
	{
		Update();	
		CWnd *pw = GetParent();
		if(pw && pw->m_hWnd)
			pw->SendMessage(DMM_PLACELISTCH, 0, 0);
	}
	*pResult = 0;
}

void CDMPlaceListCtrl::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->uNewState&LVIS_SELECTED)
		OnSelectItem(pNMListView->iItem);
	*pResult = 0;
}



void CDMPlaceListCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if(isZone)
		return;

#ifndef _WIN32_WCE
	m_nDragIndex = m_plist->GetPlaceByPos(pNMListView->iItem)->GetID();

	//// Create a drag image
    POINT pt;
    int nOffset = 10; //offset in pixels for drag image (up and to the left)
    pt.x = nOffset;
    pt.y = nOffset;

    m_pDragImage = CreateDragImage(pNMListView->iItem, &pt);
    ASSERT(m_pDragImage); //make sure it was created
    //We will call delete later (in LButtonUp) to clean this up

    //// Change the cursor to the drag image
    ////    (still must perform DragMove() in OnMouseMove() to show it moving)
    m_pDragImage->BeginDrag(0, CPoint(nOffset, nOffset));
    m_pDragImage->DragEnter(GetDesktopWindow(), pNMListView->ptAction);

	m_bDragging = TRUE;
	
	//// Capture all mouse messages
    SetCapture ();
#endif
	
	*pResult = 0;
}

void CDMPlaceListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
#ifndef _WIN32_WCE
	if (m_bDragging)
	{
		//// Move the drag image
		CPoint pt(point);           //get our current mouse coordinates
		ClientToScreen(&pt);        //convert to screen coordinates

		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT(pDropWnd); //make sure we have a window

		// Save current window pointer as the CListCtrl we are dropping onto
		m_pDropWnd = pDropWnd;

/*		
		if(pDropWnd->IsKindOf(RUNTIME_CLASS (CDMMapView)))
		{
			// Convert from screen coordinates to drop target client coordinates
			CPoint pt2(pt);
			pDropWnd->ScreenToClient(&pt2);
			pDropWnd->SendMessage(WM_MOUSEMOVE, 0, MAKELPARAM(pt2.x, pt2.y));
		}
*/
		m_pDragImage->DragMove(pt); //move the drag image to those coordinates
		// Unlock window updates (this allows the dragging image to be shown smoothly)
		m_pDragImage->DragShowNolock(true);
	}
#endif
	CListCtrl::OnMouseMove(nFlags, point);
}

void CDMPlaceListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
#ifndef _WIN32_WCE
	if (m_bDragging)
	{	
		// Release mouse capture, so that other controls can get control/messages
		ReleaseCapture ();
		// Note that we are NOT in a drag operation
		m_bDragging = FALSE;
		// End dragging image
		m_pDragImage->DragLeave (GetDesktopWindow ());
		m_pDragImage->EndDrag ();
		delete m_pDragImage; //must delete it because it was created at the beginning of the drag
		m_pDragImage = 0;



		CPoint pt(point);           //get our current mouse coordinates
		ClientToScreen(&pt);        //convert to screen coordinates
		m_pDropWnd = WindowFromPoint (pt);
		ASSERT(m_pDropWnd); //make sure we have a window
		if(m_pDropWnd->IsKindOf(RUNTIME_CLASS (CDMMapView)))
		{

			// Convert from screen coordinates to drop target client coordinates
			m_pDropWnd->ScreenToClient(&pt);
			m_pDropWnd->SendMessage(WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));

 			CDMMapView *mv = (CDMMapView*)m_pDropWnd;
			mv->AddPlace(m_nDragIndex);
			Update();
			CWnd *pw = GetParent();
			if(pw && pw->m_hWnd)
				pw->SendMessage(DMM_PLACELISTCH, 0, 0);
		}
	}
#endif
	CListCtrl::OnLButtonUp(nFlags, point);
}

void CDMPlaceListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	switch(pNMListView->iSubItem)
	{
	case 0:	m_plist->Sort(0,1); break;
	case 1:
	default: m_plist->Sort(1,0); break;
	}
	Update();

	*pResult = 0;
}