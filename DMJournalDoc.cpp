// DMJournalDoc.cpp : implementation of the CDMJournalDoc class
//

#include "stdafx.h"
#include "DMJournal.h"

#include "DMJournalDoc.h"
#include "DMlib\\ExpatXMLParser.h"
#include "DMlib\\XMLWriter.h"

#include "Zlib\\zlib.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMJournalDoc

IMPLEMENT_DYNCREATE(CDMJournalDoc, CDocument)

BEGIN_MESSAGE_MAP(CDMJournalDoc, CDocument)
	//{{AFX_MSG_MAP(CDMJournalDoc)
	ON_COMMAND(IDM_SAVEXML, OnSave2xml)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMJournalDoc construction/destruction

CDMJournalDoc::CDMJournalDoc()
{
	// TODO: add one-time construction code here
	CWinApp *app = AfxGetApp();
}

CDMJournalDoc::~CDMJournalDoc()
{
}

BOOL CDMJournalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if(!bStarting && MessageBox(AfxGetMainWnd( )->m_hWnd, _T("Создать карту по умолчанию?"), _T("Карта по умолчанию"), MB_YESNO|MB_ICONQUESTION) == IDNO)
		return TRUE;

	HMODULE hMod=AfxGetResourceHandle();
	HRSRC   hRes=FindResource(hMod, MAKEINTRESOURCE(IDR_DEFAULTFILE), _T("XML"));
	if (hRes) 
	{
		DWORD   rsize=SizeofResource(hMod,hRes);
		HGLOBAL hGlob=LoadResource(hMod,hRes);
		if (hGlob) 
		{
			void  *res=LockResource(hGlob);
			if (res) 
			{
				CExpatXMLParser parser;
				if(!parser.BeginRead(&m_journal))
				{			
					TCHAR str[255];
					TRACE(_T("%s\n"), parser.GetErrorMessage(str, 255));			
				}
				else
				{
					if(!parser.Read((char *)res, rsize))
					{
						TCHAR str[255];
						TRACE(_T("%s\n"), parser.GetErrorMessage(str, 255));
					}
					parser.EndRead();
				}
				UnlockResource(hGlob);
			}
			FreeResource(hGlob);
		}
	}
	UpdateAllViews(NULL, 0, 0);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDMJournalDoc serialization

void CDMJournalDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDMJournalDoc diagnostics

#ifdef _DEBUG
void CDMJournalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDMJournalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMJournalDoc commands

BOOL CDMJournalDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
/*
	CFileException  ex;
	CFile fp;
	
	if (!fp.Open(lpszPathName,CFile::modeRead|CFile::shareDenyWrite,&ex)) 
	{
		return false;
	}

	m_journal.DeleteAll();
	SetModifiedFlag(FALSE)
		;
	long len = fp.GetLength();
	char *buf = new char[len+1];	
	if(buf)
	{
		CExpatXMLParser parser;
		if(!parser.BeginRead(&m_journal))
		{			
			TCHAR str[255];
			TRACE(_T("%s\n"), parser.GetErrorMessage(str, 255));			
		}
		else
		{
			char *testXml = "<?xml version";
			w_char_t *testXmlU = L"<?xml version"
			int r = fp.Read(buf, 26);
			buf[26] = 0;
			if(memcmp(buf, testXml, min(13, r)) && memcmp(buf, testXmlU, min(26, r)))
			{
				// Это gzip файл???
				fp.Close();
				delete[] buf;
				buf = NULL;
				
				gzFile gz_f = gzopen(lpszPathName, "rb");

				if(!gz_f)
					return FALSE;


			}
			else
			{
				r += fp.Read(buf + 26, len - 26); // Дочитываем остаток файла
			}

			if(!parser.Read(buf, r))
			{
				TCHAR str[255];
				TRACE(_T("%s\n"), parser.GetErrorMessage(str, 255));
			}
			parser.EndRead();
		}
		delete[] buf;
	}
	else
	{
		return FALSE;
	}
*/
	m_journal.DeleteAll();
	SetModifiedFlag(FALSE);

#ifdef UNICODE
		char lpszPathNameCh[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, lpszPathName, _tcslen(lpszPathName) + 1, lpszPathNameCh, MAX_PATH, NULL, NULL);
		gzFile gz_f = gzopen(lpszPathNameCh, "rb");
#else
	gzFile gz_f = gzopen(lpszPathName, "rb");
#endif
	
	if(!gz_f)
		return FALSE;

	CExpatXMLParser parser;
	if(!parser.BeginRead(&m_journal))
	{			
		return FALSE;
	}

#define BUF_LEN 10000	
	char *buf = new char[BUF_LEN];

	int n = gzread(gz_f, buf, BUF_LEN);
	while(n > 0)
	{	
		parser.Read(buf, n);
		n = gzread(gz_f, buf, BUF_LEN);
	}
	parser.EndRead();
	gzclose(gz_f);
	delete[] buf;
#undef BUF_LEN
	
	return TRUE;
}

BOOL CDMJournalDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CXMLWriter writer;

	CString csName = lpszPathName;

#ifdef UNICODE
	char lpszPathNameCh[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, lpszPathName, _tcslen(lpszPathName)+1, lpszPathNameCh, MAX_PATH, NULL, NULL);
	gzFile gz_f = gzopen(lpszPathNameCh, "wb");
#else
	gzFile gz_f = gzopen(lpszPathName, "wb9");
#endif
	
	if(!gz_f)
		return FALSE;

	if(writer.BeginWrite(&m_journal))
	{

		CString buffer;
		int s = writer.Write(buffer);
				
		if(!gzwrite(gz_f, buffer.GetBuffer(buffer.GetLength()), buffer.GetLength() * sizeof(TCHAR)))
			return FALSE;
		SetModifiedFlag(FALSE);
	}
	else
		return FALSE;

	gzclose(gz_f);

	UpdateAllViews(NULL);
	return TRUE;
}

void CDMJournalDoc::DeleteContents() 
{
	m_journal.DeleteAll();
	SetModifiedFlag(FALSE);
}

BOOL CDMJournalDoc::SaveModified() 
{
#ifndef _WIN32_WCE	
	return CDocument::SaveModified();
#else
	if(IsModified())
		OnSaveDocument(GetPathName());
	return TRUE;
#endif
}



void CDMJournalDoc::OnSave2xml() 
{
	CFileDialog cf(FALSE, _T("xml"), GetTitle(), OFN_OVERWRITEPROMPT, _T("XML|*.xml|Все файлы|*.*||"), AfxGetMainWnd( ));
	if(cf.DoModal() == IDOK)
	{
		CFileException  ex;
		CFile fp;

		if (!fp.Open(cf.GetPathName(), CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite,&ex)) 
		{
			MessageBox(AfxGetMainWnd( )->m_hWnd, _T("Error saving file"), _T("Error"), MB_OK|MB_ICONERROR);
			return;
		}

		CXMLWriter writer;
		if(writer.BeginWrite(&m_journal))
		{

			CString buffer;
			int s = writer.Write(buffer);
			
			fp.Write(buffer, buffer.GetLength() * sizeof(TCHAR));
			SetModifiedFlag(FALSE);
		}
		else
		{
			MessageBox(AfxGetMainWnd( )->m_hWnd, _T("Error saving file"), _T("Error"), MB_OK|MB_ICONERROR);
			return;
		}
	}
}
