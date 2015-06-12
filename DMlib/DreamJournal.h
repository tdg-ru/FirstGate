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
	// ћетоды чтени€/редактировани€
	virtual int GetDreamsCount();	// кол-во снов
//	virtual int GetFirstDreamID();	// первый сон
//	virtual int GetNextDreamID(int id);	// следующий сон (-1 - конец)
	virtual IDreamRecord* GetDreamByPos(int pos); // сон по идентификатору

	// ¬ыделение
	virtual void SelectDreamPos(int pos); // пометить сон
	virtual int GetSelectedPos();	  // получить id выделенного
	virtual IDreamRecord* GetSelected(); 
	
	// ћетоды добавлени€/удалени€
	virtual int Add(IDreamRecord &dream); // возвращает id - нового сна
	virtual int Add(); // возвращает id - нового сна
	virtual void Delete(int id);		 // удал€ет сон с id
	virtual void DeleteAll();			 // удалить все записи

	// ћетоды сортировки и поиска
	// ѕосле сортировки или поиска, новый список можно получить методами
	// GetFirst, GetNext
	virtual bool SortByDate(BOOL gr = TRUE); // отсортировать по дате

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
