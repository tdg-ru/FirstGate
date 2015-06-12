// IPlace.h: interface for the IPlace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPLACE_H__30D5A779_D50D_492B_B084_967463347905__INCLUDED_)
#define AFX_IPLACE_H__30D5A779_D50D_492B_B084_967463347905__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DMxml.h"
#include "DMDescription.h"

// Сновиденное место
// идентификатор
// название
// описание
// цвет
class IPlace
{
public:
	IPlace(){};
	virtual ~IPlace(){};
	
	virtual int GetID() const = 0;
	virtual LPCTSTR GetTitle() const = 0;
	virtual const DMDescription* GetDescription()  const = 0;
	virtual DMDescription* GetDescription() = 0;

	virtual void SetTitle(LPCTSTR) = 0;
	virtual void SetDescription(const DMDescription*) = 0;

	virtual void SetColor(COLORREF) = 0;
	virtual void GetColor(COLORREF &) const = 0;
	virtual COLORREF GetColor() const = 0;

	virtual void SetPoint(int layer, int x, int y) = 0;
	virtual void GetPoint(int &layer, int &x, int &y) const = 0;

// MFC интерфейс
	virtual CString GetTitleCS() const = 0;
	virtual void SetTitleCS(CString) = 0;
};

#endif // !defined(AFX_IPLACE_H__30D5A779_D50D_492B_B084_967463347905__INCLUDED_)
