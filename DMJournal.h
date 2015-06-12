// DMJournal.h : main header file for the DMJOURNAL application
//

#if !defined(AFX_DMJOURNAL_H__65A8A598_A35F_44DC_9813_E7B8679E9622__INCLUDED_)
#define AFX_DMJOURNAL_H__65A8A598_A35F_44DC_9813_E7B8679E9622__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "MainFrm.h"



/////////////////////////////////////////////////////////////////////////////
// CDMJournalApp:
// See DMJournal.cpp for the implementation of this class
//

class CDMJournalApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMainFrame *m_mainframe;
	CDMJournalApp();

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMJournalApp)
	public:
	virtual BOOL InitInstance();	

	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDMJournalApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CDMJournalApp theApp;
extern BOOL bStarting;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMJOURNAL_H__65A8A598_A35F_44DC_9813_E7B8679E9622__INCLUDED_)
