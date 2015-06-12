// ExpatXMLParser.h: interface for the CExpatXMLParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPATXMLPARSER_H__D7BAFF56_E1CD_4EEA_99AA_81CEAA8F6CB8__INCLUDED_)
#define AFX_EXPATXMLPARSER_H__D7BAFF56_E1CD_4EEA_99AA_81CEAA8F6CB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <tchar.h>
#include "IDreams.h"
#include "..\\expat\\winconfig.h"
#include "..\\expat\\expat.h"


#include "unicode.h"

#include <stack>

using namespace std;

class CExpatXMLParser : public IDreamParser  
{
	static int	m_utf8enc;
	XML_Parser	m_parser;	
	
	stack<int> m_s;
	DWORD m_flags;
	CString m_str;
	
	int m_last_id;
	int m_last_place_id;
	int m_last_layer_id;

	OwnerInfo owner;
	
	void StartElement(const XML_Char *el, const XML_Char **attr);
	void EndElement(const XML_Char *el);
	void CharacterData(const XML_Char *s, int len);

	static void StartElementCB(void *data, const XML_Char *el, const XML_Char **attr);
	static void EndElementCB   (void *data, const XML_Char *el);
	static void CharacterDataCB(void *data, const XML_Char *s, int len);
	static void CDataStartCB(void *data);
	static void CDataEndCB(void *data);
	static int UnknownEncodingCB(void *data,const XML_Char *name, XML_Encoding *info);

	static CString FromXMLChar(const XML_Char *s){	return FromXMLChar(s, _tcslen(s));}

#ifndef UNICODE
	static CString FromXMLChar(const XML_Char *s, int len)
	{
		return  Unicode::ToCS(m_utf8enc, s, len);
	}
#else
	static CString FromXMLChar(const XML_Char *s, int len)
	{
		return CString(s, len);
	}
#endif 
	void ReadAttr(const XML_Char **attr, int *a, CString *na, int n);
public:	
	int	m_encoding;
	CExpatXMLParser();
	virtual ~CExpatXMLParser();

	virtual BOOL	BeginRead(IDreamJournal *journal); // Начало чтения
	virtual BOOL	Read(const char *data, int size);  // 
	virtual void	EndRead();
	virtual LPTSTR	GetErrorMessage(LPTSTR message, int max_len);
};

#endif // !defined(AFX_EXPATXMLPARSER_H__D7BAFF56_E1CD_4EEA_99AA_81CEAA8F6CB8__INCLUDED_)
