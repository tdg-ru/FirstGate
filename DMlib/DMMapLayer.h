// DMMapLayer.h: interface for the DMMapLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMMAPLAYER_H__8CAC3EF1_12E4_4BC7_8408_3864D1A659E2__INCLUDED_)
#define AFX_DMMAPLAYER_H__8CAC3EF1_12E4_4BC7_8408_3864D1A659E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IMapLayer.h"
#include "DMPlaceListV.h"	// Added by ClassView

#include <map>

using namespace std ;

typedef map<DWORD, int> TPointMap;

class DMMapLayer : public IMapLayer  
{
protected:
	virtual void SetLayerId(int id){ m_id = id; }
public:
	DMMapLayer();
	virtual ~DMMapLayer();

	virtual const IPlaceList *GetPlaces() const;
	virtual bool GetPlacePoint(const int id, int &x, int &y) const;
	virtual IPlace* GetPlace(int x, int y);
	virtual bool Add(int id, int x, int y);
	virtual void Delete(int id);
	virtual void DeleteAll();

	virtual IPlaceList* GetPlaces() {return (IPlaceList*)&m_places; }

	BOOL SetPlacesRef(DMPlaceList *list);

	virtual int GetLayerId() const { return m_id; }

	virtual void toString(CString &str);

private:
	int m_id;
	DMPlaceListV m_places;
	TPointMap    m_points;
friend class CDreamJournalImp;
};

#endif // !defined(AFX_DMMAPLAYER_H__8CAC3EF1_12E4_4BC7_8408_3864D1A659E2__INCLUDED_)
