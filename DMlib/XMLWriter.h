// XMLWriter.h: interface for the CXMLWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLWRITER_H__8CC18757_205C_427C_8181_A6DA403E2EC8__INCLUDED_)
#define AFX_XMLWRITER_H__8CC18757_205C_427C_8181_A6DA403E2EC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDreams.h"

class CXMLWriter : public IDreamWriter  
{
	int m_len;
	int	m_writed;
	CString m_str;
public:
	CXMLWriter(){ m_journal = NULL; m_len = m_writed = 0; }
	virtual ~CXMLWriter();

	virtual BOOL	BeginWrite(IDreamJournal *journal);
	virtual int		Write(void *buffer, int size);
	virtual int		Write(CString &str);
	virtual BOOL	IsEnd();
	virtual LPTSTR	GetErrorMessage(LPTSTR message, int max_len);
	virtual int		GetBufferSize();
};

#endif // !defined(AFX_XMLWRITER_H__8CC18757_205C_427C_8181_A6DA403E2EC8__INCLUDED_)
