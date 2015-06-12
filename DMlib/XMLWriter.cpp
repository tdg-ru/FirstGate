// XMLWriter.cpp: implementation of the CXMLWriter class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "XMLWriter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXMLWriter::~CXMLWriter()
{

}

BOOL	CXMLWriter::BeginWrite(IDreamJournal *journal)
{
	if(!journal)
		return FALSE;
	
//	CString tmp;
	m_journal = journal;
	m_journal->SortByDate(FALSE);

	m_str = _T("");

/*	
#ifdef _UNICODE
	m_str += _T("<?xml version=\"1.0\" encoding=\"UTF-16\"?>\r\n");
#else 
	m_str += _T("<?xml version=\"1.0\" encoding=\"windows-1251\"?>\r\n");
#endif
	m_str += _T("<!DOCTYPE Dreams SYSTEM \"dream.dtd\">\r\n<Dreams version=\"0.1\">\r\n");
	m_journal->toString(m_str);
	m_str += tmp;

	m_str += _T("</Dreams>\r\n");

	m_len = m_str.GetLength();
	m_writed = 0;
*/
	return TRUE;
}

int	CXMLWriter::Write(void *buffer, int size)
{
	int w = min(size, m_len-m_writed);
	memcpy(buffer, (LPCTSTR)(m_str.Right(m_len - m_writed)), w * sizeof(TCHAR));
	m_writed += w;
	return w;
}

int	CXMLWriter::Write(CString &str)
{
	m_str = _T("");
	int min_len = m_journal->GetMinLength() + 120;
	str.GetBuffer(min_len);
	
#ifdef _UNICODE
	str = _T("<?xml version=\"1.0\" encoding=\"UTF-16\"?>\r\n");
#else 
	str = _T("<?xml version=\"1.0\" encoding=\"windows-1251\"?>\r\n");
#endif
	str += _T("<!DOCTYPE Dreams SYSTEM \"dream.dtd\">\r\n<Dreams version=\"0.1\">\r\n");
	m_journal->toString(str);
	str += _T("</Dreams>\r\n");
	m_len = str.GetLength();
	m_writed = m_len;
	return m_len; 
}

BOOL	CXMLWriter::IsEnd()
{
	return (m_writed >= m_len);
}

LPTSTR	CXMLWriter::GetErrorMessage(LPTSTR message, int max_len)
{
	return message;
}

int	CXMLWriter::GetBufferSize() 
{ 
	int min_len = m_journal->GetMinLength() + 120;
	m_str.GetBuffer(min_len);
#ifdef _UNICODE
	m_str += _T("<?xml version=\"1.0\" encoding=\"UTF-16\"?>\r\n");
#else 
	m_str += _T("<?xml version=\"1.0\" encoding=\"windows-1251\"?>\r\n");
#endif
	m_str += _T("<!DOCTYPE Dreams SYSTEM \"dream.dtd\">\r\n<Dreams version=\"0.1\">\r\n");
	

	m_journal->toString(m_str);
	m_str += _T("</Dreams>\r\n");
	m_len = m_str.GetLength();
	m_writed = 0;
	return m_len; 
}
