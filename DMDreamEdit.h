#if !defined(AFX_DMDREAMEDIT_H__62D83959_0498_41CB_AA39_654CF2710AD0__INCLUDED_)
#define AFX_DMDREAMEDIT_H__62D83959_0498_41CB_AA39_654CF2710AD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMDreamEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEdit form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "DMJournalDoc.h"

class CDMDreamEdit : public CFormView
{
	BOOL bChanged;
protected:
	CDMDreamEdit();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDMDreamEdit)

// Form Data
public:
	//{{AFX_DATA(CDMDreamEdit)
	enum { IDD = IDD_DREAMEDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CDMJournalDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMDreamEdit)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDMDreamEdit();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDMDreamEdit)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnApply();
	afx_msg void OnCancel();
	afx_msg void OnEditchangeType();
	afx_msg void OnNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Clear();
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in DMJournalView.cpp
inline CDMJournalDoc* CDMDreamEdit::GetDocument()
   { return (CDMJournalDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMDREAMEDIT_H__62D83959_0498_41CB_AA39_654CF2710AD0__INCLUDED_)
