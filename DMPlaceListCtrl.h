#if !defined(AFX_DMPLACELISTCTRL_H__94AA2E50_01A4_4760_8AE4_B055E2A3B9D6__INCLUDED_)
#define AFX_DMPLACELISTCTRL_H__94AA2E50_01A4_4760_8AE4_B055E2A3B9D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMPlaceListCtrl.h : header file
//

#include "DMlib\\IPlaceList.h"

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListCtrl window

class CDMPlaceListCtrl : public CListCtrl
{
// Construction
public:
	CDMPlaceListCtrl();

// Attributes
public:
	BOOL isZone;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMPlaceListCtrl)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitColumns();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void OnUpdate();
	virtual void SetPList(IPlaceList *l);
	virtual ~CDMPlaceListCtrl();

	// Generated message map functions
protected:
#if !defined(_WIN32_WCE)
	CImageList *m_pDragImage;
	BOOL m_bDragging;
	CWnd *m_pDropWnd;
	int m_nDragIndex;
#endif

	//{{AFX_MSG(CDMPlaceListCtrl)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemactivate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void OnSelectItem(int n = -1);
	void Update();
	IPlaceList *m_plist;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMPLACELISTCTRL_H__94AA2E50_01A4_4760_8AE4_B055E2A3B9D6__INCLUDED_)
