// IZoneList.h: interface for the IZoneList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IZONELIST_H__12AF6181_2B8E_4EF7_92DB_2D1C273F530E__INCLUDED_)
#define AFX_IZONELIST_H__12AF6181_2B8E_4EF7_92DB_2D1C273F530E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IZoneList
{
public:
	virtual ~IZoneList(){}

	virtual const IPlaceList *GetPlaces() const = 0;
	virtual IPlace* GetPlace(int layer, int x, int y) = 0;
	virtual void Select(int layer, int x, int y) = 0;

	virtual bool Add(int id, int layer, int x, int y) = 0;
	virtual IPlaceList* GetPlaces() = 0;
};

#endif // !defined(AFX_IZONELIST_H__12AF6181_2B8E_4EF7_92DB_2D1C273F530E__INCLUDED_)
