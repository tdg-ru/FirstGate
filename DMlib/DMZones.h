// DMZones.h: interface for the DMZones class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMZONES_H__C4F5BD84_68CA_41B8_9818_C53F1B241FAC__INCLUDED_)
#define AFX_DMZONES_H__C4F5BD84_68CA_41B8_9818_C53F1B241FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDreams.h"
#include "DMPlaceList.h"
#include "IZoneList.h"

#include <map>
typedef map<DWORD, int> TPointMap;

using namespace std ;

class DMZoneList: public IZoneList, public DMxml
{
public:
	DMZoneList();
	virtual ~DMZoneList();

	virtual const IPlaceList *GetPlaces() const { return &m_zones; }
	virtual IPlaceList* GetPlaces() { return &m_zones; }
	virtual void Select(int layer, int x, int y);
	
	virtual IPlace* GetPlace(int layer, int x, int y);
	virtual bool Add(int id, int layer, int x, int y);	
	void DeleteAll();

	virtual void toString(int layer_id, CString &str);
	virtual int GetMinLength(int layer_id);

	virtual void toString(CString &str);
	virtual int GetMinLength();
private:
	DMPlaceList m_zones;
	TPointMap m_points[DM_LAYERS];
};

#endif // !defined(AFX_DMZONES_H__C4F5BD84_68CA_41B8_9818_C53F1B241FAC__INCLUDED_)
