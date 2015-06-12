// DreamRecord.cpp: implementation of the CDreamRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "DreamRecord.h"

// ”становка
void DreamRecord::SetTitle(LPCTSTR t)
{
	title = t;
}

void DreamRecord::SetType(const DM_DREAM_TYPE t)
{
	type = t;
}

void DreamRecord::SetExtType(LPCTSTR s)
{
	other_type = s;
}

void DreamRecord::SetDate(const DMDate* pd)
{
	date = *pd;
}

void DreamRecord::SetDescription(const DMDescription* pd)
{
	description.SetText(pd->GetText());
}

void DreamRecord::SetComment(const DMDescription* pd)
{
	comment.SetText(pd->GetText());
}

void DreamRecord::Copy(IDreamRecord *d)
{
	title = d->GetTitle();	   // название
	date  = *d->GetDate();		   // дата
	type  = d->GetType();		   // тип
	other_type = d->GetExtType();  // нестандартный тип

	SetDescription(d->GetDescription());
	SetComment(d->GetComment());
}

int DreamRecord::GetMinLength()
{
	int rez = 100;
	rez += title.GetLength();
	rez += date.GetMinLength();
	rez += other_type.GetLength();
	rez += description.GetMinLength();
	rez += comment.GetMinLength();
	rez += places.GetMinLength();
	return rez;
}

void DreamRecord::toString(CString &str)
{
//	CString tmp;	
	str += _T("<dream>\r\n<title>");
	Quote(title, str);
	str += _T("</title>\r\n");

	date.toString(str);
	str += _T("<type>");
	Quote(other_type, str);
	str += _T("</type>\r\n<description>");

	description.toString(str);
	str += _T("</description>\r\n<comment>");
	comment.toString(str);
	str += _T("</comment>\r\n");
	places.toString(str);
	str += _T("</dream>\r\n");
}

IPlaceList* DreamRecord::GetPlaces()
{
	return (IPlaceList*)&places;
}

BOOL DreamRecord::SetPlacesRef(DMPlaceList *list)
{
	return places.SetList(list);
}