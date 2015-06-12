// DMPlace.cpp: implementation of the DMPlace class.
//
//////////////////////////////////////////////////////////////////////

#include "DMPlace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DMPlace::DMPlace()
{
	m_id = -1;
	m_color = RGB(0, 0, 255);
	m_x = m_y = m_layer = 0;
}

DMPlace::DMPlace(int id)
{
	m_id = id;
	m_color = RGB(0, 0, 255);
	m_x = m_y = m_layer = 0;
}

DMPlace::DMPlace(const DMPlace &d):
		m_id(d.m_id),
		m_title(d.m_title),
		m_description(d.m_description),
		m_color(d.m_color)		
{
			m_x = d.m_x;
			m_y = d.m_y;
			m_layer = d.m_layer;
}

DMPlace::DMPlace(const IPlace &d):
		m_id(d.GetID()),
		m_title(d.GetTitleCS()),
		m_description(*d.GetDescription())
{
	d.GetColor(m_color);
	d.GetPoint(m_layer, m_x, m_y);
}


DMPlace::~DMPlace()
{

}

void DMPlace::SetTitle(LPCTSTR name)
{
	m_title = name;
}

void DMPlace::SetDescription(const DMDescription* d)
{
	m_description = *d;
}

// MFC интерфейс
CString DMPlace::GetTitleCS() const
{
	return m_title;
}

void DMPlace::SetTitleCS(CString name)
{
	m_title = name;
}

int DMPlace::GetMinLength()
{
	return 173 + m_title.GetLength() + m_description.GetMinLength();
}

void DMPlace::toString(CString &str)
{
	CString tmp;
	tmp.Format(_T("<place id=\"%d\" color=\"#%02X%02X%02X\">\r\n<title>"), m_id, GetRValue(m_color), GetGValue(m_color), GetBValue(m_color)); str += tmp;
	Quote(m_title, str);
	str += _T("</title>\r\n<description>");		
	m_description.toString(str);
	str += _T("</description>\r\n</place>\r\n");
}  

void DMPlace::SetColor(COLORREF c)
{
	m_color = c;
}

void DMPlace::GetColor(COLORREF &c) const
{
	c = m_color;
}

COLORREF DMPlace::GetColor() const
{
	return m_color;
}


void DMPlace::SetPoint(int layer, int x, int y)
{
	m_layer = layer;
	m_x = x;
	m_y = y;
}

void DMPlace::GetPoint(int &layer, int &x, int &y) const
{
	layer = m_layer;
	x = m_x;
	y = m_y;
}
