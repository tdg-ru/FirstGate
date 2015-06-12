// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DMJournal.h"

#include "MainFrm.h"
#include "DMJournalListView.h"
#include "DMJournalView.h"
#include "DMDreamEdit.h"
#include "DMMapView.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelTab)
	ON_COMMAND(IDM_ZOOMIN, OnZoomin)
	ON_COMMAND(IDM_ZOOMOUT, OnZoomout)
	ON_COMMAND(IDM_TAB, OnTab)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_LIST, OnLayerCh)
	ON_COMMAND(IDM_NEW, OnNewDream)
	ON_COMMAND(IDM_BIGICONS, OnBigicons)
	ON_COMMAND(IDM_ZONEEDITR, OnZoneeditr)
	ON_COMMAND(IDM_NEWZONE, OnNewzone)
	ON_COMMAND(IDM_GRIDONOFF, OnGridonoff)
	ON_UPDATE_COMMAND_UI(IDW_MAPBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(IDW_MAPBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(IDW_DIALOGBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(IDW_DIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(IDW_DREAMBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(IDW_DREAMBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(IDW_LAYERBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(IDW_LAYERBAR, OnBarCheck)
	ON_COMMAND(IDM_NEWPLACE, OnNewplace)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()	

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


CString csSection = _T("Windows");

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_mainframe = this;	

	il_map = NULL;
	il_main = NULL;
	il_dream = NULL;
	il_dream_d = NULL;
	m_bigicons = TRUE;
}

CMainFrame::~CMainFrame()
{
	delete il_dream_d;
	delete il_dream;
	delete il_map;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_bigicons = theApp.GetProfileInt(csSection, _T("Icons"), 1);

 	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_GRIPPER|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndDreamBar.CreateEx(this, TBSTYLE_FLAT, CBRS_GRIPPER|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|WS_VISIBLE, CRect(0,0,0,0), IDW_DREAMBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}	
	if (!m_wndMapBar.CreateEx(this, TBSTYLE_FLAT, CBRS_GRIPPER|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|WS_VISIBLE, CRect(0,0,0,0), IDW_MAPBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}	
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_GRIPPER|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|WS_VISIBLE, IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
	if (!m_wndLayerBar.Create(this, IDD_LAYERBAR, 
		CBRS_GRIPPER|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|WS_VISIBLE, IDW_LAYERBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	CTabCtrl *tab = (CTabCtrl*)m_wndDlgBar.GetDlgItem(IDC_TAB);
	if(tab)
	{
		CString str;
		str.LoadString(IDS_DREAMJOURNAL);
		tab->InsertItem(0, str);
		str.LoadString(IDS_DREAMMAP);
		tab->InsertItem(1, str);
		tab->SetCurSel(1);
	}

	if(!LoadBars())
		return -1;


	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDreamBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMapBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDlgBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndLayerBar.EnableDocking(CBRS_ALIGN_ANY);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndToolBar);
	DockControlBarLeftOf(&m_wndDreamBar, &m_wndToolBar);
	DockControlBarLeftOf(&m_wndMapBar, &m_wndDreamBar);
	DockControlBar(&m_wndDlgBar);
	DockControlBarLeftOf(&m_wndLayerBar, &m_wndMapBar);

	LoadBarState(_T("Settings\\ControlBar"));

	CSize sz = m_wndToolBar.CalcFixedLayout(FALSE, TRUE);
	m_wndLayerBar.SetYS(sz.cy);

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(TRUE, this);

	SetTab(theApp.GetProfileInt(csSection, _T("DefView"), 1));
	return 0;
}

void CMainFrame::DockControlBarLeftOf(CControlBar* Bar, CControlBar* LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	CString csSection = _T("Windows");
	CString csItem  = _T("MainFrame");

	RECT* rc;
    UINT n;
    BOOL ret = theApp.GetProfileBinary(csSection, csItem, (LPBYTE*)&rc, &n);
	if(ret)
	{
		if(n == sizeof(RECT))
		{
			cs.x = rc->left;
			cs.y = rc->top;
			cs.cx = rc->right - rc->left;
			cs.cy = rc->bottom - rc->top;
		}
		delete [] rc;
	}

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	// create splitter window

	if (!m_wndSplitter.CreateStatic(this, 1, 2, WS_CHILD|WS_VISIBLE))
		return FALSE;
	
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDMJournalView), CSize(300, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CDMMapView), CSize(300, 100), pContext)
	   )
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	m_pPlaceListView = (CView*)m_wndSplitter.GetPane(0,0);
	m_pMapView		 = (CDMMapView*)m_wndSplitter.GetPane(0,1);

	UINT viewID = AFX_IDW_PANE_FIRST+100;
	CRect rect(0, 0, 0, 0); 

	m_pJournalView = new CDMJournalListView();
	m_pJournalView->Create(NULL, _T("AnyWindowName"), WS_CHILD, rect, this, viewID, pContext);

	int bGrid = theApp.GetProfileInt(csSection, _T("Grid"), 1);
	if(!bGrid)
		OnGridonoff();

//	CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

void CMainFrame::OnSelTab(NMHDR* pNMHDR, LRESULT* pResult) 
{

	CTabCtrl *tab = (CTabCtrl*)m_wndDlgBar.GetDlgItem(IDC_TAB);
	if(tab)
	{
		int i = tab->GetCurSel();
		switch(i)
		{
		case 0: /* Дневник сновидений */
#ifndef _WIN32
			::SetWindowWord(m_pPlaceListView->m_hWnd, GWW_ID, AFX_IDW_PANE_FIRST+100);
			::SetWindowWord(m_pJournalView->m_hWnd, GWW_ID, AFX_IDW_PANE_FIRST);
#else
			::SetWindowLong(m_pPlaceListView->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST+100);
			::SetWindowLong(m_pJournalView->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST);
#endif
			m_wndSplitter.ShowWindow(SW_HIDE);
			m_pJournalView->ShowWindow(SW_SHOW);		
			SetActiveView(m_pJournalView);
			RecalcLayout();
			break;

		case 1: /* Карта сновиденного мира */
#ifndef _WIN32
			::SetWindowWord(m_pPlaceListView->m_hWnd, GWW_ID, AFX_IDW_PANE_FIRST);
			::SetWindowWord(m_pJournalView->m_hWnd, GWW_ID, AFX_IDW_PANE_FIRST+100);
#else
			::SetWindowLong(m_pPlaceListView->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST);
			::SetWindowLong(m_pJournalView->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST+100);
#endif
			m_pJournalView->ShowWindow(SW_HIDE);		
			m_wndSplitter.ShowWindow(SW_SHOW);
			m_wndSplitter.RecalcLayout();
			SetActiveView(m_pPlaceListView);
			RecalcLayout();
			break;
		}

	}
	*pResult = 0;
}

void CMainFrame::OnZoomin() 
{
	m_pMapView->SendMessage(WM_COMMAND, IDM_ZOOMIN, 0);
}

void CMainFrame::OnZoomout() 
{
	m_pMapView->SendMessage(WM_COMMAND, IDM_ZOOMOUT, 0);	
}

void CMainFrame::OnTab() 
{
	SetTab(-1);
}

void CMainFrame::OnClose() 
{
	RECT rc;

	if(!IsIconic() && !IsZoomed())
	{
		GetWindowRect(&rc);
		theApp.WriteProfileBinary(csSection, _T("MainFrame"), (LPBYTE)&rc, sizeof(rc));		
	}

	theApp.WriteProfileInt(csSection, _T("Icons"), m_bigicons);

	CTabCtrl *tab = (CTabCtrl*)m_wndDlgBar.GetDlgItem(IDC_TAB);
	if(tab)
	{
		int i = tab->GetCurSel();
		theApp.WriteProfileInt(csSection, _T("DefView"), i);
	}


	theApp.WriteProfileInt(csSection, _T("Grid"), ((GetMenu()->GetMenuState(IDM_GRIDONOFF, MF_BYCOMMAND)&MF_CHECKED) != 0));

	SaveBarState(_T("Settings\\ControlBar"));

	
	CFrameWnd::OnClose();
}

void CMainFrame::OnLayerCh() 
{
	int n = ((CComboBox*)(m_wndLayerBar.GetDlgItem(IDC_LIST)))->GetCurSel();
	int n_layer_id = 0;
	switch(n)
	{
	case 0: n_layer_id = 1; break;
	case 1: n_layer_id = 0; break;
	case 2: n_layer_id = -1; break;
	}

	m_pMapView->SetLayer(n_layer_id);
}

void CMainFrame::OnNewDream() 
{
	SetTab(0);
	m_pJournalView->SendMessage(WM_COMMAND, WPARAM(IDM_NEW), 0);
}

void CMainFrame::OnBigicons() 
{	
	if(m_bigicons)
		m_bigicons = FALSE;
	else
		m_bigicons = TRUE;

	LoadBars();
}

BOOL CMainFrame::LoadBars()
{
	int bars_id[6];
	CMenu *menu = GetMenu();	
	if(m_bigicons)
	{
		bars_id[0] = IDR_MAINFRAME;
		bars_id[1] = IDR_DREAMBAR;
		bars_id[2] = IDB_DREAMBAR256D;
		bars_id[3] = IDR_MAPTOOLBAR;
		bars_id[4] = IDB_DREAMBAR256;
		bars_id[5] = IDB_MAPTOOLBAR256;
		menu->CheckMenuItem(IDM_BIGICONS, MF_CHECKED);
	}
	else
	{
		bars_id[0] = IDR_MAINFRAME_SM;
		bars_id[1] = IDR_DREAMBAR_SM;
		bars_id[2] = IDB_DREAMBARD_SM;	
		bars_id[3] = IDR_MAPTOOLBAR_SM;	
		bars_id[4] = IDB_DREAMBAR256SM;
		bars_id[5] = IDB_MAPTOOLBAR256SM;
		menu->CheckMenuItem(IDM_BIGICONS, MF_UNCHECKED);
	}

	if(m_wndToolBar.LoadToolBar(bars_id[0]))
	{
		CToolBarCtrl &ctrl = m_wndToolBar.GetToolBarCtrl();
		il_main = ctrl.GetImageList();
	}
	else
		return FALSE;

	if(m_wndDreamBar.LoadToolBar(bars_id[1]))
	{
		HBITMAP hbmd = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
					MAKEINTRESOURCE(bars_id[2]),
					IMAGE_BITMAP,
					0,0, // cx, cy
					LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );

		HBITMAP hbm = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
					MAKEINTRESOURCE(bars_id[4]),
					IMAGE_BITMAP,
					0,0, // cx, cy
					LR_CREATEDIBSECTION);

		CBitmap bm, bmd;
		bm.Attach(hbm);
		bmd.Attach(hbmd);

		if(il_dream_d)
			delete il_dream_d;
		if(il_dream)
			delete il_dream;

		il_dream_d = new CImageList();
		il_dream = new CImageList();
		if(m_bigicons)
		{
			il_dream_d->Create(32, 32, ILC_COLORDDB, 0, 2);
			il_dream->Create(32, 32, ILC_COLORDDB, 0, 2);
		}
		else
		{
			il_dream_d->Create(16, 16, ILC_COLORDDB, 0, 2);
			il_dream->Create(16, 16, ILC_COLORDDB, 0, 2);
		}

		il_dream->Add(&bm, (CBitmap*)NULL);
		il_dream_d->Add(&bmd, (CBitmap*)NULL);
		CToolBarCtrl &ctrl = m_wndDreamBar.GetToolBarCtrl();
		ctrl.SetDisabledImageList(il_dream_d);
		ctrl.SetImageList(il_dream);
		//il_dream = ctrl.GetImageList();
	}
	else
		return FALSE;

	if(m_wndMapBar.LoadToolBar(bars_id[3]))
	{

		HBITMAP hbm = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
			MAKEINTRESOURCE(bars_id[5]),
			IMAGE_BITMAP,
			0,0, // cx, cy
			LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );

		CBitmap bm;
		bm.Attach(hbm);

		if(il_map)
			delete il_map;

		il_map = new CImageList();
		if(m_bigicons)
			il_map->Create(32, 32, ILC_COLORDDB, 0, 5);
		else	
			il_map->Create(16, 16, ILC_COLORDDB, 0, 5);
		il_map->Add(&bm, (CBitmap*)NULL);
		CToolBarCtrl &ctrl = m_wndMapBar.GetToolBarCtrl();
		ctrl.SetImageList(il_map);
		//il_map = ctrl.GetImageList();	
	}
	else
		return FALSE;

	CSize sz = m_wndToolBar.CalcFixedLayout(FALSE, TRUE);
	m_wndLayerBar.SetYS(sz.cy);

	RecalcLayout();

	return TRUE;
}

void CMainFrame::OnZoneeditr() 
{
	// TODO: Add your command handler code here
	CTabCtrl *tab = (CTabCtrl*)m_wndDlgBar.GetDlgItem(IDC_TAB);
	int i = tab->GetCurSel();
	if(!i)
	{
		tab->SetCurSel(1);
		LRESULT rez;
		OnSelTab(NULL, &rez);
	}
	m_pMapView->SendMessage(WM_COMMAND, WPARAM(IDM_ZONEEDITR), 0);	
}

void CMainFrame::OnNewzone() 
{
	// TODO: Add your command handler code here
	SetTab(1);
	m_pMapView->SendMessage(WM_COMMAND, WPARAM(IDM_NEWZONE), 0);		
}

void CMainFrame::OnGridonoff() 
{
	// TODO: Add your command handler code here
	m_pMapView->SendMessage(WM_COMMAND, WPARAM(IDM_GRIDONOFF), 0);
}

void CMainFrame::OnNewplace() 
{
	// TODO: Add your command handler code here
	m_pPlaceListView->SendMessage(WM_COMMAND, WPARAM(IDM_NEWPLACE), 0);	
}

void CMainFrame::SetTab(int id)
{
	if(id > 1)
		return;
	CTabCtrl *tab = (CTabCtrl*)m_wndDlgBar.GetDlgItem(IDC_TAB);
	if(tab)
	{
		int i = tab->GetCurSel();
		if(id < 0)
			id = (!i);
		if(i != id)
		{
			tab->SetCurSel(id);
			LRESULT rez;
			OnSelTab(NULL, &rez);
		}
	}
}


BOOL CMainFrame::OnToolTipText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	*pResult = m_pMapView->SendMessage(WM_NOTIFY, TTN_NEEDTEXT, (LPARAM)pNMHDR);
	return TRUE;
	//m_pMapView->OnToolTipText(id, pNMHDR, pResult);
}
