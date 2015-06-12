// DMDreamEdit2.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMDreamEdit2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEdit2

IMPLEMENT_DYNAMIC(CDMDreamEdit2, CPropertySheet)

CDMDreamEdit2::CDMDreamEdit2(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	InitPages();	
}

CDMDreamEdit2::CDMDreamEdit2(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	InitPages();
}

CDMDreamEdit2::~CDMDreamEdit2()
{
}


BEGIN_MESSAGE_MAP(CDMDreamEdit2, CPropertySheet)
	//{{AFX_MSG_MAP(CDMDreamEdit2)
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTONSAVE, OnSave)
	ON_COMMAND(ID_BUTTONCANCEL, OnDmCancel)
	ON_COMMAND(ID_BUTTONFIRST, OnFirst)
	ON_COMMAND(ID_BUTTONPREV, OnPrev)
	ON_COMMAND(ID_BUTTONNEXT, OnNext)
	ON_COMMAND(ID_BUTTONLAST, OnLast)
	ON_COMMAND(ID_BUTTONNEW, OnNew)
	ON_COMMAND(ID_BUTTONDELETE, OnDelete)
	ON_MESSAGE(DMM_DREAMMODIFIED, OnEnableBtns)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


void CDMDreamEdit2::InitPages()
{	
	bModified = FALSE;
	m_journal = NULL;

	m_dream.m_psp.dwFlags |= PSP_USETITLE;
	m_dream.m_psp.dwFlags &= ~PSP_HASHELP;
	m_dream.m_psp.pszTitle = (TCHAR *)IDS_DREAM;

	m_description.m_psp.dwFlags |= PSP_USETITLE;
	m_description.m_psp.dwFlags &= ~PSP_HASHELP;
	m_description.m_psp.pszTitle = (TCHAR *)IDS_DESCRIPTION;

	m_comment.m_psp.dwFlags |= PSP_USETITLE;
	m_comment.m_psp.dwFlags &= ~PSP_HASHELP;
	m_comment.m_psp.pszTitle = (TCHAR *)IDS_COMMENT;

	m_placelist.m_psp.dwFlags |= PSP_USETITLE;
	m_placelist.m_psp.dwFlags &= ~PSP_HASHELP;
	m_placelist.m_psp.pszTitle = (TCHAR *)IDS_PLACES;

	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	m_psh.dwFlags &= ~PSH_HASHELP;	

	AddPage(&m_dream);
	AddPage(&m_description);	
	AddPage(&m_placelist);
	AddPage(&m_comment);
}

void CDMDreamEdit2::SetJournal(IDreamJournal *j)
{
	m_journal = j;	
	OnUpdate();
}

void CDMDreamEdit2::Update()
{
	IDreamRecord *dream;
	if(m_journal && (dream = m_journal->GetSelected()))
	{
		m_dream.SetDream(dream);
		m_description.SetDescription(dream->GetDescription());
		m_comment.SetDescription(dream->GetComment());
		m_placelist.SetPlaceList(dream->GetPlaces(), m_journal);
	}
	else
	{
		Clear();
	}
	OnEnableBtns(0, 0);
}

void CDMDreamEdit2::Clear()
{
	m_dream.SetDream(NULL);
	m_placelist.SetPlaceList(NULL, m_journal);
	m_description.SetDescription(NULL);
	m_comment.SetDescription(NULL);
}

void CDMDreamEdit2::OnUpdate()
{
	if(m_hWnd)
		Update();
}

BOOL CDMDreamEdit2::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();


#ifndef _WIN32_WCE
	if(!m_toolbar.m_hWnd)
	{
		m_toolbar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_VISIBLE | CBRS_ALIGN_BOTTOM, CRect(0,0,0,0), IDW_DREAMBAR);
		m_toolbar.LoadToolBar(IDR_DREAMTOOLBAR);		
	}
