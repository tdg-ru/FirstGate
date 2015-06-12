// DMPlaceListPage.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMPlaceListPage.h"
#include "DMPlaceEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListPage property page

IMPLEMENT_DYNCREATE(CDMPlaceListPage, CPropertyPage)

CDMPlaceListPage::CDMPlaceListPage() : CDMPlaceListSm(CDMPlaceListPage::IDD)//CPropertyPage(CDMPlaceListPage::IDD)
{
	//{{AFX_DATA_INIT(CDMPlaceListPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bModified = FALSE;
//	mp_dream = NULL;
	m_placelist = NULL;
	m_journal = NULL;
}

CDMPlaceListPage::~CDMPlaceListPage()
{
}

void CDMPlaceListPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMPlaceListPage)
	DDX_Control(pDX, IDC_NEW, m_new);
	DDX_Control(pDX, IDC_GLOBALLIST, m_glist);
	DDX_Control(pDX, IDC_DELETE, m_delbtn);
	DDX_Control(pDX, IDC_ADD, m_addbtn);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMPlaceListPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDMPlaceListPage)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_MESSAGE(DMM_PLACELISTCH, OnPlaceListCh)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListPage message handlers

BOOL CDMPlaceListPage::OnInitDialog() 
{
	CDMPlaceListSm::OnInitDialog();
	
	// TODO: Add extra initialization here
/*
	m_list.InitColumns();
	Update();
*/
#ifndef _WIN32_WCE
	HICON hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ADD), IMAGE_ICON, 0, 0, LR_LOADMAP3DCOLORS);
	m_addbtn.SetIcon(hIco);
	hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DEL), IMAGE_ICON, 16, 16, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
	m_delbtn.SetIcon(hIco);
	hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_NEW), IMAGE_ICON, 16, 16, LR_CREATEDIBSECTION);
	m_new.SetIcon(hIco);
#endif

	if(!m_journal || !m_placelist)
	{
		m_addbtn.EnableWindow(FALSE);
		m_delbtn.EnableWindow(FALSE);
		m_new.EnableWindow(FALSE);
	}
	else
	{
		m_addbtn.EnableWindow(TRUE);
		m_delbtn.EnableWindow(TRUE);
		m_new.EnableWindow(TRUE);	
	}

	UpdateGList();

	/*
	DWORD dwExStyle = m_list.GetExtendedStyle();
#ifndef _WIN32_WCE
		dwExStyle |= LVS_EX_GRIDLINES;
#endif
	m_list.SetExtendedStyle(dwExStyle|LVS_EX_FULLROWSELECT);
	*/


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDMPlaceListPage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	if(m_hWnd && m_list.m_hWnd)
	{
		RECT rc, rc2;
		m_addbtn.GetWindowRect(&rc);
		m_glist.GetUpdateRect(&rc2);

#ifndef _WIN32_WCE		
		int h = 20; //rc.bottom - rc.top;
		//int x1 = rc2.right - rc2.left;
		int x2 = 20;//rc.right - rc.left;
		int x1 = 100;
#else
		int h = 20;
		int x2 = 20;
		int x1 = 180;
#endif
		m_list.MoveWindow(0, 0, cx, cy - h - 1);	
		m_glist.MoveWindow(0, cy-h, x1, 200);
		m_new.MoveWindow(x1+1, cy-h, x2, h);		
		m_addbtn.MoveWindow(x1 + x2 + 1, cy - h, x2, h);
		m_delbtn.MoveWindow(x1 + 2*x2 + 1, cy - h, x2, h);
		
	}
}

/*
void CDMPlaceListPage::Update()
{
	if(!m_placelist || !m_list.m_hWnd)
	{
		m_list.SetPList(NULL);
		return;
	}
	m_list.SetPList(m_placelist);
}
*/

void CDMPlaceListPage::SetPlaceList(IPlaceList *d, IDreamJournal *j)
{
	m_placelist = d;
	m_journal = j;
	Update();
	SetModified();

	if(m_addbtn.m_hWnd)
	{
		if(!m_journal || !m_placelist)
		{
			m_addbtn.EnableWindow(FALSE);
			m_delbtn.EnableWindow(FALSE);
			m_new.EnableWindow(FALSE);
		}
		else
		{
			m_addbtn.EnableWindow(TRUE);
			m_delbtn.EnableWindow(TRUE);
			m_new.EnableWindow(TRUE);	
		}	
	}
}

void CDMPlaceListPage::OnAdd() 
{
	if(!m_journal || !m_placelist)
		return;
	int n = m_glist.GetCurSel();
	int id = m_glist.GetItemData(n);

	IPlaceList *pl = m_journal->GetPlaces();
	if(!pl)
		return;
	IPlace *p = pl->GetPlace(id);
	if(!p)
		return;

	m_placelist->Add(p);	
	Update();
	SetModified(TRUE);
	GetParent()->SendMessage(DMM_DREAMMODIFIED, 0, 0);
}

void CDMPlaceListPage::OnDelete() 
{
	if(!m_placelist)
		return;
	int id = m_placelist->GetSelectedID();
	m_placelist->Delete(id);
	Update();
	SetModified(TRUE);
	GetParent()->SendMessage(DMM_DREAMMODIFIED, 0, 0);
}

void CDMPlaceListPage::OnNew() 
{
	if(m_placelist)
	{
		CDMPlaceEdit edit(IDS_PLACEEDIT, this);
		//IPlaceList *p = mp_dream->GetPlaces(); /*m_journal->GetPlaces()*/
		m_placelist->Select(-1);
		edit.SetPlaceList(m_placelist);
		if(edit.DoModal() == IDOK)
		{
			Update();
			UpdateGList();
			SetModified(TRUE);
			GetParent()->SendMessage(DMM_DREAMMODIFIED, 0, 0);
		}
	}
}

void CDMPlaceListPage::UpdateGList()
{
	m_glist.SetRedraw(FALSE);
	m_glist.ResetContent();
	if(m_journal)
	{
		IPlaceList *pl = m_journal->GetPlaces();
		if(pl)	
		{
			for(int i = 0; i < pl->GetCount(); i++)
			{
				IPlace *p = pl->GetPlaceByPos(i);
				if(p)
				{
					int n = m_glist.AddString(p->GetTitle());
					m_glist.SetItemData(n, p->GetID());
				}
			}
		}
	}
	m_glist.SetRedraw(TRUE);
}

LRESULT CDMPlaceListPage::OnPlaceListCh(WPARAM, LPARAM)
{
	UpdateGList();
	SetModified(TRUE);
	GetParent()->SendMessage(DMM_DREAMMODIFIED, 0, 0);
	return 0;
}

void CDMPlaceListPage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	HICON hIco;
	switch(nIDCtl)
	{
	case IDC_ADD:
		hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ADD), IMAGE_ICON, 16, 16, 0);
		break;
	case IDC_DELETE:
		hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DEL), IMAGE_ICON, 16, 16, 0);
		break;
	case IDC_NEW:
		hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_NEW), IMAGE_ICON, 16, 16, 0);
		break;
	default:
		CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
		return;
	}


	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	if((lpDrawItemStruct->itemAction&ODA_SELECT) && (lpDrawItemStruct->itemState&ODS_SELECTED))
	{
		CBrush br(RGB(0,0,0));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(255,255,255));
		dc.FrameRect(&lpDrawItemStruct->rcItem, &br);
	}
	else
	{
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_BTNFACE));
	}

	dc.DrawIcon(2, 2, hIco);
	dc.Detach();
}

