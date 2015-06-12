// ExpatXMLParser.cpp: implementation of the CExpatXMLParser class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "DreamRecord.h"
#include "ExpatXMLParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define NUMITEMS(x) (sizeof(x)/sizeof(*x))

enum DM_TAGS
{
	DMT_DREAMS=1,
	DMT_JOURNAL,
	DMT_OWNER,
	DMT_FIRST,
	DMT_MIDDLE,
	DMT_LAST,
	DMT_NICK,
	DMT_EMAIL,
	DMT_DREAM,
	DMT_TITLE,
	DMT_DATE,
	DMT_TYPE,
	DMT_DESCRIPTION,
	DMT_P,
	DMT_COMMENT,
	DMT_LOCALITY,
	DMT_MAP,
	DMT_LAYER,
	DMT_PLACE,
	DMT_ZONE,
	DMT_PNT
};

struct TTag
{
	int id;
	TCHAR *name;
};

struct TType
{
	int id;
	char *name;
};


TTag knownTags[] = 
{
	{DMT_DREAMS,	_T("Dreams")},
	{DMT_JOURNAL,	_T("journal")},	
	{DMT_OWNER,		_T("owner")},
	{DMT_FIRST,		_T("first-name")},
	{DMT_MIDDLE,	_T("middle-name")},
	{DMT_LAST,		_T("last-name")},
	{DMT_NICK,		_T("nick")},
	{DMT_EMAIL,		_T("email")},
	{DMT_DREAM,		_T("dream")},
	{DMT_TITLE,		_T("title")},
	{DMT_DATE,		_T("date")},
	{DMT_TYPE,		_T("type")},
	{DMT_DESCRIPTION,_T("description")},
	{DMT_P,			_T("p")},
	{DMT_COMMENT,	_T("comment")},
	{DMT_LOCALITY,	_T("locality")},
	{DMT_MAP,		_T("dream-map")},
	{DMT_LAYER,		_T("layer")},
	{DMT_PLACE,		_T("place")},
	{DMT_ZONE,		_T("zone")},
	{DMT_PNT,		_T("pnt")}
};

#ifdef UNICODE
TCHAR delirious_loop[] =	{1073,1088,1077,1076,1086,1074,1072,1103,32,1087,1077,1090,1083,1103, 0};
TCHAR speach[] =			{49,48,48,37,45,1103,32,1073,1086,1083,1090,1086,1074,1085,1103, 0};
TCHAR action[] =			{1089,1086,1085,32,1089,32,1101,1083,1077,1084,1077,1085,1090,1072,1084,1080,32,1076,1077,1081,1089,1090,1074,1080,1103,0};
TCHAR lucid[] =				{1087,1088,1086,1079,1088,1072,1095,1085,1086,1077,32,1089,1085,1086,1074,1080,1076,1077,1085,1080,1077, 0};
TCHAR oc_dream[] =			{1054,1057, 0};
#else
TCHAR *delirious_loop =	"бредовая петля";
TCHAR *speach =			"100%-я болтовня";
TCHAR *action =			"сон с элементами действия";
TCHAR *lucid =			"прозрачное сновидение";
TCHAR *oc_dream =		"ОС";
#endif

TTag knownTypes[] =
{
	{DREAM_DELIRIOUS_LOOP,	delirious_loop	},
	{DREAM_SPEACH,			speach			},
	{DREAM_ACTION,			action			},
	{DREAM_LUCID,			lucid			},
	{DREAM_OC,				oc_dream		}
};


#define DM_XML_IN_JOURNAL		0x1
#define DM_XML_IN_DREAM			0x2
#define DM_XML_IN_PLACE			0x4
#define DM_XML_IN_MAPLAYER		0x8
#define DM_XML_IN_ZONE			0x10

int GetID(const CString &s)
{
	for(int i = 0; i < NUMITEMS(knownTags); i++)
	{
		if(!s.CompareNoCase(knownTags[i].name))
		{
			return knownTags[i].id;
		}
	}
	return -1;
}

