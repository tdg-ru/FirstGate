#if !defined(AFX_DMPLACELISTSM_H__5B3DCFBF_5CAD_4FEA_B4AB_97100886C4B2__INCLUDED_)
#define AFX_DMPLACELISTSM_H__5B3DCFBF_5CAD_4FEA_B4AB_97100886C4B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMPlaceListSm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListSm dialog

class CDMPlaceListSm : public CPropertyPage
{
	DECLARE_DYNCREATE(CDMPlaceListSm)

// Construction
public:
	BOOL IsModified() { return bModified; } 
	void SetModified(BOOL b = FALSE) { bModified = b; } 
	void Update();
	void SetPlaceList(IPlaceList *d);
	CDMPlaceListSm(int idd);
	CDMPlaceListSm();
	~CDMPlaceListSm();

// Dialog Data
	//{{AFX_DATA(CDMPlaceListSm)
	enum { IDD = IDD_PLACELIST2 };
	CDMPlaceListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDMPlaceListSm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDMPlaceListSm)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	BOOL bModified;
	IPlaceList *m_placelist;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMPLACELISTSM_H__5B3DCFBF_5CAD_4FEA_B4AB_97100886C4B2__INCLUDED_)
