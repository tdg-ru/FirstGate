// DreamJournal.cpp: implementation of the CDreamJournal class.
//
//////////////////////////////////////////////////////////////////////
#include "DreamJournal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDreamJournalImp::CDreamJournalImp()
{
	m_selected = -1;
	for(int i = 0; i < DM_LAYERS; i++)
	{
		m_layers[i].SetPlacesRef(&m_places);
		m_layers[i].SetLayerId(i - DM_LAYERS_DOWN);
	}
	m_map_width = 100;
	m_map_height = 100;
}

CDreamJournalImp::~CDreamJournalImp()
{

}

int CDreamJournalImp::GetDreamsCount()
{
	return m_dreams.size();
}

/*
int CDreamJournalImp::GetFirstDreamID()
{	
	return m_dreams.size()?0:(-1);
}

int CDreamJournalImp::GetNextDreamID(int id)
{
	return (id >= 0 && id+1 < (signed)m_dreams.size())?(id+1):(-1);
}
*/

IDreamRecord* CDreamJournalImp::GetDreamByPos(int id)
{
	return (id >= 0 && id < (signed)m_dreams.size())?&m_dreams[id]:NULL;
}

int CDreamJournalImp::Add(IDreamRecord &dream)
{	
	DreamRecord tmp;	
	tmp.SetPlacesRef(&m_places);
	m_dreams.push_back(tmp);  // добавили
	int id = m_dreams.size() - 1;
	m_dreams[id].Copy(&dream);
	return id; // вернуть id последнего
}

int CDreamJournalImp::Add()
{	
	DreamRecord tmp;
	tmp.SetPlacesRef(&m_places);
//	m_dreams.insert(m_dreams.begin(), tmp);
	m_dreams.push_back(tmp);  // добавили
	return m_dreams.size() - 1; // вернуть id последнего
}

void CDreamJournalImp::Delete(int id)
{
	if(id >= 0 && id < (signed)m_dreams.size())
		m_dreams.erase(&m_dreams[id]);

	int s = m_dreams.size();
	if(!s)
		m_selected = -1;
	if(m_selected > s-1)
		m_selected = s - 1;
}

void CDreamJournalImp::DeleteAll()
{
	m_dreams.clear();
	m_selected = -1;

	m_places.DeleteAll();

	for(int i = 0; i < DM_LAYERS; i++)
	{
		m_layers[i].DeleteAll();
	}

	m_zones.DeleteAll();
}

void CDreamJournalImp::SelectDreamPos(int pos)
{
	if(pos >= 0 && pos < (signed)m_dreams.size())
		m_selected = pos;
	else
		m_selected = -1;
}

int CDreamJournalImp::GetSelectedPos()
{
	if(m_selected >= 0 && m_selected <= (signed)m_dreams.size())
		return m_selected;
	m_selected = -1;
	return -1;
}

IDreamRecord* CDreamJournalImp::GetSelected()
{
	if(m_selected >= 0 && m_selected <= (signed)m_dreams.size())
		return &m_dreams[m_selected];
	else
		return NULL;
}

bool CDreamJournalImp::SortByDate(BOOL gr)
{
	if(gr)
	{
		stable_sort(m_dreams.begin(), m_dreams.end(), greater<DreamRecord>());
	}
	else
	{
		stable_sort(m_dreams.begin(), m_dreams.end(), less<DreamRecord>());
	}
	return true;
}

int CDreamJournalImp::GetMinLength()
{
	int rez = 23 + 52 + 125 + 26 * DM_LAYERS;
	rez += m_owner.GetMinLength();

	rez += m_dreams.size() * 1300;
	rez += m_places.GetCount() * 200;

	rez += m_zones.GetMinLength();
/*
	for(int i = 0; i < (signed)m_dreams.size(); i++)
	{
		rez += m_dreams[i].GetMinLength();
	}
	rez += m_places.GetMinLength();
*/
	return rez;
}

void CDreamJournalImp::toString(CString &str)
{
	int i;
	str += _T("<journal>\r\n");
	m_owner.toString(str);
	for(i = 0; i < (signed)m_dreams.size(); i++)
	{
		m_dreams[i].toString(str);
	}
	str += _T("</journal>\r\n");

	CString tmp;
	tmp.Format(_T("<dream-map width=\"%d\" height=\"%d\">\r\n"), m_map_width, m_map_height); str += tmp;
	for(i = 0; i < DM_LAYERS; i++)
	{
		int id = i - DM_LAYERS_DOWN; 
		tmp.Format(_T("<layer id=\"%d\">\r\n"), id); str += tmp;
		m_layers[i].toString(str);
		m_zones.toString(id, str);
		str += _T("</layer>");
	}
	str += _T("</dream-map>\r\n");
	m_places.toString(str);
	m_zones.toString(str);
}

IPlaceList* CDreamJournalImp::GetPlaces()
{
	return (IPlaceList*)&m_places;
}

IPlaceList* CDreamJournalImp::GetNewPlaces()
{
	return m_places.GetCofactorPL();
}

void CDreamJournalImp::SetMapSize(int w, int h)
{
	m_map_width = w;
	m_map_height = h;
}

void CDreamJournalImp::GetMapSize(int &w, int &h) const
{
	w = m_map_width;
	h = m_map_height;
}

IMapLayer*  CDreamJournalImp::GetLayer(int id)
{
	int i = id + DM_LAYERS_DOWN;
	if(i >= 0 && i < DM_LAYERS)
		return &(m_layers[i]);
	return NULL;
}
