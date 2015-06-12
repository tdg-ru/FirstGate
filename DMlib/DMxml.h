#ifndef DM_XML_H
#define DM_XML_H

#define __AFXSTATE_H__
#include <afx.h>         // MFC core and standard components


#ifdef _DEBUG
#define BEGIN_TO_STRING 	TCHAR *b = buf; int n, n_size = GetXMLBufferSize();
#else
#define BEGIN_TO_STRING 	TCHAR *b = buf; int n
#endif // _DEBUG


class DMxml
{
public:
	static CString& Quote(const CString &str, CString &rez);
	static CString& QuoteP(const CString &str, CString &rez);
	virtual void toString(CString &str) = 0;
	virtual int GetMinLength() = 0;
};

#endif //DM_XML_H