// DMPlaceListV.h: interface for the DMPlaceListV class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMPLACELISTV_H__7397A633_861B_4496_A02A_0C07CD02BC69__INCLUDED_)
#define AFX_DMPLACELISTV_H__7397A633_861B_4496_A02A_0C07CD02BC69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPlaceList.h"
#include "DMPlaceList.h"
#include "DMxml.h"

#include <vector>
#include <functional>
#include <algorithm>

using namespace std ;

typedef vector<int> INTVECTOR;

class DMPlaceListV : 
	public IPlaceList, 
	public DMxml  
{
private:
	DMPlaceList *m_list;
	INTVECTOR m_places;
	INTVECTOR::iterator m_i;
	int m_selected;

	void InsertAll();
	
	int m_name_sort;
	int m_color_sort;
protected:
	BOOL bUpdateCofactor;

public:
	DMPlaceListV();
	DMPlaceListV(DMPlaceList *list);
	DMPlaceListV(const DMPlaceListV &);
	virtual ~DMPlaceListV();

	BOOL SetList(DMPlaceList *list);
	BOOL Verify();

	virtual int GetCount() const;
	virtual int GetFirstID();
	virtual int GetNextID();
	virtual const IPlace *GetPlace(const int) const;
	virtual IPlace *GetPlace(int);
	virtual IPlace *GetPlaceByPos(int);

	virtual void Select(const int);
	virtual int GetSelectedID() const;
	virtual int GetSelectedPos() const;
	virtual const IPlace *GetSelected() const;
	virtual IPlace *GetSelected();

	virtual BOOL Add(const int id);
	virtual BOOL Add(const IPlace *);
	virtual int Add();
	virtual void Replace(const IPlace *);
	virtual void Delete(const int);
	virtual void DeleteAll();

	virtual void Sort();
	virtual void Sort(int name, int color);

	virtual int GetMinLength();
	virtual void toString(CString &str);

	friend class DMPlaceList;
	friend class DMMapLayer;
};

#endif // !defined(AFX_DMPLACELISTV_H__7397A633_861B_4496_A02A_0C07CD02BC69__INCLUDED_)
