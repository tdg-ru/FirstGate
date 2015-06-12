/*
 * Copyright (c) 2002, TDG. All Rights Reserved.
 * IDreams.h: ���������� ����������� ��� ������ � ���������� ��������� 
 * CDreamJournal � ������ 
 */

#if !defined(AFX_IDJREADER_H__28E82C28_89FB_4769_8341_8482C0B43A88__INCLUDED_)
#define AFX_IDJREADER_H__28E82C28_89FB_4769_8341_8482C0B43A88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDreamRecord.h"
#include "IDreamList.h"
#include "ownerinfo.h"
#include "IMapLayer.h"
#include "IZoneList.h"


#define DM_LAYERS_UP 1
#define DM_LAYERS_DOWN 1
#define DM_LAYERS DM_LAYERS_UP + DM_LAYERS_DOWN + 1


// ����� ��� ������ � ��������� ����������
class IDreamJournal: public DMxml, public IDreamList
{
protected:
	OwnerInfo m_owner;
public:
	virtual ~IDreamJournal(){};

	// ������ ��� ������� � ������ ������ ������������
	virtual void SetOwnerInfo(OwnerInfo &ow)
	{
		m_owner = ow;
	}
	virtual OwnerInfo& GetOwnerInfo()
	{
		return m_owner;
	}

	// "����������" ������
	virtual IPlaceList* GetPlaces() = 0;
	virtual IPlaceList* GetNewPlaces() = 0;
	virtual void SetMapSize(int w, int h) = 0;
	virtual void GetMapSize(int &w, int &h) const = 0;
	virtual IMapLayer*  GetLayer(int id) = 0;
	virtual IZoneList*  GetZones() = 0;
};


// ��������� ��� ������ �������� �� ������
class IDreamParser
{
protected:
	IDreamJournal *m_journal;
public:
	IDreamParser() { m_journal = NULL; }
	virtual ~IDreamParser(){};
	virtual BOOL	BeginRead(IDreamJournal *journal)	= 0; // ������ ������
	virtual BOOL	Read(const char *data, int size)			= 0;  // 
	virtual void	EndRead()							= 0;
	virtual LPTSTR	GetErrorMessage(LPTSTR message, int max_len) = 0;
};

// ��������� ��� ������ �������� � ������
class IDreamWriter
{
protected:
	IDreamJournal *m_journal;
public:
	IDreamWriter() { m_journal = NULL; }
	virtual ~IDreamWriter(){};
	virtual BOOL	BeginWrite(IDreamJournal *journal)	= 0;
	virtual int		Write(void *buffer, int size)		= 0;
	virtual int		Write(CString &str)					= 0;
	virtual BOOL	IsEnd()								= 0;
	virtual LPTSTR	GetErrorMessage(LPTSTR message, int max_len) = 0;
	virtual int		GetBufferSize() = 0;
};

#endif // !defined(AFX_IDJREADER_H__28E82C28_89FB_4769_8341_8482C0B43A88__INCLUDED_)
