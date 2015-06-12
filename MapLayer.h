// MapLayer.h: interface for the MapLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPLAYER_H__EF9B9D35_9CD9_4DF7_8610_B8D5F4D0CB2A__INCLUDED_)
#define AFX_MAPLAYER_H__EF9B9D35_9CD9_4DF7_8610_B8D5F4D0CB2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DMLib\\IMapLayer.h"
#include "DMlib\\IZoneList.h"


#define COS_30 0.86602540378443864676372317075294

class CMapLayer  
{
public:
	BOOL m_bGrid;
	void SetSize(int sx, int sy);
	int GetWidth(int size);
	int GetHeight(int size);
	void SelectCell(RECT r, int size, int px, int py);
	void DrawLayer(HDC hDC, const int x, const int y, const RECT &r, const int size, IMapLayer *layer, IZoneList *zl);
	
	CMapLayer(int xs, int ys);
	CMapLayer();
	virtual ~CMapLayer();

	void GetCurPoint(CPoint &p) { p.x = Int2MapX(m_x_sel); p.y = Int2MapY(m_y_sel); }
	void Map2Disp(CPoint &c, int size);

private:
	int Int2MapX(int x){ return x - (m_xsize-1)/2; }
	int Int2MapY(int y){ return y - (m_ysize-1)/2; }
	int Map2IntX(int x){ return x + (m_xsize-1)/2; }
	int Map2IntY(int y){ return y + (m_ysize-1)/2; }
	
	
	int m_ysize;
	int m_xsize;

	int m_x_sel;
	int m_y_sel;
};

#endif // !defined(AFX_MAPLAYER_H__EF9B9D35_9CD9_4DF7_8610_B8D5F4D0CB2A__INCLUDED_)
