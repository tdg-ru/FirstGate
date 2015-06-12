#ifndef OWNER_INFO_H
#define OWNER_INFO_H

#include "dmxml.h"

// Информайия о владельце дневника
struct OwnerInfo: public DMxml
{
	CString first, middle, last;	// ФИО
	CString nick;				// Прозвище
	CString email;				// e-mail
	OwnerInfo(){}
	~OwnerInfo(){}
public:
	LPCTSTR GetLastName() const;
	LPCTSTR GetMiddleName() const;
	LPCTSTR GetFirstName() const;
	LPCTSTR GetNick() const;
	LPCTSTR GetEmail() const;
	void SetLastName(LPCTSTR name);
	void SetMiddleName(LPCTSTR name);
	void SetFirstName(LPCTSTR name);
	void SetNick(LPCTSTR name);
	void SetEmail(LPCTSTR name);

	int GetMinLength();
	void toString(CString &str);
};


#endif // OWNER_INFO_H