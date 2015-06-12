// DMDescriptionPage1.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMDescriptionPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMDescriptionPage property page

IMPLEMENT_DYNCREATE(CDMDescriptionPage, CPropertyPage)

CDMDescriptionPage::CDMDescriptionPage() : CPropertyPage(CDMDescriptionPage::IDD)
{
	//{{AFX_DATA_INIT(CDMDescriptionPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bModified = FALSE;
	bUpdate = FALSE;
}

CDMDescriptionPage::~CDMDescriptionPage()
{
}

void CDMDescriptionPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMDescriptionPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMDescriptionPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDMDescriptionPage)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_DESCRIPTION, OnEditchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMDescriptionPage message handlers

void CDMDescriptionPage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	CWnd *cw = GetDlgItem(IDC_DESCRIPTION);
	if(cw)
	{
		cw->MoveWindow(0, 0, cx, cy);
	}
}

void CDMDescriptionPage::SetDescription(const DMDescription *d)
{
	bUpdate = TRUE;
	if(d)
	{ 
		CString str;
		if(m_hWnd)
			GetDlgItemText(IDC_DESCRIPTION, str);
		if(d->GetTextCS() != str)
		{
			m_d = *d;
			if(m_hWnd)
			{
				SetDlgItemText(IDC_DESCRIPTION, m_d.GetText());
				bUpdate = FALSE;
			}
		}
	}
	else
	{
		m_d.SetText(_T(""));
		if(m_hWnd)
		{
			SetDlgItemText(IDC_DESCRIPTION, m_d.GetText());
			bUpdate = FALSE;
		}
	}
	SetModified();
}

const DMDescription * CDMDescriptionPage::GetDescription()
{	
	if(m_hWnd)
	{
		CString str;
		GetDlgItemText(IDC_DESCRIPTION, str);
		m_d.SetText(str);
	}
	return &m_d;
}

BOOL CDMDescriptionPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if(bUpdate)
		SetDlgItemText(IDC_DESCRIPTION, m_d.GetText());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDMDescriptionPage::OnEditchange()
{
	bModified = TRUE;
	GetParent()->SendMessage(DMM_DREAMMODIFIED, 0, 0);
}
