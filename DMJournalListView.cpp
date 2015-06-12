// DMJournalListView.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMJournalListView.h"
#include "DMJournalDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMJournalListView

IMPLEMENT_DYNCREATE(CDMJournalListView, CListView)

CDMJournalListView::CDMJournalListView()
{
	m_editpage = NULL;
	il = NULL;
}

CDMJournalListView::~CDMJournalListView()
{
	delete m_editpage;
	delete il;
}


BEGIN_MESSAGE_MAP(CDMJournalListView, CListView)
	//{{AFX_MSG_MAP(CDMJournalListView)
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(IDM_DELETE, OnDelete)
	ON_COMMAND(IDM_NEW, OnNew)
	ON_COMMAND(IDM_DVIEW, OnView)
	ON_MESSAGE(DMM_UPDATELIST, OnListUpdate)
	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, OnItemactivate)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMJournalListView drawing

void CDMJournalListView::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDMJournalListView diagnostics

#ifdef _DEBUG
void CDMJournalListView::AssertValid() const
{
	CListView::AssertValid();
}

void CDMJournalListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDMJournalDoc* CDMJournalListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMJournalDoc)));
	return (CDMJournalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMJournalListView message handlers

void CDMJournalListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CDMJournalDoc* pDoc = GetDocument();

	CListCtrl &list = GetListCtrl();

#ifndef _WIN32_WCE
	list.LockWindowUpdate();
#else
	list.SetRedraw(FALSE); 
#endif

	if(list.GetItemCount() != pDoc->m_journal.GetDreamsCount())
	{
		list.SetItemCount(pDoc->m_journal.GetDreamsCount());
	}

	int id = pDoc->m_journal.GetSelectedPos();

	if(id >= 0 && id != list.GetSelectionMark())
	{		
		list.SetSelectionMark(id);
		list.SetItemState(id, LVIS_FOCUSED|LVIS_SELECTED, LVIS_SELECTED|LVIS_FOCUSED);
		list.EnsureVisible(id, FALSE);		
	}
	else
	{
		list.EnsureVisible((id>=0)?id:0, FALSE);
	}

	if(m_editpage)
		m_editpage->OnUpdate();

#ifndef _WIN32_WCE
	list.UnlockWindowUpdate();
#else
	list.SetRedraw(TRUE); 
#endif

	InvalidateRect(NULL);
}

const int images[] = {IDI_OTHERTYPES, IDI_LOOP, IDI_SPEAK, IDI_ACTION, IDI_LUCID, IDI_CONSCIOUS};

BOOL CDMJournalListView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	dwStyle = (dwStyle & ~LVS_TYPEMASK) | LVS_REPORT | LVS_OWNERDATA | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_OWNERDRAWFIXED;
	BOOL rez = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	
	if(rez)
	{
		CListCtrl &list = GetListCtrl();
		SIZE size;
		CDC *dc = list.GetDC();
		GetTextExtentPoint32(dc->m_hDC, _T("##.0#.20##"), 10, &size);
		list.ReleaseDC(dc);

		CString str; 
		list.InsertColumn(0, NULL, LVCFMT_LEFT, 20);
		str.LoadString(IDS_DATE);		
		list.InsertColumn(1, str, LVCFMT_LEFT, size.cx);
		str.LoadString(IDS_TITLE);
		list.InsertColumn(2, str, LVCFMT_LEFT, size.cx*3);


		DWORD dwExStyle = list.GetExtendedStyle();
#ifndef _WIN32_WCE
		dwExStyle |= LVS_EX_GRIDLINES;
#endif
		list.SetExtendedStyle(dwExStyle|LVS_EX_FULLROWSELECT);

		il = new CImageList;
		il->Create(16, 16, ILC_COLORDDB, 0, 6);
		for(int i = 0; i < 6; i++)
		{
#ifndef _WIN32_WCE
			HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
					MAKEINTRESOURCE(images[i]),
					IMAGE_BITMAP,
					16,16, // cx, cy
					LR_CREATEDIBSECTION);
			CBitmap cbmp;
			cbmp.Attach(hbmp);
			il->Add(&cbmp, (CBitmap*)NULL);
#else
			HICON hico = (HICON)::LoadImage(AfxGetInstanceHandle(),
					MAKEINTRESOURCE(images[i]),
					IMAGE_ICON,
					16,16, // cx, cy
					0);
			il->Add(hico);
#endif
		}

		list.SetImageList(il, LVSIL_SMALL);
	}
	return rez;
}

void CDMJournalListView::OnSize(UINT nType, int cx, int cy) 
{
	
	CListCtrl &list = GetListCtrl();	
	if(list.m_hWnd)
	{
		int c0 = list.GetColumnWidth(1);
		list.SetColumnWidth(2, cx - c0 - 20);
	}

	CListView::OnSize(nType, cx, cy);
}


