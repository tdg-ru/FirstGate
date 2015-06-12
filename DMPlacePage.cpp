// DMPlacePage.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMPlacePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMPlacePage property page

IMPLEMENT_DYNCREATE(CDMPlacePage, CPropertyPage)

CDMPlacePage::CDMPlacePage() : CPropertyPage(CDMPlacePage::IDD)
{
	//{{AFX_DATA_INIT(CDMPlacePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_plist = NULL;
#ifdef _WIN32_WCE	
	hLib = LoadLibrary(_T("cdq.dll"));
#endif
	m_c = RGB(0, 255, 0);
}

CDMPlacePage::~CDMPlacePage()
{
#ifdef _WIN32_WCE	
	FreeLibrary(hLib);
#endif
}

void CDMPlacePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMPlacePage)
	DDX_Control(pDX, IDC_TITLE, m_title);
	DDX_Control(pDX, IDC_COLOR, m_color);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMPlacePage, CPropertyPage)
	//{{AFX_MSG_MAP(CDMPlacePage)
	ON_WM_DRAWITEM()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMPlacePage message handlers

void CDMPlacePage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if(nIDCtl == IDC_COLOR)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, m_c);
		if(lpDrawItemStruct->itemAction&ODA_SELECT)
			dc.DrawEdge(&lpDrawItemStruct->rcItem, BDR_SUNKENINNER|BDR_SUNKENOUTER, BF_RECT);
		else
			dc.DrawEdge(&lpDrawItemStruct->rcItem, BDR_RAISEDINNER|BDR_RAISEDOUTER, BF_RECT);
		dc.Detach();
	}
	else
		CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CDMPlacePage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	if(m_title.m_hWnd)
	{
		RECT rc, rc2;
		CWnd *cw = GetDlgItem(IDC_TITLETEXT);
		if(cw)
		{
			cw->GetWindowRect(&rc);
			m_title.GetWindowRect(&rc2);
			ScreenToClient(&rc2);
			m_title.MoveWindow(rc.right - rc.left, rc2.top, cx - rc.right + rc.left, rc2.bottom - rc2.top);
			m_color.MoveWindow(rc.right - rc.left, rc2.bottom + 5, 2 * (rc2.bottom - rc2.top), rc2.bottom - rc2.top);
		}
	}
}

void CDMPlacePage::SetPlaceList(IPlaceList *p)
{
	m_plist = p;
	if(m_plist)
	{
		IPlace *pl = m_plist->GetSelected();
		if(pl)
		{
			pl->GetColor(m_c);
			if(m_title.m_hWnd)
				m_title.SetWindowText(pl->GetTitle());
		}
	}
}

typedef COLORREF (*CDProc)(HWND, COLORREF);

void CDMPlacePage::OnColor() 
{
#ifndef _WIN32_WCE
	CColorDialog dlg;
	dlg.m_cc.rgbResult = m_c;
	if(dlg.DoModal() == IDOK)
	{
		m_c = dlg.m_cc.rgbResult;
		m_color.InvalidateRect(NULL);
	}
#else
	if(hLib)
	{
		CDProc proc = (CDProc)GetProcAddress(hLib, _T("ColorDialog"));
		if(proc)
		{
			m_c = proc(m_hWnd, m_c);
		}		
	}
#endif

}

COLORREF CDMPlacePage::GetColor()
{
	return m_c;
}

void CDMPlacePage::GetTitle(CString &str)
{
	m_title.GetWindowText(str);
}

BOOL CDMPlacePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if(m_plist)
	{
		IPlace *pl = m_plist->GetSelected();
		if(pl)
		{
			pl->GetColor(m_c);
			if(m_title.m_hWnd)
				m_title.SetWindowText(pl->GetTitle());
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
