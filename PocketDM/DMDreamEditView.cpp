// DMDreamEditView.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DMDreamEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEditView

IMPLEMENT_DYNCREATE(CDMDreamEditView, CFormView)

CDMDreamEditView::CDMDreamEditView()
	: CFormView(CDMDreamEditView::IDD)
{
	//{{AFX_DATA_INIT(CDMDreamEditView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDMDreamEditView::~CDMDreamEditView()
{
}

void CDMDreamEditView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMDreamEditView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMDreamEditView, CFormView)
	//{{AFX_MSG_MAP(CDMDreamEditView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEditView diagnostics

#ifdef _DEBUG
void CDMDreamEditView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDMDreamEditView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMDreamEditView message handlers