#else
	if(!m_toolbar.m_hWnd)
	{		
		m_toolbar.Create(this);
		m_toolbar.ResetCommandBar();
		m_toolbar.LoadToolBar(IDR_DREAMTOOLBAR);
	}
	
	bModified = FALSE;
	Update();
#endif // _WIN32_WCE
	OnEnableBtns(0, 0);
	EnableNavigation();
	
	return bResult;
}

void CDMDreamEdit2::OnSize(UINT nType, int cx, int cy) 
{
	CPropertySheet::OnSize(nType, cx, cy);
#ifndef _WIN32_WCE
	CTabCtrl *tab = GetTabControl();
	if(tab && m_toolbar.m_hWnd) 
	{
		RECT rc;
		m_toolbar.GetItemRect(0, &rc);
		tab->MoveWindow(0, 0, cx, cy - rc.bottom + rc.top);
		m_toolbar.MoveWindow(0, cy - rc.bottom + rc.top, cx, rc.bottom - rc.top);
		CPropertyPage *page = GetActivePage();	
		if(page)
		{
			tab->GetClientRect(&rc);
			tab->AdjustRect(FALSE, &rc);
			page->MoveWindow(&rc);
		}		
	}
#endif
}

void CDMDreamEdit2::OnSave()
{
	BOOL bNew = FALSE;
	if(!m_journal)
		return;

	if(	!m_dream.IsModified() &&
		!m_description.IsModified() &&
		!m_comment.IsModified() &&
		!m_placelist.IsModified()
		)
		return;
		
	IDreamRecord *dream = m_journal->GetSelected();
	if(!dream)
	{
		int id = m_journal->Add();
		m_journal->SelectDreamPos(id);
		dream = m_journal->GetSelected();
		m_placelist.SetPlaceList(dream->GetPlaces(), m_journal);
		bNew = TRUE;
	}

	if(!dream)
		return;

	m_dream.GetDream(dream);
	dream->SetDescription(m_description.GetDescription());
	dream->SetComment(m_comment.GetDescription());

#ifndef _WIN32_WCE
	::SendMessage(m_psh.hwndParent, DMM_UPDATELIST, 1, 0);
#endif

	bModified = TRUE;

	m_dream.SetModified();
	m_description.SetModified();
	m_comment.SetModified();
	m_placelist.SetModified();

	OnEnableBtns(0, 0);

	if(bNew)
		EnableNavigation();
	return;
}

void CDMDreamEdit2::OnDmCancel()
{
	Update(); // просто перечитываем текущий сон или очищаем поля
	m_dream.SetModified();
	m_description.SetModified();
	m_comment.SetModified();
	OnEnableBtns(0, 0);
	return;
}

void CDMDreamEdit2::OnNew()
{
	if(!m_journal)
		return;
	RequestSave();
	m_journal->SelectDreamPos(-1);
	Clear();
	OnEnableBtns(0, 0);
	return;
}

