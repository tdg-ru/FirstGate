//#include "stdafx.h"
#include "ownerinfo.h"

int OwnerInfo::GetMinLength()
{
	int rez = 19;
	if(first.GetLength())	rez += 27 + first.GetLength();
	if(middle.GetLength())	rez += 29 + middle.GetLength();
	if(last.GetLength())	rez += 25 + last.GetLength();
	if(email.GetLength())	rez += 17 + email.GetLength();
	if(nick.GetLength())	rez += 15 + nick.GetLength();
	return rez;
}

void  OwnerInfo::toString(CString &str)
{
	CString tmp;
	str += _T("<owner>\r\n");
	if(first.GetLength())	{tmp.Format(_T("<first-name>%s</first-name>\r\n"), first); str += tmp; }
	if(middle.GetLength())	{tmp.Format(_T("<middle-name>%s</middle-name>\r\n"), middle); str += tmp; }
	if(last.GetLength())	{tmp.Format(_T("<last-name>%s</last-name>\r\n"), last); str += tmp;}
	if(email.GetLength())	{tmp.Format(_T("<email>%s</email>\r\n"), email); str += tmp;}
	if(nick.GetLength())	{tmp.Format(_T("<nick>%s</nick>\r\n"), nick); str += tmp;}
	str += _T("</owner>\r\n");
}

void OwnerInfo::SetFirstName(LPCTSTR name)
{
	first = name;
}

void OwnerInfo::SetMiddleName(LPCTSTR name)
{
	middle = name;
}

void OwnerInfo::SetLastName(LPCTSTR name)
{
	last = name;
}

void OwnerInfo::SetNick(LPCTSTR name)
{
	nick = name;
}

void OwnerInfo::SetEmail(LPCTSTR name)
{
	email = name;
}


LPCTSTR OwnerInfo::GetFirstName() const
{
	return first;
}


LPCTSTR OwnerInfo::GetMiddleName() const
{
	return middle;
}


LPCTSTR OwnerInfo::GetLastName() const
{
	return last;
}


LPCTSTR OwnerInfo::GetNick() const
{
	return nick;
}

LPCTSTR OwnerInfo::GetEmail() const
{
	return email;
}