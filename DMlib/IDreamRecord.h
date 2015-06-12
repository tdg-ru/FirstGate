#include "DMxml.h"
#include "DMDescription.h"
#include "IPlaceList.h"

#ifndef IDREAM_RECORD_H
#define IDREAM_RECORD_H


#define DM_DREAM_TYPE_CNT 5

// Типы сновидений
enum DM_DREAM_TYPE
{
	DREAM_UNKNOWN = 0,			// Неизвестно
	DREAM_DELIRIOUS_LOOP = 1,	// Бредовая петля
	DREAM_SPEACH = 2,			// 100%-я болтовня
	DREAM_ACTION = 3,			// сон с элементами действия
	DREAM_LUCID = 4,			// "прозрачное сновидение"
	DREAM_OC = 5,				// ОС
	DREAM_ERROR = 6	
};

DM_DREAM_TYPE GetTypeID(CString &s);

// Структура для хранения информации о дате в программе для картографирования
struct DMDate: public DMxml
{
	int day, month, year; // Дата
	int hour, minute;	  // Время
	DMDate()
	{
		day = month = year = hour = minute = 0; 
	}
	void FromSysTime(SYSTEMTIME &s)
	{
		day   = s.wDay;
		month = s.wMonth;
		year  = s.wYear;
		hour  = s.wHour;
		minute = s.wMinute;
	}
	bool operator>(const DMDate& d) const 
	{
		if(year == d.year)
		{
			if(month == d.month)
			{
				if(day == d.day)
					return FALSE;
				else
					return (day > d.day);
			}
			else
				return (month>d.month);
		}
		else
			return (year>d.year);
		return false;
		
	}
	bool operator<(const DMDate& d) const
	{
		if(year == d.year)
		{
			if(month == d.month)
			{
				if(day == d.day)
					return FALSE;
				else
					return (day < d.day);
			}
			else
				return (month < d.month);
		}
		else
			return (year < d.year);
		return false;
	}

	void toString(CString &str)
	{
		CString tmp;
		tmp.Format(_T("<date value=\"%4d-%02d-%02d\">%02d.%02d.%4d</date>\r\n"),
			year, month, day, day, month, year);
		str += tmp;
	}	

	virtual int GetMinLength(){ return 120; }
};

// Интерфейс для работы со сном
// У сна есть:
//  - название
//  - дата
//  - тип
//  - описание
//  - комментарии
//  - список мест, посещенных в сновидении
//  - изображение  - зарезервировано для реализации позже
class IDreamRecord
{
public:
	// Конструктор и деструктор
	IDreamRecord(){};
	virtual ~IDreamRecord(){};

        // Получение информации
        virtual LPCTSTR 	GetTitle() const = 0;
        virtual DM_DREAM_TYPE 	GetType()  const = 0; 
        virtual LPCTSTR 	GetExtType() const  = 0;
        virtual const DMDate* 	GetDate()  const = 0;
        virtual const DMDescription* GetDescription()  const = 0;
        virtual const DMDescription* GetComment()  const = 0;

        // Установка
        virtual void SetTitle(LPCTSTR) = 0;
        virtual void SetType(const DM_DREAM_TYPE) = 0;
        virtual void SetExtType(LPCTSTR) = 0;
        virtual void SetDate(const DMDate*) = 0;
        virtual void SetDescription(const DMDescription*) = 0;
        virtual void SetComment(const DMDescription*) = 0;
		virtual void Copy(IDreamRecord *) = 0; 
		virtual IPlaceList* GetPlaces() = 0;
};

#endif /*IDREAM_RECORD_H*/
