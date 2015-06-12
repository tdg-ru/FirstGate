// DMMapLayer.cpp: implementation of the DMMapLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "DMMapLayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MAKE_POINT(x,y) ((x<<16) + (y&0x0000FFFF))
#define GET_X(p) ((p>>16)&0xFFFF)
#define GET_Y(p) (p&0xFFFF)

#pragma warning(disable:4786)

DMMapLayer::DMMapLayer()
{
	m_id = 0;
	m_places.bUpdateCofactor = TRUE;
}

DMMapLayer::~DMMapLayer()
{

}

const IPlaceList *DMMapLayer::GetPlaces() const
{
	return &m_places;
}

bool DMMapLayer::GetPlacePoint(const int id, int &x, int &y) const
{
	int l;
	const IPlace *p = m_places.GetPlace(id);
	if(p)
	{
		p->GetPoint(l, x, y);
		return true;
	}
	return false;
}

IPlace* DMMapLayer::GetPlace(int x, int y)
{
	DWORD a = MAKE_POINT(x,y);
	TPointMap::iterator i = m_points.find(a);
	if(i != m_points.end())
	{
		return m_places.GetPlace((*i).second);
	}
	return NULL;
}

bool DMMapLayer::Add(int id, int x, int y)
{
	if(GetPlace(x, y))
		return false;
	if(m_places.Add(id))
	{
		m_places.GetPlace(id)->SetPoint(m_id, x, y);
		DWORD a = MAKE_POINT(x,y);
		m_points[a] = id;
		return true;
	}	
	return false;
}

void DMMapLayer::Delete(int id)
{
	int l, x, y;
	DWORD a;
	IPlace *p = m_places.GetPlace(id);
	if(p)
	{
		p->GetPoint(l, x, y);
		a = MAKE_POINT(x, y);

		m_places.Delete(id);		
		m_points.erase(a);
	}
}

void DMMapLayer::DeleteAll()
{
	m_places.DeleteAll();
	m_points.clear();
}

void DMMapLayer::toString(CString &str)
{
	DWORD a;
	CString tmp;
	TPointMap::iterator i = m_points.begin();
	while(i != m_points.end())
	{
		a = (*i).first;
		int x = GET_X(a);
		int y = GET_Y(a);
		tmp.Format(_T("<locality id=\"%d\" x=\"%d\" y=\"%d\"/>\r\n"), (*i).second, x, y); 
		str += tmp;
		i++;
	}
}

BOOL DMMapLayer::SetPlacesRef(DMPlaceList *list)
{
	return m_places.SetList(list);
}