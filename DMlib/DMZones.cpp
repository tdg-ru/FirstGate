// DMZones.cpp: implementation of the DMZones class.
//
//////////////////////////////////////////////////////////////////////

#include "DMZones.h"

#define MAKE_POINT(x,y) ((x<<16) + (y&0x0000FFFF))
#define GET_X(p) ((p>>16)&0xFFFF)
#define GET_Y(p) (p&0xFFFF)

#pragma warning(disable:4786)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DMZoneList::DMZoneList()
{
	m_zones.m_next_id = 1;
}

DMZoneList::~DMZoneList()
{

}


IPlace* DMZoneList::GetPlace(int layer, int x, int y)
{
	int l_id = layer + DM_LAYERS_DOWN;
	if(l_id >= 0 && l_id < DM_LAYERS)
	{
		DWORD a = MAKE_POINT(x,y);
		TPointMap::iterator i = m_points[l_id].find(a);
		if(i != m_points[l_id].end())
		{
			return m_zones.GetPlace((*i).second);
		}
	}
	return NULL;
}

void DMZoneList::Select(int layer, int x, int y)
{
	int l_id = layer + DM_LAYERS_DOWN;
	if(l_id >= 0 && l_id < DM_LAYERS)
	{
		DWORD a = MAKE_POINT(x,y);
		TPointMap::iterator i = m_points[l_id].find(a);
		if(i != m_points[l_id].end())
		{
			m_zones.Select((*i).second);
		}
		else
		{
			m_zones.Select(-1);
		}
	}
}

bool DMZoneList::Add(int id, int layer, int x, int y)
{
	int l_id = layer + DM_LAYERS_DOWN;
	if(l_id >= 0 && l_id < DM_LAYERS)
	{
		DWORD a = MAKE_POINT(x,y);
		if(id >= 0)
		{
			if(!m_zones.GetPlace(id) && !m_zones.Add(id))
				return false;
			m_points[l_id][a] = id;
		}
		else
		{
			m_points[l_id].erase(a);
		}
		return true;
	}
	return false;
}

void DMZoneList::DeleteAll()
{
	m_zones.DeleteAll();
	for(int i = 0; i < DM_LAYERS; i++)
		m_points[i].clear();
}

void DMZoneList::toString(int layer, CString &str)
{
	CString tmp;
	int z_cnt = m_zones.GetCount();
	if(!z_cnt)
		return;
	int l_id = layer + DM_LAYERS_DOWN;
	if(l_id >= 0 && l_id < DM_LAYERS)
	{	
		TPointMap::iterator i = m_points[l_id].begin();
		while(i != m_points[l_id].end())
		{
			tmp.Format(_T("<pnt id=\"%d\" x=\"%d\" y=\"%d\"/>"), (*i).second, GET_X((*i).first), GET_Y((*i).first));
			str += tmp;
			i++;
		}
	}
	str+=_T("\r\n");
}

int DMZoneList::GetMinLength(int layer)
{
	int z_cnt = m_zones.GetCount();
	if(!z_cnt)
		return 0;
	int l_id = layer + DM_LAYERS_DOWN;
	if(l_id >= 0 && l_id < DM_LAYERS)
		return m_points[l_id].size() * 37;
	return 0;
}

void DMZoneList::toString(CString &str)
{
	CString tmp;
	int id = m_zones.GetFirstID();
	while(id >= 0)
	{
		IPlace *p = m_zones.GetPlace(id);
		COLORREF c;
		p->GetColor(c);
		tmp.Format(_T("<zone id=\"%d\" color=\"#%02X%02X%02X\"><title>"), p->GetID(), GetRValue(c), GetGValue(c), GetBValue(c)); str += tmp;
		Quote(p->GetTitleCS(), str);
		str += _T("</title><description>");		
		p->GetDescription()->toString(str);
		str += _T("</description></zone>\r\n");
		id = m_zones.GetNextID();
	}
}

int DMZoneList::GetMinLength()
{
	int z_cnt = m_zones.GetCount();
	if(!z_cnt)
		return 0;
	int rez = 0;
	for(int l_id = 0; l_id < DM_LAYERS; l_id++)
		rez += m_points[l_id].size() * 37;
	rez += m_zones.GetMinLength();
	return rez;
}
