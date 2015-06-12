// DMJournalView.cpp : implementation of the CDMJournalView class
//

#include "stdafx.h"
#include "DMJournal.h"

#include "DMJournalDoc.h"
#include "DMJournalView.h"

#include "DMPlaceEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMJournalView

IMPLEMENT_DYNCREATE(CDMJournalView, CView)

BEGIN_MESSAGE_MAP(CDMJournalView, CView)
	//{{AFX_MSG_MAP(CDMJournalView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(DMM_PLACELISTCH, OnPlaceListCh)
	ON_COMMAND(IDM_NEWPLACE, OnNewplace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMJournalView construction/destruction

CDMJournalView::CDMJournalView()
{
}

CDMJournalView::~CDMJournalView()
{
}

BOOL CDMJournalView::PreCreateWindow(CREATESTRUCT& cs)
{
#ifndef _WIN32_WCE
	cs.dwExStyle |= LVS_EX_GRIDLINES;
#endif

	cs.dwExStyle |= LVS_EX_FULLROWSELECT;


	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDMJournalView drawing

void CDMJournalView::OnDraw(CDC* pDC)
{
	/*
	CDMJournalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	*/
}

/////////////////////////////////////////////////////////////////////////////
// CDMJournalView diagnostics

#ifdef _DEBUG
void CDMJournalView::AssertValid() const
{
	CView::AssertValid();
}

void CDMJournalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDMJournalDoc* CDMJournalView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMJournalDoc)));
	return (CDMJournalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMJournalView message handlers

void CDMJournalView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	m_list.OnUpdate();
	Invalidate();
}

void CDMJournalView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if(m_list.m_hWnd)
		m_list.MoveWindow(0, 0, cx, cy);
}

BOOL CDMJournalView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	BOOL rez = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	
	if(rez)
	{
		RECT r;
		GetClientRect(&r);
		m_list.Create(WS_CHILD|WS_VISIBLE, r, this, 0);
		IPlaceList *pl = GetDocument()->m_journal.GetNewPlaces();		
		m_list.SetPList(pl);
	}
	return rez;
}

BOOL CDMJournalView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}


LRESULT CDMJournalView::OnPlaceListCh(WPARAM, LPARAM)
{
	GetDocument()->SetModifiedFlag();
	return 0;
}

void CDMJournalView::OnNewplace() 
{
	// TODO: Add your command handler code here
	CDMJournalDoc* pDoc = GetDocument();
	IPlaceList *pl = pDoc->m_journal.GetPlaces();
	if(pl)
	{
		CDMPlaceEdit edit(IDS_PLACEEDIT, this);
		pl->Select(-1);
		edit.SetPlaceList(pl);
		if(edit.DoModal() == IDOK)
		{
			OnUpdate(this, 0, 0);
			pDoc->SetModifiedFlag();
			pDoc->UpdateAllViews(this);			
		}
	}
}