void CDMDreamEdit2::OnDelete()
{
	if(!m_journal)
		return;
	
	int id = m_journal->GetSelectedPos();
	if(id >= 0)
	{
		CString t1, t2;
		t1.LoadString(IDS_QUESTION2);
		t2.LoadString(IDS_QUESTION3);
		if(MessageBox(t2, t1, MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			m_journal->Delete(id);
#ifndef _WIN32_WCE
			::SendMessage(m_psh.hwndParent, DMM_UPDATELIST, 1, 0);
#endif
			bModified = TRUE;
			Update();
		}
	}
	return;
}


void CDMDreamEdit2::OnFirst()
{
	if(!m_journal)
		return;
	RequestSave();
	m_journal->SelectDreamPos(0); //m_journal->GetFirstDreamID());
	Update();
#ifndef _WIN32_WCE
	::SendMessage(m_psh.hwndParent, DMM_UPDATELIST, 0, 0);
#endif
	EnableNavigation();
	return;
}

void CDMDreamEdit2::OnPrev()
{
	if(!m_journal)
		return;
	RequestSave();
	int id = m_journal->GetSelectedPos();
	if(id >= 0 && m_journal->GetDreamByPos(id-1))
	{
		m_journal->SelectDreamPos(id-1);
		Update();
#ifndef _WIN32_WCE
		::SendMessage(m_psh.hwndParent, DMM_UPDATELIST, 0, 0);
#endif
	}
	EnableNavigation();
	return;
}

void CDMDreamEdit2::OnNext()
{
	if(!m_journal)
		return;
	RequestSave();
	int id = m_journal->GetSelectedPos();
	if(id >= 0 && m_journal->GetDreamByPos(id+1))
	{
		m_journal->SelectDreamPos(id+1);
		Update();
#ifndef _WIN32_WCE
		::SendMessage(m_psh.hwndParent, DMM_UPDATELIST, 0, 0);
#endif
	}
	EnableNavigation();
	return;
}

void CDMDreamEdit2::OnLast()
{
	if(!m_journal)
		return;
	RequestSave();
	int id = m_journal->GetDreamsCount();
	m_journal->SelectDreamPos(id-1);
	Update();
#ifndef _WIN32_WCE
	::SendMessage(m_psh.hwndParent, DMM_UPDATELIST, 0, 0);
#endif
	EnableNavigation();
	return;
}


void CDMDreamEdit2::OnClose() 
{
	RequestSave();
	ShowWindow(SW_HIDE);
}

LRESULT CDMDreamEdit2::OnEnableBtns(WPARAM, LPARAM)
{
	if(!m_toolbar.m_hWnd)
		return 0;

	CToolBarCtrl &ctrl = m_toolbar.GetToolBarCtrl();

	if(	m_dream.IsModified() ||
		m_description.IsModified() ||
		m_comment.IsModified() ||
		m_placelist.IsModified()
		)
	{
		ctrl.EnableButton(ID_BUTTONSAVE, TRUE);
		ctrl.EnableButton(ID_BUTTONCANCEL, TRUE);
	}
	else
	{
		ctrl.EnableButton(ID_BUTTONSAVE, FALSE);
		ctrl.EnableButton(ID_BUTTONCANCEL, FALSE);
	}
	return 0;
}

void CDMDreamEdit2::RequestSave()
{	
	if(	m_dream.IsModified() ||
		m_description.IsModified() ||
		m_comment.IsModified() ||
		m_placelist.IsModified()
	  )
	{
		OnSave();
	}
}

void CDMDreamEdit2::EnableNavigation()
{
	if(!m_journal || !m_toolbar.m_hWnd)
		return;

	CToolBarCtrl &ctrl = m_toolbar.GetToolBarCtrl();
	int id = m_journal->GetSelectedPos();
	if(id >= 0)
	{
		BOOL isLast = !(id==m_journal->GetDreamsCount()-1);
		ctrl.EnableButton(ID_BUTTONFIRST, id);
		ctrl.EnableButton(ID_BUTTONPREV, id);
		ctrl.EnableButton(ID_BUTTONNEXT, isLast);
		ctrl.EnableButton(ID_BUTTONLAST, isLast);
	}
	else
	{
		ctrl.EnableButton(ID_BUTTONFIRST, FALSE);
		ctrl.EnableButton(ID_BUTTONPREV, FALSE);
		ctrl.EnableButton(ID_BUTTONNEXT, FALSE);
		ctrl.EnableButton(ID_BUTTONLAST, FALSE);
	}
}


BOOL CDMDreamEdit2::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (LOWORD(wParam) == IDOK)
	{
		bModified |= m_dream.IsModified()|m_description.IsModified()|m_comment.IsModified()|m_placelist.IsModified();
		RequestSave();
	}	
	return CPropertySheet::OnCommand(wParam, lParam);
}


BOOL CDMDreamEdit2::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CPropertySheet::PreTranslateMessage(pMsg);
}

int CDMDreamEdit2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}
