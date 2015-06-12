#include "DMxml.h"
#include <vector>

#ifndef DMDESCRIPTION_H
#define DMDESCRIPTION_H

using namespace std;

// Класс для всяких описаний
class DMDescription: public DMxml
{
	CString m_str;
//	vector<CString> m_par;
public:	
	DMDescription()	{}
	DMDescription(const DMDescription &d);
	~DMDescription(){}
	void SetText(LPCTSTR str);
	void SetText(CString &str);
	LPCTSTR GetText() const;
	const CString& GetTextCS() const;
	const DMDescription &operator=(const DMDescription &d);
	
	virtual int GetMinLength();
	void toString(CString &str);
private:
	void Normalize();
};

#endif /*DMDESCRIPTION_H*/