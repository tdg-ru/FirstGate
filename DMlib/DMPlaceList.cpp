// DMPlaceList.cpp: implementation of the DMPlaceList class.
//
//////////////////////////////////////////////////////////////////////

#include "DMPlaceList.h"
#include "DMPlaceListV.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


DMPlaceList::DMPlaceList()
{
	mp_new_places = new DMPlaceListV(this);
	mp_new_places->bUpdateCofactor = FALSE;

	m_selected = -1;
	m_i = m_places.end();

	m_next_id = 0;
}

DMPlaceList::~DMPlaceList()
{
	if(mp_new_places)
		delete mp_new_places;
}

int DMPlaceList::GetCount() const
{
	return m_places.size();
}

int DMPlaceList::GetFirstID() 
{
	
	if(m_places.size())
	{
		m_i = m_places.begin();
		return (*m_i).GetID();
	}
	else
	{
		m_i = m_places.end();
		return -1;
	}
	return -1;
}

int DMPlaceList::GetNextID()
{
	if(m_i != m_places.end())
	{
		m_i++;
		if(m_places.size() && m_i != m_places.end())
		{
			return (*m_i).GetID();
		}
	}	
	m_i = m_places.end();
	return -1;
}

const IPlace *DMPlaceList::GetPlace(const int id) const
{
	TPlaceMap::const_iterator i = find(id);
	if(i != m_places.end())
		return &(*i);
	return NULL;
}

IPlace *DMPlaceList::GetPlace(int id)
{
	TPlaceMap::iterator i = find(id);
	if(i != m_places.end())
		return &(*i);
	return NULL;
}

IPlace *DMPlaceList::GetPlaceByPos(int n)
{
	if(n < 0 || n >= (signed)m_places.size())
		return NULL;
	TPlaceMap::iterator i = m_places.begin();
	while(i != m_places.end() && n)
	{
		i++;
		n--;
	}
	return &(*i);
}

int DMPlaceList::GetNumByID(int id)
{
	TPlaceMap::const_iterator i = m_places.begin();
	int num = 0;
	while(i != m_places.end())
	{
		if(m_selected == (*i).GetID())
		{		
			return num;
		}
		i++;	
		num++;
	}	
	return -1;
}

void DMPlaceList::Select(const int id)
{
	IPlace *p = GetPlace(id);
	if(p)
		m_selected = id;
	else
		m_selected = -1;
}

int DMPlaceList::GetSelectedID() const
{
	return m_selected;
}

int DMPlaceList::GetSelectedPos() const
{
	if(m_selected<0)
		return -1;

	TPlaceMap::const_iterator i = m_places.begin();
	int num = 0;
	while(i != m_places.end())
	{
		if(m_selected == (*i).GetID())
		{		
			return num;
		}
		i++;	
		num++;
	}	
	return -1;
}


const IPlace *DMPlaceList::GetSelected() const
{
	return GetPlace(m_selected);
}

IPlace *DMPlaceList::GetSelected()
{
	return GetPlace(m_selected);
}

BOOL DMPlaceList::Add(const int id)
{
	IPlace *p = GetPlace(id);
	if(p)
		return FALSE;

	DMPlace tmp(id);
	m_places.push_back(tmp);
	mp_new_places->Add(id);
	
	if(id >= m_next_id)
		m_next_id = id + 1;

	return TRUE;
}

int DMPlaceList::Add()
{
	int id = m_next_id;
	Add(id);
	return id;
}

BOOL DMPlaceList::Add(const IPlace *place)
{
	int id = place->GetID();
	TPlaceMap::iterator i = find(id);
	if(i != m_places.end())
		return FALSE;

	m_places.push_back(*place);
	mp_new_places->Add(id);

	if(id >= m_next_id)
		m_next_id = id + 1;

	return TRUE;
}

void DMPlaceList::Replace(const IPlace *place)
{
	int id = place->GetID();
	TPlaceMap::iterator i = find(id);
	if(i != m_places.end())
	{
		(*i) = *place;
		return;
	}
	else
	{
		m_places.push_back(*place);
		mp_new_places->Add(id);
		
		if(id >= m_next_id)
			m_next_id = id + 1;
	}
}

void DMPlaceList::Delete(const int id)
{
	TPlaceMap::iterator i = find(id);
	if(i != m_places.end())
	{
		m_places.erase(i);
		mp_new_places->Delete(id);
		m_selected = -1;
	}
}

void DMPlaceList::DeleteAll()
{
	m_places.clear();
	m_selected = -1;
	mp_new_places->DeleteAll();
	m_i = m_places.end();
}


struct DMlessP : binary_function<DMPlace&, DMPlace&, bool> 
{
	int m_color;
	int m_name;

	DMlessP(int n, int c)
	{
		m_name = n;
		m_color = c;
	}
	bool operator()(const DMPlace& a, const DMPlace& b) const
	{
		bool n = (a.GetTitleCS() < b.GetTitleCS());
		bool c = (a.GetColor() < b.GetColor());
		bool rez = false;
		if(m_name)
		{
			if(m_name > 0) 
				rez = n;
			else
				rez = !n;
			return rez;
		}
		if(m_color)
		{
			if(m_color > 0) 
				rez = c;
			else
				rez = !c;
			return rez;
		}
		return false;
	}
};


void DMPlaceList::Sort()
{
	sort(m_places.begin(), m_places.end(), DMlessP(m_name_sort, m_color_sort));
}

void DMPlaceList::Sort(int name, int color)
{
	if(m_name_sort == name)
		m_name_sort = -name;
	else
		m_name_sort = name;
	if(m_color_sort == color)
		m_color_sort = -color;
	else
		m_color_sort = color;
	sort(m_places.begin(), m_places.end(), DMlessP(m_name_sort, m_color_sort));
}

int DMPlaceList::GetMinLength()
{
	int rez = 0;
	TPlaceMap::iterator i = m_places.begin();
	while(i != m_places.end())
	{
		rez += (*i).GetMinLength();
		i++;
	}
	return rez;
}

void DMPlaceList::toString(CString &str)
{
	TPlaceMap::iterator i = m_places.begin();
	while(i != m_places.end())
	{
		(*i).toString(str);
		i++;
	}
}


TPlaceMap::iterator DMPlaceList::find(int id)
{
	TPlaceMap::iterator i = m_places.begin();
	while(i != m_places.end())
	{
		if(id == (*i).GetID())
		{		
			return i;
		}
		i++;	
	}
	return i;
}

TPlaceMap::const_iterator DMPlaceList::find(int id) const
{
	TPlaceMap::const_iterator i = m_places.begin();
	while(i != m_places.end())
	{
		if(id == (*i).GetID())
		{		
			return i;
		}
		i++;	
	}
	return i;
}