#if !defined(AFX_DMPLACELISTBOX_H__F7F8D95D_2C1A_4F64_83B7_46946E461420__INCLUDED_)
#define AFX_DMPLACELISTBOX_H__F7F8D95D_2C1A_4F64_83B7_46946E461420__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMPlaceListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceListBox window

#include "DMlib\\IPlaceList.h"

class CDMPlaceListBox : public CListBox
{
// Construction
public:
	CDMPlaceListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMPlaceListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnUpdate(){Update();};
	virtual void SetPList(IPlaceList *l);
	virtual ~CDMPlaceListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDMPlaceListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void Update();
	IPlaceList *m_plist;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMPLACELISTBOX_H__F7F8D95D_2C1A_4F64_83B7_46946E461420__INCLUDED_)
