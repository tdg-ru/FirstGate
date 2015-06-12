#include "DMxml.h"


const CString quotes[] = {	
	CString(_T("&amp;"), 5),  // 0
	CString(_T("&lt;"), 4),	  // 1
	CString(_T("&gt;"), 4),   // 2
	CString(_T("&quot;"), 6), // 3
	CString(_T("<p>"), 3),	  // 4
	CString(_T("</p>"), 4)    // 5

};

/*
LPCTSTR quotes[] = {	
	_T("&amp;"),
	_T("&lt;"),
	_T("&gt;"),
	_T("&quot;"),
	_T("<p>"),
	_T("</p>")
};
*/
#define NUMITEMS(x) (sizeof(x)/sizeof(*x))


LPCTSTR quotes_chrs= _T("&<>\"");
LPCTSTR quotesp_chrs= _T("&<>\"\n\r");

CString& DMxml::Quote(const CString &str, CString &rez)
{
	int i = 0, start = 0;
/*
	for(i = 0; i < str.GetLength(); i++)
	{
		int j;
		switch(str[i])
		{
		case '&': j = 0; break;
		case '<': j = 1; break;
		case '>': j = 2; break;
		case '\"': j = 3; break;
		default: continue;
		}

		rez += str.Mid(start, i - start);
		rez += quotes[j];
		start = i + 1;
	}
*/
	LPCTSTR buf = LPCTSTR(str);
	LPCTSTR pos;
	while((pos = _tcspbrk(buf + start, quotes_chrs)) != NULL)
	{
		int j;
		i = pos - buf;
		switch(buf[i])
		{
		case '&': j = 0; break;
		case '<': j = 1; break;
		case '>': j = 2; break;
		case '\"': j = 3; break;
		default: continue;
		}

		rez += str.Mid(start, i - start);
		rez += quotes[j];
		start = i + 1;
	}

	if(start)
		rez += str.Right(str.GetLength() - start);
	else
		rez += str;

	return rez;
}

CString& DMxml::QuoteP(const CString &str, CString &rez)
{
	int i, start = 0, p = 0;
	BOOL bOpenP = TRUE;
/*
	for(i = 0; i < str.GetLength(); i++)
	{
		int j;
		switch(str[i])
		{
		case '&': j = 0; break;
		case '<': j = 1; break;
		case '>': j = 2; break;
		case '\"': j = 3; break;
		case '\r': 
			{
				if(bOpenP)
				{
					rez += quotes[4];
					bOpenP = FALSE;
				}
				rez += str.Mid(start, i - start);
				rez += quotes[5];
				bOpenP = TRUE;
				start = i + 1;
				continue;
			}			
			break;
		
		case '\n': start++;
		default: continue;
		}

		if(bOpenP)
		{
			rez += quotes[4];
			bOpenP = FALSE;
		}
		rez += str.Mid(start, i - start);
		rez += quotes[j];
		start = i + 1;
	}
	rez += str.Right(i - start);
	if(!bOpenP)
		rez += quotes[5];
*/
	LPCTSTR buf = LPCTSTR(str);
	LPCTSTR pos;
	while((pos = _tcspbrk(buf + start, quotesp_chrs)) != NULL)
	{
		int j;
		i = pos - buf;
		switch(buf[i])
		{
		case '&': j = 0; break;
		case '<': j = 1; break;
		case '>': j = 2; break;
		case '\"': j = 3; break;
		case '\r': 
			{
				if(bOpenP)
				{
					rez += quotes[4];
					bOpenP = FALSE;
				}
				rez += str.Mid(start, i - start);
				rez += quotes[5];
				bOpenP = TRUE;
				start = i + 1;
				continue;
			}			
			break;
		
		case '\n': start++;
		default: continue;
		}

		if(bOpenP)
		{
			rez += quotes[4];
			bOpenP = FALSE;
		}
		rez += str.Mid(start, i - start);
		rez += quotes[j];
		start = i + 1;
	}

	if(bOpenP)
	{
		rez += quotes[4];
		bOpenP = FALSE;
	}
	if(start)
		rez += str.Right(str.GetLength() - start);
	else
		rez += str;

	rez += quotes[5];

	return rez;
}
