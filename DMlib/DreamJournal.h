// DreamJournal.h: interface for the CDreamJournal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DREAMJOURNAL_H__417C5963_A1B3_4978_A057_99C816DA58EE__INCLUDED_)
#define AFX_DREAMJOURNAL_H__417C5963_A1B3_4978_A057_99C816DA58EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <functional>
#include <algorithm>

#include "IDreams.h"
#include "DreamRecord.h"
#include "DMMapLayer.h"
#include "DMZones.h"

using namespace std;

class CDreamJournalImp: public IDreamJournal
{	
public:
	CDreamJournalImp();
	~CDreamJournalImp();
	// ������ ������/��������������
	virtual int GetDreamsCount();	// ���-�� ����
//	virtual int GetFirstDreamID();	// ������ ���
//	virtual int GetNextDreamID(int id);	// ��������� ��� (-1 - �����)
	virtual IDreamRecord* GetDreamByPos(int pos); // ��� �� ��������������

	// ���������
	virtual void SelectDreamPos(int pos); // �������� ���
	virtual int GetSelectedPos();	  // �������� id �����������
	virtual IDreamRecord* GetSelected(); 
	
	// ������ ����������/��������
	virtual int Add(IDreamRecord &dream); // ���������� id - ������ ���
	virtual int Add(); // ���������� id - ������ ���
	virtual void Delete(int id);		 // ������� ��� � id
	virtual void DeleteAll();			 // ������� ��� ������

	// ������ ���������� � ������
	// ����� ���������� ��� ������, ����� ������ ����� �������� ��������
	// GetFirst, GetNext
	virtual bool SortByDate(BOOL gr = TRUE); // ������������� �� ����

	virtual IPlaceList* GetPlaces();
	virtual IPlaceList* GetNewPlaces();

	virtual void SetMapSize(int w, int h);
	virtual void GetMapSize(int &w, int &h) const;
	virtual IMapLayer*  GetLayer(int id);
	virtual IZoneList*  GetZones(){ return &m_zones; }

	int GetMinLength();
	virtual void toString(CString &str);

private:
	vector<DreamRecord> m_dreams;
	int m_selected;
	int m_map_width, m_map_height;
	DMPlaceList m_places;
	DMMapLayer m_layers[DM_LAYERS];
	DMZoneList m_zones;
};

#endif // !defined(AFX_DREAMJOURNAL_H__417C5963_A1B3_4978_A057_99C816DA58EE__INCLUDED_)
