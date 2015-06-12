// MapLayer.cpp: implementation of the MapLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapLayer.h"
#include "Cell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapLayer::CMapLayer(int xs, int ys)
{
	m_xsize = xs;
	m_ysize = ys;
	m_x_sel = xs+1;
	m_y_sel = ys+1;
	SetSize(xs, xs);

	m_bGrid = TRUE;
}

CMapLayer::CMapLayer()
{
	m_xsize = 0;
	m_ysize = 0;
	m_x_sel = -1;
	m_y_sel = -1;

	m_bGrid = TRUE;
}

CMapLayer::~CMapLayer()
{

}

void CMapLayer::SetSize(int xs, int ys)
{
	m_xsize = xs;
	m_ysize = ys;
}


void CMapLayer::DrawLayer(HDC hDC, const int x, const int y, const RECT &r, const int size, IMapLayer *layer, IZoneList *zl)
{
	int xi, yi, xa, ya;

	int width  = r.right - r.left;
	int height = r.bottom - r.top;

	int mw = GetWidth(size);
	int mh = GetHeight(size);

	int ystep = int(size * COS_30);
	int ystep2 = 2 * ystep;
	int xstep = int(1.5 * size);

	xi = max(int(double(r.left) / (xstep)) - 1, 0);
	yi = max(int(double(r.top / ystep2)) - 1, 0);
	xa = min(int(double(r.right) / (xstep)) + 5, m_xsize);
	ya = min(int(double(r.bottom / ystep2)) + 5, m_ysize);

	CCell cell;
	cell.SetSize(-r.left, -r.top, size, xstep, ystep);

	HDC hMemoryDC = CreateCompatibleDC(hDC);
	HBITMAP hBmp  = CreateCompatibleBitmap(hDC, width, height);
	::SelectObject(hMemoryDC, hBmp);
	RECT re = {0, 0, width, height};
	HBRUSH hBr = (HBRUSH)GetStockObject(WHITE_BRUSH);
	FillRect(hMemoryDC, &re, hBr);
	IPlace *p = NULL;
	IPlace *z = NULL;
	for(int i = yi;  i < ya; i++)
	{
		for(int j = xi; j < xa;  j++)
		{
			if(j%2 && i == m_ysize-1)
				continue;

			int map_x = Int2MapX(j);
			int map_y = Int2MapY(i);
			
			if(layer)
			{
				p = layer->GetPlace(map_x, map_y);		
				if(zl)
					z = zl->GetPlace(layer->GetLayerId(), map_x, map_y);
			}
			if(z)
			{
				z->GetColor(cell.cBack);
			}
			else
				cell.cBack = RGB(255,255,255);
			if(!m_bGrid)
				cell.cBorder = cell.cBack;

			if(p)
			{
				p->GetColor(cell.cColor);
				cell.Draw(hMemoryDC, j, i, FALSE);
			}
			else
				cell.Draw(hMemoryDC, j, i);
		}
	}
	cell.cBorder = RGB(255,0,0);
	if(layer)
	{
		p = layer->GetPlace(Int2MapX(m_x_sel), Int2MapY(m_y_sel));
		if(zl)
			z = zl->GetPlace(layer->GetLayerId(), Int2MapX(m_x_sel), Int2MapY(m_y_sel));
	}
	if(z)
	{
		z->GetColor(cell.cBack);
	}
	else
		cell.cBack = RGB(255,255,255);
	if(p)
	{
		p->GetColor(cell.cColor);
		cell.Draw(hMemoryDC, m_x_sel, m_y_sel, FALSE);
	}
	else
		cell.Draw(hMemoryDC, m_x_sel, m_y_sel);

	BitBlt(hDC, x, y, width, height, hMemoryDC, 0, 0, SRCCOPY);
	DeleteDC(hMemoryDC);
	DeleteObject(hBmp);
}


void CMapLayer::SelectCell(RECT r, int size, int px, int py)
{
	int ystep = int(size * COS_30);
	int xstep = int(1.5 * size);

	px += r.left;
	py += r.top;

	int xi, yi;
	xi = px / xstep;
	yi = py / (ystep * 2);

	CCell cell;
	cell.SetSize(0, 0, size, xstep, ystep);

	for(int i = max(yi-2, 0);  i < min(yi+2, m_ysize); i++)
	for(int j = max(xi-2, 0);  j < min(xi+2, m_xsize); j++)
	{
		if(j%2 && i == m_ysize-1)
			continue;

		if(cell.Check(px, py, j, i))
		{
			m_x_sel = j;
			m_y_sel = i;
			return;
		}		
	}
}


int CMapLayer::GetHeight(int size)
{
	return 2 * m_ysize * int(size * COS_30) + 1;
}

int CMapLayer::GetWidth(int size)
{
	return int(int(1.5 * size) * m_xsize + 0.5 * size + 1);	
}


void CMapLayer::Map2Disp(CPoint &c, int size)
{
	int ystep = int(size * COS_30);
	int xstep = int(1.5 * size);
	
	int x = Map2IntX(c.x) * xstep + size/2;
	int y = Map2IntY(c.y) * ystep * 2 + size/2;

	if(c.x%2)
	{
		y += xstep;
	}

	c.x = x;
	c.y = y;
}