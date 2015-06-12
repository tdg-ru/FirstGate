// IDreamList.h: interface for the IDreamList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDREAMLIST_H__6C3C5DF3_B460_4F5E_A808_AC15596356FB__INCLUDED_)
#define AFX_IDREAMLIST_H__6C3C5DF3_B460_4F5E_A808_AC15596356FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDreamRecord.h"

class IDreamList  
{
public:
	virtual ~IDreamList(){}

	virtual int GetDreamsCount() = 0;	// кол-во снов
	virtual IDreamRecord* GetDreamByPos(int pos) = 0; // сон по позиции в списке
	virtual void SelectDreamPos(int pos) = 0; // пометить сон
	virtual int GetSelectedPos() = 0;	  // получить id выделенного
	virtual IDreamRecord* GetSelected() = 0; 

	virtual int Add(IDreamRecord &dream) = 0; // возвращает id - нового сна
	virtual int Add() = 0; // возвращает id - нового сна
	virtual void Delete(int pos) = 0;		 // удаляет сон из позиции
	virtual void DeleteAll() = 0;			 // удалить все записи

	virtual bool SortByDate(BOOL gr = TRUE) = 0; // отсортировать по дате
};

#endif // !defined(AFX_IDREAMLIST_H__6C3C5DF3_B460_4F5E_A808_AC15596356FB__INCLUDED_)
