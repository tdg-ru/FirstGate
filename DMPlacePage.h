#if !defined(AFX_DMPLACEPAGE_H__60A42FAF_8DB2_4BA4_A23E_2551C67452D0__INCLUDED_)
#define AFX_DMPLACEPAGE_H__60A42FAF_8DB2_4BA4_A23E_2551C67452D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMPlacePage.h : header file
//
#include "DMlib\\IPlaceList.h"

/////////////////////////////////////////////////////////////////////////////
// CDMPlacePage dialog

class CDMPlacePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDMPlacePage)

// Construction
public:
	void GetTitle(CString &str);
	COLORREF GetColor();
	COLORREF m_c;
	void SetPlaceList(IPlaceList *p);
	CDMPlacePage();
	~CDMPlacePage();

// Dialog Data
	//{{AFX_DATA(CDMPlacePage)
	enum { IDD = IDD_PLACEEDIT };
	CEdit	m_title;
	CButton	m_color;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDMPlacePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDMPlacePage)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnColor();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	IPlaceList* m_plist;

#if defined _WIN32_WCE
	HINSTANCE hLib;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMPLACEPAGE_H__60A42FAF_8DB2_4BA4_A23E_2551C67452D0__INCLUDED_)
