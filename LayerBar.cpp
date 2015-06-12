// LayerBar.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "LayerBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerBar dialog


CLayerBar::CLayerBar()
	: CDialogBar()
{
	//{{AFX_DATA_INIT(CLayerBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_ys = 36;
}



BEGIN_MESSAGE_MAP(CLayerBar, CDialogBar)
	//{{AFX_MSG_MAP(CLayerBar)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayerBar message handlers

void CLayerBar::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
}


BOOL CLayerBar::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID) 
{
	BOOL rez = CDialogBar::Create(pParentWnd,  nIDTemplate, nStyle, nID);

	if(rez)
	{
		CComboBox *cw = (CComboBox*)GetDlgItem(IDC_LIST);
		if(cw)
		{
			CString str;
			str.LoadString(IDS_LAYER01); cw->AddString(str);
			str.LoadString(IDS_LAYER00); cw->AddString(str);
			str.LoadString(IDS_LAYER_1); cw->AddString(str);
			cw->SetCurSel(1);
		}
	}
	return rez;
}

CSize CLayerBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	if (bStretch) // if not docked stretch to fit
		return CSize(bHorz ? 32767 : m_sizeDefault.cx,
			bHorz ? m_ys : 32767);
	else
		return CSize(m_sizeDefault.cx, m_ys);

//	return CDialogBar::CalcFixedLayout(bStretch, bHorz);
}

void CLayerBar::OnSize(UINT nType, int cx, int cy) 
{
	CDialogBar::OnSize(nType, cx, cy);
	RECT rc, rc1;
	GetClientRect(&rc);

	CWnd *cw = GetDlgItem(IDC_LIST);
	if(!cw)
		return;

	cw->GetWindowRect(&rc1);
	ScreenToClient(&rc1);
	int h = (rc1.bottom - rc1.top) / 2;
	rc1.top = (rc.bottom - rc.top) / 2 - h;
	rc1.bottom = rc1.top + 2 * h;
	cw->MoveWindow(&rc1);
}

