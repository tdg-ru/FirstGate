#if !defined(AFX_DMPLACEEDIT_H__68E8B2F0_FC2E_4533_AFD6_345CA367E634__INCLUDED_)
#define AFX_DMPLACEEDIT_H__68E8B2F0_FC2E_4533_AFD6_345CA367E634__INCLUDED_

#include "DMDescriptionPage1.h"	// Added by ClassView
#include "DMPlacePage.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMPlaceEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceEdit

class CDMPlaceEdit : public CPropertySheet
{
	DECLARE_DYNAMIC(CDMPlaceEdit)

// Construction
public:
	CDMPlaceEdit(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDMPlaceEdit(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMPlaceEdit)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetPlaceList(IPlaceList *p);
	virtual ~CDMPlaceEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDMPlaceEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnBtnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitPages(BOOL isZone);
	CDMPlacePage m_place;
	CDMDescriptionPage m_description;
	IPlaceList *m_plist;

#if defined _WIN32_WCE	
	CCeCommandBar m_toolbar;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMPLACEEDIT_H__68E8B2F0_FC2E_4533_AFD6_345CA367E634__INCLUDED_)
