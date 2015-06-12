#if !defined(AFX_DMDREMAEDIT_H__0FF6415A_8B19_4952_9765_B88A21B75B09__INCLUDED_)
#define AFX_DMDREMAEDIT_H__0FF6415A_8B19_4952_9765_B88A21B75B09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMDremaEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMDremaEdit form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDMDreamEdit : public CFormView
{
protected:
	CDMDremaEdit();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDMDremaEdit)

// Form Data
public:
	//{{AFX_DATA(CDMDremaEdit)
	enum { IDD = IDD_DREAMEDIT2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMDremaEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDMDremaEdit();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDMDremaEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMDREMAEDIT_H__0FF6415A_8B19_4952_9765_B88A21B75B09__INCLUDED_)
