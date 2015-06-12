//#include "stdafx.h"
#include "DMDescription.h"


DMDescription::DMDescription(const DMDescription &d)
{
	m_str = d.m_str;
}

void DMDescription::SetText(LPCTSTR str)
{	
	m_str = str;
	Normalize();
}

void DMDescription::SetText(CString &str)
{
	m_str = str;
	Normalize();
}

LPCTSTR DMDescription::GetText() const
{
	return m_str;
}

const CString& DMDescription::GetTextCS() const
{
	return m_str;
}

const DMDescription& DMDescription::operator=(const DMDescription &d)
{
	m_str = d.m_str;
	return *this;
}

int DMDescription::GetMinLength()
{
	return int(1.5 * m_str.GetLength());
}

void DMDescription::toString(CString &str)
{	
	QuoteP(m_str, str);
}

void DMDescription::Normalize()
{
	m_str.TrimLeft(_T(" \r\n"));
	m_str.TrimRight(_T(" \r\n"));
	m_str += _T("\r\n");
}
