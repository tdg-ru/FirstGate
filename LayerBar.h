#if !defined(AFX_LAYERBAR_H__D6290279_AF09_4AE9_AB4F_FE3C96C832DD__INCLUDED_)
#define AFX_LAYERBAR_H__D6290279_AF09_4AE9_AB4F_FE3C96C832DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayerBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayerBar dialog

class CLayerBar : public CDialogBar
{
// Construction
public:
	void SetYS(int ys){ m_ys = ys; }
	CLayerBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLayerBar)
	enum { IDD = IDD_LAYERBAR };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayerBar)
	public:
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
    virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLayerBar)
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_ys;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERBAR_H__D6290279_AF09_4AE9_AB4F_FE3C96C832DD__INCLUDED_)
