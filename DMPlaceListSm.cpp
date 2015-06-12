// DMPlaceListSm.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMPlaceListSm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListSm property page

IMPLEMENT_DYNCREATE(CDMPlaceListSm, CPropertyPage)

CDMPlaceListSm::CDMPlaceListSm(int idd) : CPropertyPage(idd)
{
	bModified = FALSE;
	m_placelist = NULL;
}

CDMPlaceListSm::CDMPlaceListSm() : CPropertyPage(CDMPlaceListSm::IDD)
{
	//{{AFX_DATA_INIT(CDMPlaceListSm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	bModified = FALSE;
	m_placelist = NULL;
}

CDMPlaceListSm::~CDMPlaceListSm()
{
}

void CDMPlaceListSm::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMPlaceListSm)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMPlaceListSm, CPropertyPage)
	//{{AFX_MSG_MAP(CDMPlaceListSm)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListSm message handlers


void CDMPlaceListSm::Update()
{
	if(!m_placelist || !m_list.m_hWnd)
	{
		m_list.SetPList(NULL);
		return;
	}
	m_list.SetPList(m_placelist);
}

void CDMPlaceListSm::SetPlaceList(IPlaceList *d)
{
	m_placelist = d;
	Update();
	SetModified();
}

void CDMPlaceListSm::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_list.m_hWnd)
	{
		RECT rc;
		rc.top = 0;
		rc.left = 0;
		rc.right = cx;
		rc.bottom = cy;
		m_list.MoveWindow(&rc);
	}
}

BOOL CDMPlaceListSm::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list.InitColumns();
	Update();
	
	DWORD dwExStyle = m_list.GetExtendedStyle();
#ifndef _WIN32_WCE
	dwExStyle |= LVS_EX_GRIDLINES;
#endif
	m_list.SetExtendedStyle(dwExStyle|LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