DM_DREAM_TYPE GetTypeID(CString &s)
{
	for(int i = 0; i < DM_DREAM_TYPE_CNT; i++)
	{
/*
		CString str;
		str = Unicode::ToCS(Unicode::DefaultCodePage(), ty[i], strlen(ty[i]));
*/
		if(!s.CompareNoCase(knownTypes[i].name))
		{
			return (DM_DREAM_TYPE)knownTypes[i].id;
		}
	}
	return DREAM_UNKNOWN;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int	CExpatXMLParser::m_utf8enc;

#define BAD_LAYER_ID (-10 * DM_LAYERS_DOWN)

CExpatXMLParser::CExpatXMLParser()
{
	m_utf8enc = Unicode::FindCodePage(_T("UTF-8"));
	m_str = "";
	m_flags = 0;
	m_last_layer_id = BAD_LAYER_ID;
}

CExpatXMLParser::~CExpatXMLParser()
{

}

void CExpatXMLParser::StartElementCB(void *data, const XML_Char *el, const XML_Char **attr)
{
	((CExpatXMLParser*)data)->StartElement(el, attr);	
}

void CExpatXMLParser::EndElementCB(void *data, const XML_Char *el)
{
	((CExpatXMLParser*)data)->EndElement(el);
}

void CExpatXMLParser::CharacterDataCB(void *data, const XML_Char *s, int len)
{
	((CExpatXMLParser*)data)->CharacterData(s, len);
}


void CExpatXMLParser::CDataStartCB(void *data)
{
	TRACE(_T("CDats START\n"));
}

void CExpatXMLParser::CDataEndCB(void *data)
{
	TRACE(_T("CDats END\n"));
}

void CExpatXMLParser::CharacterData(const XML_Char *s, int len)
{	
	// удаляем лишние пробелы и концы строк
	CString str = FromXMLChar(s, len);
	CString st;

	//MessageBox(NULL, str, _T("str"), MB_OK);
	BOOL last_chr = (m_str.GetLength()>0) && (m_str[m_str.GetLength()-1] != ' ');

	TCHAR *sa = st.GetBufferSetLength(str.GetLength());	
	int i, j = 0;
	for(i = 0; i < str.GetLength(); i++)
	{
		TCHAR ch = str[i];
		if(ch == '\n'||ch=='\t'||ch=='\r')
			ch = ' ';

		if(ch != ' ' || (j && str[i-1] != ' ') || (!j && last_chr))
			sa[j++] = ch;
	}
	sa[j] = 0;
	st.ReleaseBuffer(j);

	if(!st.IsEmpty())
	{
		m_str += st;
	}
}

void CExpatXMLParser::ReadAttr(const XML_Char **attr, int *a, CString *na, int n)
{
	int i = 0;
	while(attr[i])
	{
		CString attr_cs = FromXMLChar(attr[i]);
		for(int j = 0; j < n; j++)
		{
			if(!attr_cs.CompareNoCase(na[j])) 
			{					
				_stscanf(FromXMLChar(attr[i+1]), _T("%d"), &(a[j]));
			}
		}
		i += 2;
	}
}

void CExpatXMLParser::StartElement(const XML_Char *el, const XML_Char **attr)
{		
	int i = 0;
	int id = GetID(FromXMLChar(el));
	
	if(id <= 0)	// Неизвестные теги пропускаем
		return;

	switch(id)
	{
	case DMT_JOURNAL: 
		m_flags |= DM_XML_IN_JOURNAL; 
		break;
	case DMT_DREAM:
		{
			m_flags |= DM_XML_IN_DREAM;
			m_last_id = m_journal->Add();
			break;
		}
	case DMT_DATE:
	{
		CString attr_cs = FromXMLChar(attr[0]);
		if(!attr_cs.CompareNoCase(_T("value")))
		{
			DMDate d;
			attr_cs = FromXMLChar(attr[1]);
			IDreamRecord *dream = m_journal->GetDreamByPos(m_last_id);
			_stscanf(attr_cs, _T("%d-%d-%d"), &d.year, &d.month, &d.day);
			d.hour   = 0;
			d.minute = 0;
			dream->SetDate(&d);
		}
		break;		
	}
	case DMT_PLACE:
		{
			m_flags |= DM_XML_IN_PLACE;
			m_last_place_id = -1;
			int r = 0, g = 0, b = 0, i = 0;
			while(attr[i])
			{
				CString attr_cs = FromXMLChar(attr[i]);
				if(!attr_cs.CompareNoCase(_T("id"))) 
				{ 
					_stscanf(FromXMLChar(attr[i+1]), _T("%6d"), &m_last_place_id); 					
				}
				else
				{
					if(!attr_cs.CompareNoCase(_T("color"))) 
					{
						_stscanf(FromXMLChar(attr[i+1]), _T("#%2x%2x%2x"), &r, &g, &b);
					}
				}
				i += 2;
			}
			if(m_flags&DM_XML_IN_DREAM)
			{
				IPlaceList *pl = m_journal->GetDreamByPos(m_last_id)->GetPlaces();
				pl->Add(m_last_place_id);
				IPlace *p = pl->GetPlace(m_last_place_id);
				p->SetColor(RGB(r,g,b));
			}
			else
			{
				IPlaceList *pl = m_journal->GetPlaces();
				pl->Add(m_last_place_id);
				IPlace *p = pl->GetPlace(m_last_place_id);
				p->SetColor(RGB(r,g,b));
			}
		}
		break;
	case DMT_MAP:
		{
			int h = 300, w = 300, i = 0;
			while(attr[i])
			{
				CString attr_cs = FromXMLChar(attr[i]);
				if(!attr_cs.CompareNoCase(_T("width"))) 
				{ 
					_stscanf(FromXMLChar(attr[i+1]), _T("%d"), &w); 					
				}
				else
				{
					if(!attr_cs.CompareNoCase(_T("height"))) 
					{
						_stscanf(FromXMLChar(attr[i+1]), _T("%d"), &h);
					}
				}
				i += 2;
			}
			m_journal->SetMapSize(w, h);
		}
		break;
	case DMT_LAYER:
		{
			m_last_layer_id = BAD_LAYER_ID;
			int i = 0;
			while(attr[i])
			{
				CString attr_cs = FromXMLChar(attr[i]);
				if(!attr_cs.CompareNoCase(_T("id"))) 
				{					
					_stscanf(FromXMLChar(attr[i+1]), _T("%d"), &m_last_layer_id);
				}
				i += 2;
			}
			if(m_last_layer_id >= -DM_LAYERS_DOWN && m_last_layer_id <= DM_LAYERS_UP)
			{
				m_flags |= DM_XML_IN_MAPLAYER;
			}
			else
			{
				m_last_layer_id = BAD_LAYER_ID;
				m_flags &= (~DM_XML_IN_MAPLAYER);
			}
		}
		break;
	case DMT_LOCALITY:
		{
			int id, x, y, i = 0;
			while(attr[i])
			{
				CString attr_cs = FromXMLChar(attr[i]);
				if(!attr_cs.CompareNoCase(_T("id"))) 
				{					
					_stscanf(FromXMLChar(attr[i+1]), _T("%d"), &id);
				}
				if(!attr_cs.CompareNoCase(_T("x"))) 
				{					
					_stscanf(FromXMLChar(attr[i+1]), _T("%d"), &x);
				}
				if(!attr_cs.CompareNoCase(_T("y"))) 
				{					
					_stscanf(FromXMLChar(attr[i+1]), _T("%d"), &y);
				}
				i += 2;
			}
			if((m_flags & DM_XML_IN_MAPLAYER) && (m_last_layer_id != BAD_LAYER_ID))
			{
				IMapLayer *ml = m_journal->GetLayer(m_last_layer_id);
				if(ml)
					ml->Add(id, x, y);

			}
		}
		break;
	case DMT_ZONE:
		{
			m_flags |= DM_XML_IN_ZONE;
			int r = 0, g = 0, b = 0, i = 0;
			while(attr[i])
			{
				CString attr_cs = FromXMLChar(attr[i]);
				if(!attr_cs.CompareNoCase(_T("id"))) 
				{ 
					_stscanf(FromXMLChar(attr[i+1]), _T("%6d"), &m_last_place_id); 					
				}
				else
				{
					if(!attr_cs.CompareNoCase(_T("color"))) 
					{
						_stscanf(FromXMLChar(attr[i+1]), _T("#%2x%2x%2x"), &r, &g, &b);
					}
				}
				i += 2;
			}
			IPlaceList *pl = m_journal->GetZones()->GetPlaces();
			IPlace *p = pl->GetPlace(m_last_place_id);
			if(!p)	pl->Add(m_last_place_id);
			p = pl->GetPlace(m_last_place_id);
			if(p)
			{
				p->SetColor(RGB(r,g,b));
			}
		}
		break;
	case DMT_PNT:
		if(m_flags & DM_XML_IN_MAPLAYER)
		{
			IZoneList *zl = m_journal->GetZones();
			if(zl)
			{
				int pnt[3];
				CString na[] = {CString(_T("id")), CString(_T("x")), CString(_T("y"))};
				ReadAttr(attr, pnt, na, 3);
				if(!zl->GetPlaces()->GetPlace(pnt[0]))				
				{
					zl->GetPlaces()->Add(pnt[0]);
				}
				zl->Add(pnt[0], m_last_layer_id, pnt[1], pnt[2]);
			}
		}
		break;
	}	
	m_s.push(id);
}

void CExpatXMLParser::EndElement(const XML_Char *el)
{
	int id = GetID(FromXMLChar(el));

	/*
	TCHAR str[255];
	_stprintf(str, _T("%d - <%s>"), id, FromXMLChar(el));
	MessageBox(NULL, m_str, str, MB_OK);
	*/

	if(id <= 0)	// Неизвестные теги пропускаем
		return;
	
	if(!m_str.IsEmpty())
	{
		switch(id)
		{
		case DMT_P:
			// Закончился очередной абзац. 
			m_str += "\r\n";
			break;
		case DMT_DESCRIPTION:
			if(m_flags&DM_XML_IN_DREAM) // Описание последнего сна
			{
				DMDescription d;
				d.SetText(m_str);
				IDreamRecord *dream = m_journal->GetDreamByPos(m_last_id);
				dream->SetDescription(&d);
				break;
			}
			if(m_flags&DM_XML_IN_PLACE)
			{
				if(m_last_place_id != -1)
				{
					IPlace *p;
					DMDescription d;
					d.SetText(m_str);
					if(m_flags&DM_XML_IN_DREAM)
					{
						p = m_journal->GetDreamByPos(m_last_id)->GetPlaces()->GetPlace(m_last_place_id);
					}
					else
					{
						p = m_journal->GetPlaces()->GetPlace(m_last_place_id);
					}

					if(p)
					{
						p->SetDescription(&d);
					}
				}
				break;
			}
			if(m_flags&DM_XML_IN_ZONE)
			{
				if(m_last_place_id != -1)
				{
					IPlace *p = m_journal->GetZones()->GetPlaces()->GetPlace(m_last_place_id);
					if(p)
					{
						DMDescription d;
						d.SetText(m_str);
						p->SetDescription(&d);
					}
				}				
			}
			break;
		case DMT_COMMENT:
			if(m_flags&DM_XML_IN_DREAM) // Комментарий
			{
				DMDescription d;
				d.SetText(m_str);
				IDreamRecord *dream = m_journal->GetDreamByPos(m_last_id);
				dream->SetComment(&d);
			}
			break;
		case DMT_TITLE:
			if(m_flags&DM_XML_IN_PLACE)
			{
				if(m_last_place_id != -1)
				{
					IPlace *p;
					if(m_flags&DM_XML_IN_DREAM)
						p = m_journal->GetDreamByPos(m_last_id)->GetPlaces()->GetPlace(m_last_place_id);
					else
						p = m_journal->GetPlaces()->GetPlace(m_last_place_id);

					if(p)
					{
						p->SetTitle(m_str);
					}
				}
				break;
			}
			else
			{
				if(m_flags&DM_XML_IN_DREAM)
				{
					IDreamRecord *dream = m_journal->GetDreamByPos(m_last_id);
					dream->SetTitle(m_str);
					break;
				}

				if(m_flags&DM_XML_IN_ZONE)
				{
					if(m_last_place_id != -1)
					{
						IPlace *p = m_journal->GetZones()->GetPlaces()->GetPlace(m_last_place_id);
						if(p)
						{
							p->SetTitle(m_str);
						}
					}				
				}
			}
			break;
		case DMT_TYPE:
			if(m_flags&DM_XML_IN_DREAM)
			{
				IDreamRecord *dream = m_journal->GetDreamByPos(m_last_id);
				dream->SetExtType(m_str);
				dream->SetType(GetTypeID(m_str));
			}
			break;
		case DMT_FIRST:		
			owner.SetFirstName(m_str);
			break;
		case DMT_MIDDLE:		
			owner.SetMiddleName(m_str);
			break;
		case DMT_LAST:		
			owner.SetLastName(m_str);
			break;
		case DMT_NICK:		
			owner.SetNick(m_str);
			break;
		case DMT_EMAIL:		
			owner.SetEmail(m_str);
			break;
		}
	}
	else
	{
		switch(id)
		{
		case DMT_DREAM:
			m_flags &= (~DM_XML_IN_DREAM);
			break;
		case DMT_JOURNAL:
			m_flags &= (~DM_XML_IN_JOURNAL);
			break;
		case DMT_OWNER:
			m_journal->SetOwnerInfo(owner);
			break;
		case DMT_PLACE:
			m_flags &= (~DM_XML_IN_PLACE);
			m_last_place_id = -1;
			break;
		case DMT_LAYER:
			m_last_layer_id = BAD_LAYER_ID;
			m_flags &= (~DM_XML_IN_MAPLAYER);
			break;
		case DMT_ZONE:
			m_flags &= (~DM_XML_IN_ZONE);
		}
	}
	m_s.pop();

	if(id != DMT_P)
		m_str="";
}

int CExpatXMLParser::UnknownEncodingCB(void *data,const XML_Char *name, XML_Encoding *info)
{
	int	cp=Unicode::FindCodePage(FromXMLChar(name));
	const wchar_t	*tab=NULL;
	if (cp>=0)
		tab=Unicode::GetTable(cp);
	if (!tab)
		return 0;
	info->data=NULL;
	info->convert=NULL;
	info->release=NULL;
	for (int i=0;i<256;++i)
		info->map[i]=tab[i];
	((CExpatXMLParser*)data)->m_encoding=cp;
	return 1;
}

void * my_malloc(size_t size)
{
	return malloc(size);
}

void * my_realloc(void *p, size_t size)
{
	return realloc(p, size);
}

void my_free(void *p)
{
	free(p);
}

BOOL CExpatXMLParser::BeginRead(IDreamJournal *journal)
{	
	XML_Memory_Handling_Suite xmm = {my_malloc, my_realloc, my_free};

	m_journal = journal;
	m_parser = XML_ParserCreate_MM(NULL, &xmm, _T("|"));
	if(!m_parser)
		return false;
	XML_SetElementHandler(m_parser, StartElementCB, EndElementCB);
	XML_SetCharacterDataHandler(m_parser, CharacterDataCB);
	XML_SetCdataSectionHandler(m_parser, CDataStartCB, CDataEndCB);
	XML_SetUnknownEncodingHandler(m_parser, UnknownEncodingCB, this);
	XML_SetUserData(m_parser, this);	
	return true;	
}

BOOL CExpatXMLParser::Read(const char *data, int size)
{
	if (XML_Parse(m_parser, data, size, FALSE) == XML_STATUS_ERROR)
		return false;
	return true;
}

void CExpatXMLParser::EndRead()
{
	XML_Parse(m_parser, NULL, 0, TRUE);
//	m_journal->GetPlaces()->Sort(1, 0);
	m_journal->GetNewPlaces()->Sort(1,0);
}

LPTSTR CExpatXMLParser::GetErrorMessage(LPTSTR message, int max_len)
{
	XML_Error error = XML_GetErrorCode(m_parser);
	CString str = FromXMLChar(XML_ErrorString(error));
	_tcsncpy(message, str, max_len);
	return message;
}
