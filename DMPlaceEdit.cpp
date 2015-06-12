// DMPlaceEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DMJournal.h"
#include "DMPlaceEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceEdit

IMPLEMENT_DYNAMIC(CDMPlaceEdit, CPropertySheet)

CDMPlaceEdit::CDMPlaceEdit(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
		InitPages(nIDCaption == IDS_ZONEEDIT);
}

CDMPlaceEdit::CDMPlaceEdit(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
		InitPages(FALSE);
}

CDMPlaceEdit::~CDMPlaceEdit()
{
}


BEGIN_MESSAGE_MAP(CDMPlaceEdit, CPropertySheet)
	//{{AFX_MSG_MAP(CDMPlaceEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_COMMAND(ID_BUTTONSAVE, OnBtnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMPlaceEdit message handlers

void CDMPlaceEdit::InitPages(BOOL isZone)
{
	m_plist = NULL;
	m_place.m_psp.dwFlags |= PSP_USETITLE;
	m_place.m_psp.dwFlags &= ~PSP_HASHELP;
	m_place.m_psp.pszTitle = (TCHAR *)((isZone)?IDS_ZONE:IDS_PLACE);

	m_description.m_psp.dwFlags |= PSP_USETITLE;
	m_description.m_psp.dwFlags &= ~PSP_HASHELP;
	m_description.m_psp.pszTitle = (TCHAR *)IDS_DESCRIPTION;

	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	m_psh.dwFlags &= ~PSH_HASHELP;	

	AddPage(&m_place);
	AddPage(&m_description);
}

void CDMPlaceEdit::SetPlaceList(IPlaceList *p)
{
	m_plist = p;
	m_place.SetPlaceList(p);

	IPlace *pl;
	if(p && (pl = p->GetSelected()))
	{
		m_description.SetDescription(pl->GetDescription());
	}
	else
	{
		m_description.SetDescription(NULL);
	}
}

BOOL CDMPlaceEdit::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (LOWORD(wParam) == IDOK)
	{
		if(m_plist)
		{
			CString str;			
			m_place.GetTitle(str);
			if(!str.IsEmpty())
			{
				IPlace *p = m_plist->GetSelected();
				if(!p)
				{
					int id = m_plist->Add();
					m_plist->Select(id);
					p = m_plist->GetPlace(id);
				}
				
				if(p)
				{		
					p->SetColor(m_place.GetColor());
					p->SetTitle(str);
					p->SetDescription(m_description.GetDescription());
				}
			}
		}
	}
	return CPropertySheet::OnCommand(wParam, lParam);
}


BOOL CDMPlaceEdit::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();
#ifdef _WIN32_WCE
	if(!m_toolbar.m_hWnd)
	{		
		m_toolbar.Create(this);
		m_toolbar.ResetCommandBar();
		m_toolbar.LoadToolBar(IDR_PLACETOOLBAR);
	}
#endif
	return bResult;
}

void CDMPlaceEdit::OnBtnOk()
{
	SendMessage(WM_COMMAND, IDOK, 0);
}