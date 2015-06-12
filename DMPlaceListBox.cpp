// DMPlaceListBox.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMPlaceListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListBox

CDMPlaceListBox::CDMPlaceListBox()
{
}

CDMPlaceListBox::~CDMPlaceListBox()
{
}


BEGIN_MESSAGE_MAP(CDMPlaceListBox, CListBox)
	//{{AFX_MSG_MAP(CDMPlaceListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListBox message handlers

void CDMPlaceListBox::SetPList(IPlaceList *l)
{
	m_plist = l;
	Update();
}

void CDMPlaceListBox::Update()
{
	if(!m_plist)
		return;
	
	// Delete every other item from the list box.
	ResetContent();
	int cnt = m_plist->GetCount();
	SetRedraw(FALSE);
	for(int i = 0; i < cnt; i++)
	{
		AddString(_T("1"));
	}
	SetRedraw(TRUE);
}


BOOL CDMPlaceListBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LBS_OWNERDRAWFIXED;
	return CListBox::PreCreateWindow(cs);
}

void CDMPlaceListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
   ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
   CDC dc;


   if(!m_plist)
	   return;
   IPlace *p = m_plist->GetPlaceByPos(lpDrawItemStruct->itemID);
   LPCTSTR lpszText = p->GetTitle();
   ASSERT(lpszText != NULL);

   COLORREF color;
   p->GetColor(color);
  

   RECT rc = lpDrawItemStruct->rcItem;
   RECT rc1 = lpDrawItemStruct->rcItem;

   rc1.right = rc.left + rc.bottom - rc.top;
   rc.left += rc.bottom - rc.top + 1;

   dc.Attach(lpDrawItemStruct->hDC);


   // Save these value to restore them when done drawing.
   COLORREF crOldTextColor = dc.GetTextColor();
   COLORREF crOldBkColor = dc.GetBkColor();

   dc.FillSolidRect(&rc1, color);

   // If this item is selected, set the background color 
   // and the text color to appropriate values. Also, erase
   // rect by filling it with the background color.
   if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
      (lpDrawItemStruct->itemState & ODS_SELECTED))
   {
      dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
      dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
      dc.FillSolidRect(&rc, 
         ::GetSysColor(COLOR_HIGHLIGHT));
   }
   else
      dc.FillSolidRect(&rc, crOldBkColor);

   // If this item has the focus, draw a red frame around the
   // item's rect.
   if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
      (lpDrawItemStruct->itemState & ODS_FOCUS))
   {
      CBrush br(::GetSysColor(COLOR_BTNFACE));
      dc.DrawFocusRect(&lpDrawItemStruct->rcItem);
   }

   // Draw the text.
   dc.DrawText(
      lpszText,
      _tcslen(lpszText),
      &rc,
      DT_LEFT|DT_SINGLELINE|DT_VCENTER);

   // Reset the background color and the text color back to their
   // original values.
   dc.SetTextColor(crOldTextColor);
   dc.SetBkColor(crOldBkColor);

   dc.Detach();

}

void CDMPlaceListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	ASSERT(lpMeasureItemStruct->CtlType == ODT_LISTBOX);
	CSize   sz;
	CDC*    pDC = GetDC();
	sz = pDC->GetTextExtent(_T("#"));
	ReleaseDC(pDC);
	lpMeasureItemStruct->itemHeight = sz.cy + 2;
}
