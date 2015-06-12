#if !defined(AFX_ZONEEDIT_H__90AC6FC9_FF14_4340_9BBA_871BD121F8CB__INCLUDED_)
#define AFX_ZONEEDIT_H__90AC6FC9_FF14_4340_9BBA_871BD121F8CB__INCLUDED_

#include "DMPlaceListSm.h"	// Added by ClassView
#include "DMDescriptionPage1.h"	// Added by ClassView
#include "DMPlacePage.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoneEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoneEdit

class CZoneEdit : public CPropertySheet
{
	DECLARE_DYNAMIC(CZoneEdit)

// Construction
public:
	CZoneEdit(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CZoneEdit(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoneEdit)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CZoneEdit();
	void SetPlaceList(IPlaceList *p);

	// Generated message map functions
protected:
	//{{AFX_MSG(CZoneEdit)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Update();
	CDMPlaceListSm m_plist;
	void InitPages();
/*
	CDMPlacePage m_place;
	CDMDescriptionPage m_description;
*/
	IPlaceList *m_placelist;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZONEEDIT_H__90AC6FC9_FF14_4340_9BBA_871BD121F8CB__INCLUDED_)
