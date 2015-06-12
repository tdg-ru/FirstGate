// DMDreamPage.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMDreamPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMDreamPage property page

IMPLEMENT_DYNCREATE(CDMDreamPage, CPropertyPage)

CDMDreamPage::CDMDreamPage() : CPropertyPage(CDMDreamPage::IDD)
{
	//{{AFX_DATA_INIT(CDMDreamPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	mp_dream = NULL;
	bModified = FALSE;
}

CDMDreamPage::~CDMDreamPage()
{
}

void CDMDreamPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMDreamPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMDreamPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDMDreamPage)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_TITLE, OnEditchange)
	ON_CBN_EDITCHANGE(IDC_TYPE, OnEditchange)
	ON_CBN_SELCHANGE(IDC_TYPE, OnEditchange)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE, OnDatetimechangeDate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMDreamPage message handlers

void CDMDreamPage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CWnd *cs = GetDlgItem(IDC_CAPT);
	RECT rc, rc2;
	if(cs)
	{
		cs->GetWindowRect(&rc);	ScreenToClient(&rc);
		cs = GetDlgItem(IDC_TITLE);
		cs->GetWindowRect(&rc2); ScreenToClient(&rc2);
		cs->MoveWindow(rc.right, rc2.top, cx - rc.right, rc2.bottom - rc2.top);
		
		cs = GetDlgItem(IDC_DATE);
		cs->GetWindowRect(&rc2); ScreenToClient(&rc2);
		cs->MoveWindow(rc.right, rc2.top, cx - rc.right, rc2.bottom - rc2.top);

		cs = GetDlgItem(IDC_TYPE);
		cs->GetWindowRect(&rc2); ScreenToClient(&rc2);
		cs->MoveWindow(rc.right, rc2.top, cx - rc.right, rc2.bottom - rc2.top);
	}
}

BOOL CDMDreamPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	Update();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDMDreamPage::SetDream(IDreamRecord *d)
{
	mp_dream = d;
	Update();
	SetModified();
}

void CDMDreamPage::Update()
{
	if(!m_hWnd)
		return;
	if(mp_dream)
	{
		SetDlgItemText(IDC_TITLE, mp_dream->GetTitle());
		if(mp_dream->GetType())
		{
			((CComboBox*)(GetDlgItem(IDC_TYPE)))->SetCurSel(mp_dream->GetType()-1);
		}
		else
		{
			SetDlgItemText(IDC_TYPE, mp_dream->GetExtType());
		}
		CDateTimeCtrl *cdt = (CDateTimeCtrl*)GetDlgItem(IDC_DATE);
		if(cdt)
		{
			SYSTEMTIME d;
			ZeroMemory(&d, sizeof(SYSTEMTIME));
			const DMDate *date = mp_dream->GetDate();
			d.wDay   = date->day;
			d.wMonth = date->month;
			d.wYear  = date->year;
			d.wHour  = date->hour;
			d.wMinute= date->minute;	
			cdt->SetTime(&d);
		}
	}
	else
	{
		SetDlgItemText(IDC_TITLE, _T(""));
		SetDlgItemText(IDC_TYPE, _T(""));
	}
	bModified = FALSE;
}

void CDMDreamPage::GetDream(IDreamRecord *dream)
{
	if(m_hWnd)
	{
		CString str;
		GetDlgItemText(IDC_TITLE, str);	dream->SetTitle(str);
		GetDlgItemText(IDC_TYPE, str); dream->SetExtType(str);
		dream->SetType(GetTypeID(str));
		DMDate date;
		SYSTEMTIME sd;
		((CDateTimeCtrl*)GetDlgItem(IDC_DATE))->GetTime(&sd);
		date.FromSysTime(sd);
		dream->SetDate(&date);
	}
}

void CDMDreamPage::OnEditchange()
{
	bModified = TRUE;
	GetParent()->SendMessage(DMM_DREAMMODIFIED, 0, 0);
}


void CDMDreamPage::OnDatetimechangeDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnEditchange();
	*pResult = 0;
}
