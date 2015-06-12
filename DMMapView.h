#if !defined(AFX_DMMAPVIEW_H__D9DC72AB_32D4_4E0A_B4F7_06343AD7B0B8__INCLUDED_)
#define AFX_DMMAPVIEW_H__D9DC72AB_32D4_4E0A_B4F7_06343AD7B0B8__INCLUDED_

#include "ZoneEdit.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMMapView.h : header file
//

#include "DMJournalDoc.h"
#include "MapLayer.h"

/////////////////////////////////////////////////////////////////////////////
// CDMMapView view

class CDMMapView : public CScrollView
{
	int m_layer_id;
	int m_size;	
	BOOL m_bGrid;
protected:

	CDMMapView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDMMapView)

// Attributes
public:
	CDMJournalDoc* GetDocument();

// Operations
public:
	void SetLayer(int id);
	void MovePlace(int id);
	CImageList *CreateDragImage(IPlace *);
	void AddPlace(int id);
	CMapLayer * m_layer;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMMapView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	//}}AFX_VIRTUAL

// Implementation
protected:
#if !defined(_WIN32_WCE)
	CImageList *m_pDragImage;
	BOOL m_bDragging;
	CWnd *m_pDropWnd;
	int m_nDragIndex;
#endif

	void BeginDrag();

	virtual ~CDMMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDMMapView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnZoomout();
	afx_msg void OnZoomin();
	afx_msg void OnView();
	afx_msg void OnDelete();
	afx_msg void OnMove();
	afx_msg BOOL OnMouseWheel(UINT fFlags, short zDelta, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSetzone();
	afx_msg void OnNewzone();
	afx_msg void OnDelzone();
	afx_msg void OnZoneEditR();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGridOnOff();
	afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
#if !defined _WIN32_WCE	
	CToolTipCtrl m_ToolTip;
#endif
	CZoneEdit m_zoneeditor;
	void Zoom(int new_size);
	void TrackMenu(POINT &point);
};

#ifndef _DEBUG  // debug version in DMJournalView.cpp
inline CDMJournalDoc* CDMMapView::GetDocument()
   { return (CDMJournalDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMMAPVIEW_H__D9DC72AB_32D4_4E0A_B4F7_06343AD7B0B8__INCLUDED_)
