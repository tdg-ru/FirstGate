// DMJournalView.h : interface of the CDMJournalView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMJOURNALVIEW_H__9E838DD3_F7F1_45AC_83B4_491CAB185BAD__INCLUDED_)
#define AFX_DMJOURNALVIEW_H__9E838DD3_F7F1_45AC_83B4_491CAB185BAD__INCLUDED_

#include "DMPlaceListCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDMJournalView : public CView
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CDMJournalView)

// Attributes
public:
	CDMJournalView();
	CDMJournalDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMJournalView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDMJournalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDMJournalView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnPlaceListCh(WPARAM, LPARAM);
	afx_msg void OnNewplace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDMPlaceListCtrl m_list;
};

#ifndef _DEBUG  // debug version in DMJournalView.cpp
inline CDMJournalDoc* CDMJournalView::GetDocument()
   { return (CDMJournalDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMJOURNALVIEW_H__9E838DD3_F7F1_45AC_83B4_491CAB185BAD__INCLUDED_)
