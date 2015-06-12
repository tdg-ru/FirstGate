#if !defined(AFX_DMDESCRIPTIONPAGE1_H__1396D848_060D_44A5_99A0_84178837FFAC__INCLUDED_)
#define AFX_DMDESCRIPTIONPAGE1_H__1396D848_060D_44A5_99A0_84178837FFAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMDescriptionPage1.h : header file
//

#include "DMlib\\DMDescription.h"

/////////////////////////////////////////////////////////////////////////////
// CDMDescriptionPage dialog

class CDMDescriptionPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDMDescriptionPage)

// Construction
public:
	BOOL IsModified() { return bModified; } 
	void SetModified(BOOL b = FALSE) { bModified = b; } 
	const DMDescription * GetDescription();
	void SetDescription(const DMDescription *d);
	CDMDescriptionPage();
	~CDMDescriptionPage();

// Dialog Data
	//{{AFX_DATA(CDMDescriptionPage)
	enum { IDD = IDD_DESCRIPTION };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDMDescriptionPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDMDescriptionPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL bUpdate;
	BOOL bModified;
	DMDescription m_d;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMDESCRIPTIONPAGE1_H__1396D848_060D_44A5_99A0_84178837FFAC__INCLUDED_)
