// PocketDM.h : main header file for the POCKETDM application
//

#if !defined(AFX_POCKETDM_H__18D2E085_5607_4B22_946A_D1E944486A03__INCLUDED_)
#define AFX_POCKETDM_H__18D2E085_5607_4B22_946A_D1E944486A03__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPocketDMApp:
// See PocketDM.cpp for the implementation of this class
//

class CPocketDMApp : public CWinApp
{
public:
	CPocketDMApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPocketDMApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPocketDMApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CPocketDMApp theApp;
extern BOOL bStarting;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POCKETDM_H__18D2E085_5607_4B22_946A_D1E944486A03__INCLUDED_)
