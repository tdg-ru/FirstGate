// DMDreamBar.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMDreamBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMDreamBar dialog


CDMDreamBar::CDMDreamBar(CWnd* pParent /*=NULL*/)
	: CDialog(CDMDreamBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDMDreamBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDMDreamBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMDreamBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMDreamBar, CDialog)
	//{{AFX_MSG_MAP(CDMDreamBar)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_FIRST, OnFirst)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_LAST, OnLast)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMDreamBar message handlers

void CDMDreamBar::OnSave() 
{
	CWnd *cw = GetParent();
	if(cw)
		cw->SendMessage(DMM_SAVE);
}



void CDMDreamBar::OnCancel() 
{
	CWnd *cw = GetParent();
	if(cw)
		cw->SendMessage(DMM_CANCEL);	
}

void CDMDreamBar::OnNew() 
{
	CWnd *cw = GetParent();
	if(cw)
		cw->SendMessage(DMM_NEW);	
}

void CDMDreamBar::OnFirst() 
{
	CWnd *cw = GetParent();
	if(cw)
		cw->SendMessage(DMM_FIRST);	
}

void CDMDreamBar::OnPrev() 
{
	CWnd *cw = GetParent();
	if(cw)
		cw->SendMessage(DMM_PREV);	
}

void CDMDreamBar::OnNext() 
{
	CWnd *cw = GetParent();
	if(cw)
		cw->SendMessage(DMM_NEXT);	
}

void CDMDreamBar::OnLast() 
{
	CWnd *cw = GetParent();
	if(cw)
		cw->SendMessage(DMM_LAST);
}
