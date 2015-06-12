#if !defined(AFX_DMJOURNALLISTVIEW_H__814BACF4_4646_489A_AB88_580688A8A7B2__INCLUDED_)
#define AFX_DMJOURNALLISTVIEW_H__814BACF4_4646_489A_AB88_580688A8A7B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMJournalListView.h : header file
//

#include "DMJournalDoc.h"
#include "DMDreamEdit2.h"

/////////////////////////////////////////////////////////////////////////////
// CDMJournalListView view

class CDMJournalListView : public CListView
{
protected:
	DECLARE_DYNCREATE(CDMJournalListView)

// Attributes
public:
	CDMJournalListView();           // protected constructor used by dynamic creation
	CDMJournalDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMJournalListView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
	virtual ~CDMJournalListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDMJournalListView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnNew();
	afx_msg void OnView();
	afx_msg LRESULT OnListUpdate(WPARAM, LPARAM);
	afx_msg void OnItemactivate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CImageList *il;
	void TrackMenu(POINT&);
	CDMDreamEdit2 *m_editpage;
	void OnSelectItem(int n = -1);
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in DMJournalView.cpp
inline CDMJournalDoc* CDMJournalListView::GetDocument()
   { return (CDMJournalDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMJOURNALLISTVIEW_H__814BACF4_4646_489A_AB88_580688A8A7B2__INCLUDED_)
