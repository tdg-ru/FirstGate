// IPlaceList.h: interface for the IPlaceList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPLACELIST_H__B4C7F468_0339_4525_952D_3CD8B6AEB42C__INCLUDED_)
#define AFX_IPLACELIST_H__B4C7F468_0339_4525_952D_3CD8B6AEB42C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPlace.h"

class IPlaceList  
{
public:
	virtual ~IPlaceList(){}

	virtual int GetCount() const = 0;
	virtual int GetFirstID() = 0;
	virtual int GetNextID() = 0;
	virtual const IPlace *GetPlace(const int) const = 0;
	virtual IPlace *GetPlace(int) = 0;
	virtual IPlace *GetPlaceByPos(int) = 0;

	virtual void Select(const int) = 0;
	virtual int GetSelectedID() const = 0;
	virtual int GetSelectedPos() const = 0;
	virtual const IPlace *GetSelected() const = 0;
	virtual IPlace *GetSelected() = 0;	

	virtual BOOL Add(const IPlace *) = 0;
	virtual BOOL Add(const int id) = 0;
	virtual int Add() = 0;
	virtual void Replace(const IPlace *) = 0;
	virtual void Delete(const int) = 0;
	virtual void DeleteAll() = 0;

	virtual void Sort() = 0;
	virtual void Sort(int name, int color) = 0;
};

#endif // !defined(AFX_IPLACELIST_H__B4C7F468_0339_4525_952D_3CD8B6AEB42C__INCLUDED_)
