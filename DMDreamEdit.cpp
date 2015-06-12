// DMDreamEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMDreamEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEdit

IMPLEMENT_DYNCREATE(CDMDreamEdit, CFormView)

CDMDreamEdit::CDMDreamEdit()
	: CFormView(CDMDreamEdit::IDD)
{
	//{{AFX_DATA_INIT(CDMDreamEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bChanged = false;
}

CDMDreamEdit::~CDMDreamEdit()
{
}

void CDMDreamEdit::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMDreamEdit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMDreamEdit, CFormView)
	//{{AFX_MSG_MAP(CDMDreamEdit)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_CBN_EDITCHANGE(IDC_TYPE, OnEditchangeType)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
//	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE, OnEditchangeType)
	ON_EN_CHANGE(IDC_COMMENT, OnEditchangeType)
	ON_EN_CHANGE(IDC_DESCRIPTION, OnEditchangeType)
	ON_EN_CHANGE(IDC_TITLE, OnEditchangeType)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEdit diagnostics

#ifdef _DEBUG
void CDMDreamEdit::AssertValid() const
{
	CFormView::AssertValid();
}

void CDMDreamEdit::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDMJournalDoc* CDMDreamEdit::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMJournalDoc)));
	return (CDMJournalDoc*)m_pDocument;
}
#endif //_DEBUG




/////////////////////////////////////////////////////////////////////////////
// CDMDreamEdit message handlers

BOOL CDMDreamEdit::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL rez = CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	return rez;
}

void CDMDreamEdit::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	RECT rect, r2;
	int width;
	GetClientRect(&rect);
	CWnd *cWnd = GetDlgItem(IDC_TYPE);
	if(cWnd)
	{
		cWnd->GetWindowRect(&r2);
		ScreenToClient(&r2);
		width = max(cx, r2.right - r2.left);
	}
	cWnd = GetDlgItem(IDC_TITLE);
	if(cWnd)
	{
		cWnd->GetWindowRect(&r2);
		ScreenToClient(&r2);
		cWnd->MoveWindow(0, r2.top, width, r2.bottom-r2.top);	
	}
	cWnd = GetDlgItem(IDC_DESCRIPTION);
	if(cWnd)
	{
		cWnd->GetWindowRect(&r2);
		ScreenToClient(&r2);
		cWnd->MoveWindow(0, r2.top, width, r2.bottom-r2.top);	
	}
	cWnd = GetDlgItem(IDC_COMMENT);
	if(cWnd)
	{
		cWnd->GetWindowRect(&r2);
		ScreenToClient(&r2);
		cWnd->MoveWindow(0, r2.top, width, r2.bottom-r2.top);	
	}
}

void CDMDreamEdit::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(bChanged)
	{
		CString str;
		str.LoadString(IDS_QUESTION1);
		if(MessageBox(str, str, MB_ICONQUESTION|MB_YESNO) == IDYES)
		{
			OnApply();
		}
	}
	CDMJournalDoc* pDoc = GetDocument();
	IDreamRecord *dream = pDoc->m_journal.GetSelected();
	if(dream)
	{
		CWnd *cwnd = GetDlgItem(IDC_TITLE);
		if(cwnd) cwnd->SetWindowText(dream->GetTitle());
		cwnd = GetDlgItem(IDC_DESCRIPTION);
		if(cwnd) cwnd->SetWindowText(dream->GetDescription()->GetText());
		cwnd = GetDlgItem(IDC_COMMENT);
		if(cwnd) cwnd->SetWindowText(dream->GetComment()->GetText());
		CDateTimeCtrl *cdt = (CDateTimeCtrl*)GetDlgItem(IDC_DATE);
		if(cdt)
		{
			SYSTEMTIME d;
			ZeroMemory(&d, sizeof(SYSTEMTIME));
			const DMDate *date = dream->GetDate();
			d.wDay   = date->day;
			d.wMonth = date->month;
			d.wYear  = date->year;
			d.wHour  = date->hour;
			d.wMinute= date->minute;	
			cdt->SetTime(&d);
		}
		CComboBox *cCB = (CComboBox*)GetDlgItem(IDC_TYPE);
		if(cCB)
		{
			if(dream->GetType() != DREAM_UNKNOWN)
				cCB->SetCurSel(dream->GetType()-1);
			else
				cCB->SetWindowText(dream->GetExtType());
		}
	}
	else
	{
		CWnd *cwnd = GetDlgItem(IDC_TITLE);
		if(cwnd) cwnd->SetWindowText(_T(""));
		cwnd = GetDlgItem(IDC_DESCRIPTION);
		if(cwnd) cwnd->SetWindowText(_T(""));
		cwnd = GetDlgItem(IDC_COMMENT);
		if(cwnd) cwnd->SetWindowText(_T(""));
	}
	bChanged = false;
	GetDlgItem(IDC_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_CANCEL)->EnableWindow(false);

}

