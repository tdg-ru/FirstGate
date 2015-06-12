// DreamRecord.h: interface for the CDreamRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DREAMRECORD_H__C083D5A8_FBA7_4FDD_8BE8_58CB99B65D46__INCLUDED_)
#define AFX_DREAMRECORD_H__C083D5A8_FBA7_4FDD_8BE8_58CB99B65D46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDreamRecord.h"
#include "DMPlaceListV.h"

class DreamRecord: public IDreamRecord, public DMxml
{
	CString		  title;	   // название
	DMDate		  date;		   // дата
	DM_DREAM_TYPE type;		   // тип
	CString		  other_type;  // нестандартный тип
	DMDescription description; // описание
	DMDescription comment;	   // комментарии 
	DMPlaceListV  places;	   // виртуальный список мест
public:
	DreamRecord() { type = DREAM_UNKNOWN; }
	DreamRecord(const DreamRecord &d):
		description(d.description),
		comment(d.comment),
		date(d.date),
		title(d.title),
		other_type(d.other_type),
		places(d.places)
	{
			type=d.type;
	}
	~DreamRecord()
	{ 
	}

	// Получение информации
	virtual LPCTSTR 	GetTitle()		const { return title; }
	virtual DM_DREAM_TYPE 	GetType()	const { return type;  } 
	virtual LPCTSTR 	GetExtType()	const { return other_type; }
	virtual const DMDate* 	GetDate()   const { return &date;	}
	virtual const DMDescription* GetDescription() const { return &description; }
	virtual const DMDescription* GetComment() const {return &comment; }

	// Установка
	virtual void SetTitle(LPCTSTR);
	virtual void SetType(const DM_DREAM_TYPE);
	virtual void SetExtType(LPCTSTR);
	virtual void SetDate(const DMDate*);
	virtual void SetDescription(const DMDescription*);
	virtual void SetComment(const DMDescription*);
	virtual void Copy(IDreamRecord *);

	virtual IPlaceList* GetPlaces();

	virtual int GetMinLength();
	virtual void toString(CString &str);

	bool operator>(const DreamRecord& d) const { return (date > d.date); }
	bool operator<(const DreamRecord& d) const { return (date < d.date); }

	BOOL SetPlacesRef(DMPlaceList *list);
};

#endif // !defined(AFX_DREAMRECORD_H__C083D5A8_FBA7_4FDD_8BE8_58CB99B65D46__INCLUDED_)
