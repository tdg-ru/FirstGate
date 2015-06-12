#if !defined(AFX_DMDREAMEDITVIEW_H__33D89F48_2453_4DC7_A219_5FC2670E4879__INCLUDED_)
#define AFX_DMDREAMEDITVIEW_H__33D89F48_2453_4DC7_A219_5FC2670E4879__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DMDreamEditView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEditView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDMDreamEditView : public CFormView
{
protected:
	CDMDreamEditView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDMDreamEditView)

// Form Data
public:
	//{{AFX_DATA(CDMDreamEditView)
	enum { IDD = IDD_DREAMEDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMDreamEditView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDMDreamEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDMDreamEditView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMDREAMEDITVIEW_H__33D89F48_2453_4DC7_A219_5FC2670E4879__INCLUDED_)
