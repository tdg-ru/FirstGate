// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__3C63D5FC_C1DD_4272_B7F8_F7985C60560E__INCLUDED_)
#define AFX_MAINFRM_H__3C63D5FC_C1DD_4272_B7F8_F7985C60560E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DMJournalListView.h"
#include "DMJournalView.h"
#include "DMDreamEdit.h"
#include "DMMapView.h"
#include "LayerBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	void DockControlBarLeftOf(CControlBar* Bar,CControlBar* LeftOf);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	BOOL		m_bigicons;
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	m_wndMapBar;
	CToolBar	m_wndDreamBar;

//	CReBar      m_wndReBar;
	CDialogBar  m_wndDlgBar;
	CLayerBar   m_wndLayerBar;



	CDMJournalListView *m_pJournalView;
	CView			   *m_pPlaceListView;
	CDMMapView		   *m_pMapView;

public:
	CImageList *il_main; 
	CImageList *il_map; 
	CImageList *il_dream, *il_dream_d;
	

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnTab();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLayerCh();
	afx_msg void OnNewDream();
	afx_msg void OnBigicons();
	afx_msg void OnZoneeditr();
	afx_msg void OnNewzone();
	afx_msg void OnGridonoff();
	afx_msg void OnNewplace();
	afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetTab(int i);
	BOOL LoadBars();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3C63D5FC_C1DD_4272_B7F8_F7985C60560E__INCLUDED_)
