// ZoneEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "ZoneEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoneEdit

IMPLEMENT_DYNAMIC(CZoneEdit, CPropertySheet)

CZoneEdit::CZoneEdit(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	InitPages();
}

CZoneEdit::CZoneEdit(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	InitPages();
}

CZoneEdit::~CZoneEdit()
{
}


BEGIN_MESSAGE_MAP(CZoneEdit, CPropertySheet)
	//{{AFX_MSG_MAP(CZoneEdit)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoneEdit message handlers

void CZoneEdit::InitPages()
{
	m_placelist = NULL;

	m_plist.m_psp.dwFlags |= PSP_USETITLE;
	m_plist.m_psp.dwFlags &= ~PSP_HASHELP;
	m_plist.m_psp.pszTitle = (TCHAR *)IDS_ZONELIST;
/*
	m_place.m_psp.dwFlags |= PSP_USETITLE;
	m_place.m_psp.dwFlags &= ~PSP_HASHELP;
	m_place.m_psp.pszTitle = (TCHAR *)IDS_ZONE;

	m_description.m_psp.dwFlags |= PSP_USETITLE;
	m_description.m_psp.dwFlags &= ~PSP_HASHELP;
	m_description.m_psp.pszTitle = (TCHAR *)IDS_DESCRIPTION;
*/
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	m_psh.dwFlags &= ~PSH_HASHELP;	

	AddPage(&m_plist);
//	AddPage(&m_place);
//	AddPage(&m_description);
}

void CZoneEdit::SetPlaceList(IPlaceList *p)
{
	m_placelist = p;
	m_plist.SetPlaceList(p);
}

BOOL CZoneEdit::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	m_plist.m_list.isZone = TRUE;
	Update();

	return bResult;
}

void CZoneEdit::Update()
{
	m_plist.SetPlaceList(m_placelist);
}

void CZoneEdit::OnSize(UINT nType, int cx, int cy) 
{
	CPropertySheet::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CTabCtrl *tab = GetTabControl();
	if(tab && m_plist.m_hWnd)
	{
		RECT rc;
		tab->MoveWindow(0, 0, cx, cy);
		CPropertyPage *page = GetActivePage();	
		if(page)
		{
			tab->GetClientRect(&rc);
			tab->AdjustRect(FALSE, &rc);
			page->MoveWindow(&rc);
		}		
	}	
}
