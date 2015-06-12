#if !defined(AFX_DMPLACELISTPAGE_H__93A35C86_E82D_49CE_8D33_076F8F9F7030__INCLUDED_)
#define AFX_DMPLACELISTPAGE_H__93A35C86_E82D_49CE_8D33_076F8F9F7030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMPlaceListPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListPage dialog
#include "DMPlaceListCtrl.h"
#include "DMPlaceListSm.h"
#include "DMlib\\IDreams.h"

class CDMPlaceListPage : public CDMPlaceListSm//public CPropertyPage
{
	DECLARE_DYNCREATE(CDMPlaceListPage)

// Construction
public:
//	BOOL IsModified() { return bModified; } 
//	void SetModified(BOOL b = FALSE) { bModified = b; } 
//	void Update();
	//void SetDream(IDreamRecord *d, IDreamJournal *j);
	void SetPlaceList(IPlaceList *d, IDreamJournal *j);
	CDMPlaceListPage();
	~CDMPlaceListPage();

// Dialog Data
	//{{AFX_DATA(CDMPlaceListPage)
	enum { IDD = IDD_PLACELIST };
	CButton	m_new;
	CComboBox	m_glist;
	CButton	m_delbtn;
	CButton	m_addbtn;
//	CDMPlaceListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDMPlaceListPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDMPlaceListPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnNew();
	afx_msg LRESULT OnPlaceListCh(WPARAM, LPARAM);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateGList();
//	BOOL bModified;
	//IDreamRecord *mp_dream;
//	IPlaceList *m_placelist;
	IDreamJournal *m_journal;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMPLACELISTPAGE_H__93A35C86_E82D_49CE_8D33_076F8F9F7030__INCLUDED_)