void CDMJournalListView::OnSelectItem(int n)
{
	CListCtrl &list = GetListCtrl();
	CDMJournalDoc* pDoc = GetDocument();
	int id;
	if(n < 0)
		id = list.GetSelectionMark();
	else
		id = n;
	if(id != pDoc->m_journal.GetSelectedPos())
	{
		pDoc->m_journal.SelectDreamPos(id);
		pDoc->UpdateAllViews(this);
		if(m_editpage)
			m_editpage->OnUpdate();
	}
}

void CDMJournalListView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
#ifndef _WIN32_WCE
	OnSelectItem();
	POINT point;
	GetCursorPos(&point);
	TrackMenu(point);
#endif

	*pResult = 0;
}

void CDMJournalListView::OnDelete()
{
	CString t1, t2;
	t1.LoadString(IDS_QUESTION2);
	t2.LoadString(IDS_QUESTION3);
	if(MessageBox(t2, t1, MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		CDMJournalDoc* pDoc = GetDocument();
		pDoc->m_journal.Delete(pDoc->m_journal.GetSelectedPos());
		OnUpdate(this, 0, NULL);
		pDoc->UpdateAllViews(this);
	}
}

void CDMJournalListView::OnNew()
{
	CDMJournalDoc* pDoc = GetDocument();
	pDoc->m_journal.SelectDreamPos(-1);
	OnView();
	pDoc->UpdateAllViews(this);
}

void CDMJournalListView::OnView()
{
	if(!m_editpage)
	{
		m_editpage = new CDMDreamEdit2(IDS_DREAMEDIT, this);
		m_editpage->SetJournal(&(GetDocument()->m_journal));
	}

	if(m_editpage)
	{
#ifndef _WIN32_WCE
		if(!m_editpage->m_hWnd)
		{
			m_editpage->Create(this, WS_SYSMENU | DS_SETFONT | WS_VISIBLE | WS_CAPTION | WS_SIZEBOX, WS_EX_TOOLWINDOW);
			m_editpage->ShowWindow(SW_SHOWNORMAL);
			m_editpage->OnUpdate();
		}
		else
		{
			if(!m_editpage->IsWindowVisible())
			{
				m_editpage->ShowWindow(SW_SHOWNORMAL);
				m_editpage->OnUpdate();
			}
		}
#else // _WIN32_WCE
	m_editpage->DoModal();
	if(m_editpage->bModified)
	{
		GetDocument()->SetModifiedFlag();
	}

	OnUpdate(this, 0, 0);
#endif // _WIN32_WCE
	}
}

LRESULT CDMJournalListView::OnListUpdate(WPARAM wParam, LPARAM)
{
	CDMJournalDoc* pDoc = GetDocument();
	CListCtrl &list = GetListCtrl();

	if(wParam)
	{
		pDoc->SetModifiedFlag();
	}

#ifndef _WIN32_WCE
	list.LockWindowUpdate();
#else
	list.SetRedraw(FALSE); 
#endif

	if(list.GetItemCount() != pDoc->m_journal.GetDreamsCount())
	{
		list.SetItemCount(pDoc->m_journal.GetDreamsCount());		
	}

	int id = pDoc->m_journal.GetSelectedPos();
	if(id >= 0 && id != list.GetSelectionMark())
	{
		list.SetSelectionMark(id);
		list.SetItemState(id, LVIS_FOCUSED|LVIS_SELECTED, LVIS_SELECTED|LVIS_FOCUSED);
		list.EnsureVisible(id, FALSE);
	}

#ifndef _WIN32_WCE
	list.UnlockWindowUpdate();
#else
	list.SetRedraw(TRUE); 
#endif

	GetDocument()->UpdateAllViews(this);
	return 0;
}

void CDMJournalListView::OnItemactivate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnSelectItem();
	OnView();
	*pResult = 0;
}

void CDMJournalListView::OnLButtonDown(UINT nFlags, CPoint point) 
{
#ifdef _WIN32_WCE
	OnSelectItem();
	if(SHRecognizeGesture(point, FALSE))
	{
		TrackMenu(point);
	}
#endif
	
	CListView::OnLButtonDown(nFlags, point);
}

void CDMJournalListView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	 int iItem = pDispInfo->item.iItem;
	 CDMJournalDoc* pDoc = GetDocument();

	 if(pDispInfo->item.mask & LVIF_TEXT != 0)
	 {
		 // Item's text is requested. Write it to pDispInfo structure.
		 switch(pDispInfo->item.iSubItem)
		 {
		 case 1: 
			 {
				 const DMDate *date = pDoc->m_journal.GetDreamByPos(iItem)->GetDate();
				 _stprintf(pDispInfo->item.pszText, _T("%02d.%02d.%d"), date->day, date->month, date->year); 
				 break;
			 }
		 case 2: 
			 _stprintf(pDispInfo->item.pszText, _T("%s"), pDoc->m_journal.GetDreamByPos(iItem)->GetTitle()); 
			 break;
		 }
	 }

	 if(pDispInfo->item.mask & LVIF_IMAGE != 0)
	 {
		pDispInfo->item.iImage = pDoc->m_journal.GetDreamByPos(iItem)->GetType();
	 }
	
	*pResult = 0;
}

