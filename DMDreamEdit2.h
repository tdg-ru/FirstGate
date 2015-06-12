#if !defined(AFX_DMDREAMEDIT2_H__292153C9_9881_4A5A_B2DE_F6649AD57E42__INCLUDED_)
#define AFX_DMDREAMEDIT2_H__292153C9_9881_4A5A_B2DE_F6649AD57E42__INCLUDED_

#include "DMDreamPage.h"	// Added by ClassView
#include "DMDescriptionPage1.h"	// Added by ClassView
#include "DMPlaceListPage.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMDreamEdit2.h : header file
//

#include "DMlib\\IDreams.h"
#include "DMDreamBar.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEdit2

class CDMDreamEdit2 : public CPropertySheet
{
	DECLARE_DYNAMIC(CDMDreamEdit2)

// Construction
public:
	CDMDreamEdit2(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDMDreamEdit2(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	BOOL bModified;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMDreamEdit2)
	public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnUpdate();
	void SetJournal(IDreamJournal *j);
	virtual ~CDMDreamEdit2();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDMDreamEdit2)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSave();
	afx_msg void OnDmCancel();
	afx_msg void OnFirst();
	afx_msg void OnPrev();
	afx_msg void OnNext();
	afx_msg void OnLast();
	afx_msg void OnNew();
	afx_msg void OnDelete();
	afx_msg LRESULT OnEnableBtns(WPARAM, LPARAM);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:	
	void EnableNavigation();
	void RequestSave();
	void Clear();
	void Update();
	IDreamJournal *m_journal;
	void InitPages();

#if defined _WIN32_WCE	
	CCeCommandBar m_toolbar;
#else
	CToolBar m_toolbar;
#endif
	CDMDreamPage m_dream;
	CDMDescriptionPage m_description;
	CDMDescriptionPage m_comment;
	CDMPlaceListPage m_placelist;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMDREAMEDIT2_H__292153C9_9881_4A5A_B2DE_F6649AD57E42__INCLUDED_)
