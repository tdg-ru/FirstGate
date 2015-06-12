// IMapLayer.h: interface for the IMapLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAPLAYER_H__30CA6530_5C14_47D6_BF1F_E27EF9AF3326__INCLUDED_)
#define AFX_IMAPLAYER_H__30CA6530_5C14_47D6_BF1F_E27EF9AF3326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPlaceList.h"

class IMapLayer  
{
public:
	virtual ~IMapLayer(){};

	virtual const IPlaceList *GetPlaces() const = 0;
	virtual bool GetPlacePoint(const int id, int &x, int &y) const = 0;
	virtual IPlace* GetPlace(int x, int y) = 0;

	virtual bool Add(int id, int x, int y) = 0;
	virtual void Delete(int id) = 0;
	virtual IPlaceList* GetPlaces() = 0;

	virtual int GetLayerId() const = 0;
};

#endif // !defined(AFX_IMAPLAYER_H__30CA6530_5C14_47D6_BF1F_E27EF9AF3326__INCLUDED_)
