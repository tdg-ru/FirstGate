// DMJournalDoc.h : interface of the CDMJournalDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMJOURNALDOC_H__9D45A3B9_42C2_4134_B4A1_04C842D04742__INCLUDED_)
#define AFX_DMJOURNALDOC_H__9D45A3B9_42C2_4134_B4A1_04C842D04742__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DMlib\\IDreams.h"
#include "DMlib\\DreamJournal.h"

class CDMJournalDoc : public CDocument
{
public:
	CDreamJournalImp m_journal;
protected: // create from serialization only
	CDMJournalDoc();
	DECLARE_DYNCREATE(CDMJournalDoc)

// Attributes
public:

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMJournalDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDMJournalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDMJournalDoc)
	afx_msg void OnSave2xml();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMJOURNALDOC_H__9D45A3B9_42C2_4134_B4A1_04C842D04742__INCLUDED_)
