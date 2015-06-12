#if !defined(AFX_DMDREAMPAGE_H__E017EED5_968A_4031_BB06_C1C3B2C407CB__INCLUDED_)
#define AFX_DMDREAMPAGE_H__E017EED5_968A_4031_BB06_C1C3B2C407CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMDreamPage.h : header file
//

#include "DMlib\\IDreams.h"

/////////////////////////////////////////////////////////////////////////////
// CDMDreamPage dialog

class CDMDreamPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDMDreamPage)

// Construction
public:
	BOOL IsModified() { return bModified; } 
	void SetModified(BOOL b = FALSE) { bModified = b; } 
	void GetDream(IDreamRecord *dream);
	void Update();
	void SetDream(IDreamRecord *d);
	CDMDreamPage();
	~CDMDreamPage();

// Dialog Data
	//{{AFX_DATA(CDMDreamPage)
	enum { IDD = IDD_DREAM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDMDreamPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDMDreamPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditchange();
	virtual BOOL OnInitDialog();
	afx_msg void OnDatetimechangeDate(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL bModified;
	IDreamRecord *mp_dream;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMDREAMPAGE_H__E017EED5_968A_4031_BB06_C1C3B2C407CB__INCLUDED_)
