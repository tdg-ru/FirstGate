// DMPlaceListV.cpp: implementation of the DMPlaceListV class.
//
//////////////////////////////////////////////////////////////////////

#include "DMPlaceListV.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#pragma warning(disable:4786)

DMPlaceListV::DMPlaceListV()
{
	m_list = NULL;
	m_i = m_places.end();
	m_selected = -1;
	bUpdateCofactor = FALSE;
}

DMPlaceListV::DMPlaceListV(DMPlaceList *list)
{
	m_list = list;
	m_i = m_places.end();
	m_selected = -1;
	bUpdateCofactor = FALSE;
}

DMPlaceListV::DMPlaceListV(const DMPlaceListV &pl):
			m_places(pl.m_places)
{
	m_list = pl.m_list;	
	m_i = m_places.begin();
	m_selected = pl.m_selected;
	bUpdateCofactor = FALSE;
}

DMPlaceListV::~DMPlaceListV()
{

}


BOOL DMPlaceListV::SetList(DMPlaceList *list)
{
	m_list = list;
	return Verify();
}

BOOL DMPlaceListV::Verify()
{
	if(!m_list)
		return FALSE;

	INTVECTOR::iterator i = m_places.begin();
	while(i != m_places.end())
	{		
		if(m_list->GetPlace(*i) == NULL)
			return FALSE;
		i++;
	}
	return TRUE;
}


int DMPlaceListV::GetCount() const
{
	return m_places.size();
}

int DMPlaceListV::GetFirstID()
{
	m_i = m_places.begin();
	if(m_i != m_places.end())
		return (*m_i);
	else
		return -1;
}

int DMPlaceListV::GetNextID()
{
	if(m_i != m_places.end())
	{
		m_i++;
		if(m_places.size() && m_i != m_places.end())
		{
			return (*m_i);
		}
	}	
	m_i = m_places.end();
	return -1;
}

const IPlace *DMPlaceListV::GetPlace(const int id) const
{
	if(!m_list)
		return NULL;
	return m_list->GetPlace(id);
}

IPlace *DMPlaceListV::GetPlace(int id)
{
	if(!m_list)
		return NULL;
	return m_list->GetPlace(id);
}

IPlace *DMPlaceListV::GetPlaceByPos(int n)
{
	if(!m_list)
		return NULL;

	if(n>=0 && n < (signed)m_places.size())
		return m_list->GetPlace(m_places[n]);
	else
		return NULL;
}

void DMPlaceListV::Select(const int id)
{
	m_selected = id;
}

int DMPlaceListV::GetSelectedID() const
{
	return m_selected;
}

int DMPlaceListV::GetSelectedPos() const
{
	if(m_selected < 0)
		return -1;
	INTVECTOR::const_iterator i = m_places.begin();
	int num = 0;
	while(i != m_places.end())
	{
		if(m_selected == (*i))
			return num;
		i++;
		num++;
	}
	return -1;
}

const IPlace *DMPlaceListV::GetSelected() const
{
	return GetPlace(m_selected);
}

IPlace *DMPlaceListV::GetSelected()
{
	return GetPlace(m_selected);
}

BOOL DMPlaceListV::Add(const IPlace *p)
{
	int id = p->GetID();
	INTVECTOR::iterator i = m_places.begin();
	while(i != m_places.end())
	{
		if(*i == id)
			return FALSE;
		i++;
	}
	m_places.push_back(id);

	if(m_list && !(m_list->GetPlace(id)))
	{
		return m_list->Add(p);
	}
	return TRUE;		
}

BOOL DMPlaceListV::Add(const int id)
{
	if(id < 0)
		return FALSE;

	INTVECTOR::iterator i = m_places.begin();
	while(i != m_places.end())
	{
		if(*i == id)
			return FALSE;
		i++;
	}

	if(m_list && !(m_list->GetPlace(id)))
	{
		BOOL rez = m_list->Add(id);
		if(!rez)
			return FALSE;
	}
	
	m_places.push_back(id);
	if(bUpdateCofactor)
		m_list->mp_new_places->Delete(id);

	return TRUE;
}

int DMPlaceListV::Add()
{
	if(m_list)
	{
		int id = m_list->Add();
		if(Add(id))
			return id;
	}
	return -1;
}


void DMPlaceListV::Replace(const IPlace *p)
{

	int id = p->GetID();
	if(m_list)
		m_list->Replace(p);

	INTVECTOR::iterator i = m_places.begin();
	while(i != m_places.end())
	{
		if(*i == id)
			return;
		i++;
	}

	m_places.push_back(id);
	if(bUpdateCofactor)
		m_list->mp_new_places->Delete(id);
}

void DMPlaceListV::Delete(const int id)
{
	m_selected = -1;
	INTVECTOR::iterator i = m_places.begin();

	while(i != m_places.end())
	{
		if(*i == id)
		{
			m_places.erase(i);
			m_i = m_places.end();
			if(bUpdateCofactor)
				m_list->mp_new_places->Add(id);
			return;
		}
		i++;
	}
}

void DMPlaceListV::DeleteAll()
{
	m_places.clear();
	m_i = m_places.end();
	
	if(bUpdateCofactor)
		m_list->mp_new_places->InsertAll();
}


struct DMlessV : binary_function<int, int, bool> 
{
	DMPlaceList *m_list;
	int m_name;
	int m_color;

	DMlessV(DMPlaceList *list, int n, int c)
	{
		m_name = n;
		m_color = c;
		m_list = list;
	}
	bool operator()(const int a, const int &b) const
	{
		IPlace *pa = m_list->GetPlace(a);
		IPlace *pb = m_list->GetPlace(b);
		if(a && b)
		{
			bool n = (pa->GetTitleCS() < pb->GetTitleCS());
			bool c = (pa->GetColor() < pb->GetColor());
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
		}
		return false;
	}
};

void DMPlaceListV::Sort()
{
	stable_sort(m_places.begin(), m_places.end(), DMlessV(m_list, m_name_sort, m_color_sort));
}

void DMPlaceListV::Sort(int name, int color)
{
	if(m_name_sort == name)
		m_name_sort = -name;
	else
		m_name_sort = name;
	if(m_color_sort == color)
		m_color_sort = -color;
	else
		m_color_sort = color;
	stable_sort(m_places.begin(), m_places.end(), DMlessV(m_list, m_name_sort, m_color_sort));
}

int DMPlaceListV::GetMinLength()
{
	return m_places.size() * 24;
}

void DMPlaceListV::toString(CString &str)
{
	CString tmp;
	INTVECTOR::iterator i = m_places.begin();
	while(i != m_places.end())
	{
		tmp.Format(_T("<place id=\"%06d\"/>\r\n"), (*i));
		str += tmp;
		i++;
	}
}

void DMPlaceListV::InsertAll()
{
	if(bUpdateCofactor)
	{
		m_places.clear();
		m_i = m_places.end();
		int id = m_list->GetFirstID();
		while(id >= 0)
		{
			m_places.push_back(id);
			id = m_list->GetNextID();
		}
	}
}
