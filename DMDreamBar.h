#if !defined(AFX_DMDREAMBAR_H__E46A08D7_8FCF_4352_99F1_C747A47E68E8__INCLUDED_)
#define AFX_DMDREAMBAR_H__E46A08D7_8FCF_4352_99F1_C747A47E68E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMDreamBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMDreamBar dialog

class CDMDreamBar : public CDialog
{
// Construction
public:
	CDMDreamBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDMDreamBar)
	enum { IDD = IDD_DREAMBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMDreamBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDMDreamBar)
	afx_msg void OnSave();
	afx_msg void OnCancel();
	afx_msg void OnNew();
	afx_msg void OnFirst();
	afx_msg void OnPrev();
	afx_msg void OnNext();
	afx_msg void OnLast();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMDREAMBAR_H__E46A08D7_8FCF_4352_99F1_C747A47E68E8__INCLUDED_)