void CDMJournalListView::TrackMenu(POINT &p)
{
	CMenu menu;
	menu.LoadMenu(IDR_DMLIST);	
	
	CMenu *sub = menu.GetSubMenu(0);
	int id = GetDocument()->m_journal.GetSelectedPos();
	if(id < 0)
	{
		menu.EnableMenuItem(IDM_DELETE, MF_BYCOMMAND|MF_GRAYED);
		menu.EnableMenuItem(IDM_DVIEW, MF_BYCOMMAND|MF_GRAYED);
		menu.EnableMenuItem(IDM_NEW, MF_BYCOMMAND|MF_ENABLED);
	}
	else
	{
		menu.EnableMenuItem(IDM_DELETE, MF_BYCOMMAND|MF_ENABLED);
		menu.EnableMenuItem(IDM_DVIEW, MF_BYCOMMAND|MF_ENABLED);
		menu.EnableMenuItem(IDM_NEW, MF_BYCOMMAND|MF_ENABLED);
	}

#ifndef _WIN32_WCE
	sub->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, p.x, p.y, this);
#else
	sub->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);
#endif
}

void CDMJournalListView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->uNewState&LVIS_SELECTED)
		OnSelectItem(pNMListView->iItem);
	*pResult = 0;
}

COLORREF typecolors[] = 
{
	RGB(255, 200, 200),	//IDI_OTHERTYPES
	RGB(200, 255, 255),	//IDI_LOOP
	RGB(255, 229, 187),	//IDI_SPEAK
	RGB(200, 255, 200),	//IDI_ACTION
	RGB(251, 255, 222),	//IDI_LUCID
	RGB(255, 255, 255),	//IDI_CONSCIOUS
};

void CDMJournalListView::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   ASSERT(lpDrawItemStruct->CtlType == ODT_LISTVIEW);
   CDC dc;

   CDMJournalDoc* pDoc = GetDocument();
   IDreamRecord *p = pDoc->m_journal.GetDreamByPos(lpDrawItemStruct->itemID);
   
   CString sdat;
   const DMDate *date = p->GetDate();
   sdat.Format(_T("%02d.%02d.%d"), date->day, date->month, date->year); 
   CString str = p->GetTitle();

   CListCtrl &list = GetListCtrl();
   int w0 = list.GetColumnWidth(0);
   int w1 = list.GetColumnWidth(1);
   int w2 = list.GetColumnWidth(2);

   lpDrawItemStruct->rcItem.bottom--;
   RECT rc0 = lpDrawItemStruct->rcItem;
   RECT rc1 = lpDrawItemStruct->rcItem;
   RECT rc2 = lpDrawItemStruct->rcItem;

   rc0.right = rc0.left + w0 - 1;

   rc1.left  = rc0.left + w0;
   rc1.right = rc1.left + w1 - 1;

   rc2.left = rc1.left + w1;

   rc0.left += 2;
   rc1.left += 3;
   rc2.left += 3;

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
	  dc.FillSolidRect(&lpDrawItemStruct->rcItem, 
         ::GetSysColor(COLOR_HIGHLIGHT));
	  list.GetImageList(LVSIL_SMALL)->Draw(&dc, p->GetType(), CPoint(rc0.left, rc0.top), ILD_FOCUS|ILD_TRANSPARENT);
   }
   else
   {
	   int type_id = p->GetType();
	   if(type_id >= DREAM_UNKNOWN && type_id < DREAM_ERROR)
	   {
		   dc.FillSolidRect(&lpDrawItemStruct->rcItem, typecolors[type_id]);
		   list.GetImageList(LVSIL_SMALL)->Draw(&dc, type_id, CPoint(rc0.left, rc0.top), ILD_TRANSPARENT);	  
	   }
   }

   // If this item has the focus, draw a red frame around the
   // item's rect.
   if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
      (lpDrawItemStruct->itemState & ODS_FOCUS))
   {
      CBrush br(::GetSysColor(COLOR_BTNFACE));
      dc.DrawFocusRect(&lpDrawItemStruct->rcItem);
   }

   // Draw the text.   
#ifndef _WIN32_WCE
   dc.DrawText(sdat, &rc1, DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
   dc.DrawText(str, &rc2, DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
#else
   dc.DrawText(sdat, &rc1, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
   dc.DrawText(str, &rc2, DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOCLIP);
#endif
   // Reset the background color and the text color back to their
   // original values.
//   dc.SelectObject(cOldPen);
//   dc.SelectObject(cOldBrush);
   dc.SetTextColor(crOldTextColor);
   dc.SetBkColor(crOldBkColor);

   dc.Detach();
}