void CDMDreamEdit::OnApply() 
{
	// TODO: Add your control notification handler code here
	CDMJournalDoc* pDoc = GetDocument();
	IDreamRecord *dream = pDoc->m_journal.GetSelected();
	if(!dream)
	{
		int new_id = pDoc->m_journal.Add();
		pDoc->m_journal.SelectDreamPos(new_id);
		dream = pDoc->m_journal.GetSelected();
	}

	if(dream)
	{
		DMDescription d;
		SYSTEMTIME st;
		DMDate date;
		CString str;
		GetDlgItemText(IDC_TITLE, str);	dream->SetTitle(str);
		GetDlgItemText(IDC_TYPE,  str); dream->SetExtType(str);
		GetDlgItemText(IDC_DESCRIPTION, str); 
		d.SetText(str);
		dream->SetDescription(&d);
		GetDlgItemText(IDC_COMMENT, str); 
		d.SetText(str);
		dream->SetComment(&d);
		((CDateTimeCtrl*)GetDlgItem(IDC_DATE))->GetTime(&st);
		date.FromSysTime(st);
		dream->SetDate(&date);
	}
	else
	{
		CString s1, s2;
		s1.LoadString(IDS_ERROR0);
		s2.LoadString(IDS_ERROR1);
		MessageBox(s2, s1, MB_OK|MB_ICONERROR);
	}

	bChanged = false;
	GetDlgItem(IDC_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_CANCEL)->EnableWindow(false);

	pDoc->UpdateAllViews(this);
}

void CDMDreamEdit::OnCancel() 
{
	// TODO: Add your control notification handler code here
	bChanged = false;
	GetDlgItem(IDC_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_CANCEL)->EnableWindow(false);
	OnUpdate(NULL, 0, NULL);	
}

void CDMDreamEdit::OnEditchangeType() 
{
	// TODO: Add your control notification handler code here
	bChanged = true;
	GetDlgItem(IDC_APPLY)->EnableWindow(true);
	GetDlgItem(IDC_CANCEL)->EnableWindow(true);
}

void CDMDreamEdit::OnNew() 
{
	// TODO: Add your control notification handler code here
	if(bChanged)
	{
		CString str;
		str.LoadString(IDS_QUESTION1);
		if(MessageBox(str, str, MB_ICONQUESTION|MB_YESNO) == IDYES)
		{
			OnApply();
		}
	}
	
	CDMJournalDoc* pDoc = GetDocument();
	pDoc->m_journal.SelectDreamPos(-1);
	
	CWnd *cwnd = GetDlgItem(IDC_TITLE);
	if(cwnd) cwnd->SetWindowText(_T(""));
	cwnd = GetDlgItem(IDC_DESCRIPTION);
	if(cwnd) cwnd->SetWindowText(_T(""));
	cwnd = GetDlgItem(IDC_COMMENT);
	if(cwnd) cwnd->SetWindowText(_T(""));

	GetDlgItem(IDC_APPLY)->EnableWindow(true);
	GetDlgItem(IDC_CANCEL)->EnableWindow(true);
}

void CDMDreamEdit::Clear()
{
	CDMJournalDoc* pDoc = GetDocument();
	pDoc->m_journal.SelectDreamPos(-1);
	
	CWnd *cwnd = GetDlgItem(IDC_TITLE);
	if(cwnd) cwnd->SetWindowText(_T(""));
	cwnd = GetDlgItem(IDC_DESCRIPTION);
	if(cwnd) cwnd->SetWindowText(_T(""));
	cwnd = GetDlgItem(IDC_COMMENT);
	if(cwnd) cwnd->SetWindowText(_T(""));
}
