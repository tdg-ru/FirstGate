// DMPlaceList.h: interface for the DMPlaceList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMPLACELIST_H__A519A8B4_F71B_4805_9BE4_C029AE9E107C__INCLUDED_)
#define AFX_DMPLACELIST_H__A519A8B4_F71B_4805_9BE4_C029AE9E107C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

#include "IPlaceList.h"
#include "DMxml.h"
#include "DMPlace.h"

class DMPlaceListV;

#include <vector>
#include <functional>
#include <algorithm>

using namespace std ;

typedef vector<DMPlace> TPlaceMap;

class DMPlaceList : 
	public IPlaceList, 
	public DMxml  
{
private:
	TPlaceMap m_places;	
	TPlaceMap::iterator m_i; 

	int m_selected;
	int m_next_id;

	TPlaceMap::iterator find(int id);
	TPlaceMap::const_iterator find(int id) const;

	int m_name_sort;
	int m_color_sort;
protected:
	DMPlaceListV *mp_new_places;

public:
	DMPlaceList();
	virtual ~DMPlaceList();

	virtual int GetCount() const;
	virtual int GetFirstID();
	virtual int GetNextID();
	virtual const IPlace *GetPlace(const int) const;
	virtual IPlace *GetPlace(int);
	virtual IPlace *GetPlaceByPos(int);
	virtual int GetNumByID(int);

	virtual void Select(const int);
	virtual int GetSelectedID() const;
	virtual int GetSelectedPos() const;
	virtual const IPlace *GetSelected() const;
	virtual IPlace *GetSelected();	

	virtual BOOL Add(const IPlace *);
	virtual BOOL Add(const int id);
	virtual int Add();
	virtual void Replace(const IPlace *);
	virtual void Delete(const int);
	virtual void DeleteAll();

	virtual void Sort();
	virtual void Sort(int name, int color);

	virtual int GetMinLength();	
	virtual void toString(CString &str);

	IPlaceList *GetCofactorPL() { return (IPlaceList*)mp_new_places; }

	friend class DMPlaceListV;
	friend class DMZoneList;
};

#endif // !defined(AFX_DMPLACELIST_H__A519A8B4_F71B_4805_9BE4_C029AE9E107C__INCLUDED_)
