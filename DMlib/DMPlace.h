// DMPlace.h: interface for the DMPlace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMPLACE_H__86035A04_3369_483F_9216_3B21AA89CFDF__INCLUDED_)
#define AFX_DMPLACE_H__86035A04_3369_483F_9216_3B21AA89CFDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPlace.h"

class DMPlace : public IPlace, public DMxml
{
private:
	int m_id;
	CString m_title;
	DMDescription m_description;
	COLORREF m_color;
	int m_x, m_y, m_layer;
protected:
	virtual void SetID(const int id) { m_id = id; } 
public:
	DMPlace();
	DMPlace(int id);
	DMPlace(const DMPlace &d);
	DMPlace(const IPlace &d);
	virtual ~DMPlace();

	virtual int GetID() const { return m_id; }
	virtual LPCTSTR GetTitle() const {	return m_title; }
	virtual const DMDescription* GetDescription()  const {return &m_description; }
	virtual DMDescription* GetDescription() {return &m_description; }

	virtual void SetTitle(LPCTSTR);
	virtual void SetDescription(const DMDescription*);

	virtual void SetColor(COLORREF);
	virtual void GetColor(COLORREF &) const;
	virtual COLORREF GetColor() const;

	virtual void SetPoint(int layer, int x, int y);
	virtual void GetPoint(int &layer, int &x, int &y) const;

	bool operator>(const DMPlace& d) const { return (m_title > d.m_title); }
	bool operator<(const DMPlace& d) const { return (m_title < d.m_title); }

// MFC интерфейс
	virtual CString GetTitleCS() const;
	virtual void SetTitleCS(CString);

	virtual int GetMinLength();
	virtual void toString(CString &str);
};

#endif // !defined(AFX_DMPLACE_H__86035A04_3369_483F_9216_3B21AA89CFDF__INCLUDED_)
