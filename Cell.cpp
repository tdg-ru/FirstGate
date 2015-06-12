// Cell.cpp: implementation of the CCell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cell.h"
#include "Sphere.h"

#include <windows.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCell::CCell()
{
	cBorder = RGB(192,192,192);
	cBack	= RGB(255,255,240);
	cColor  = RGB(0,255,0);

	m_size = -1;
}

CCell::CCell(const CCell &c)
{
	cBorder = c.cBorder;
	cBack	= c.cBack;
	cColor  = c.cColor;
	for(int i = 0; i < 7; i++)
		m_pnt[i]   = c.m_pnt[i];
	m_size  = c.m_size;
	m_sx	= c.m_sx;
	m_sy	= c.m_sy;
}

CCell::~CCell()
{

}

void CCell::SetSize(int bx, int by, int size, int sx, int sy)
{
	m_size = size;
	m_sx = sx;
	m_sy = sy;

	int size2 = int(0.5 * m_size);

	m_pnt[0].y = m_pnt[6].y = m_pnt[1].y = by;
	m_pnt[5].y = m_pnt[2].y = by + sy;
	m_pnt[4].y = m_pnt[3].y = m_pnt[5].y + sy;

	m_pnt[0].x = m_pnt[6].x = m_pnt[4].x = bx;
	m_pnt[1].x = m_pnt[3].x = bx + size;
	m_pnt[2].x = m_pnt[3].x + size2;
	m_pnt[5].x = bx - size2;	
}

void CCell::Draw(HDC hDC, int x, int y, BOOL empty)
{
	const int cnt = 7;

	int xc =     m_sx * x;
	int yc =  2* m_sy * y;

	if(x%2)
	{
		yc += m_sy;
	}

	int size2 = m_size / 2;
	xc += size2;
	
	HBRUSH hC, hBr, hOldBr;
	HPEN hPen, hOldPen; 
	hBr = CreateSolidBrush(cBack);
	hC  = CreateSolidBrush(cColor);
	
	hPen = CreatePen(PS_SOLID, 1, cBorder);
	
	hOldBr  = (HBRUSH)SelectObject(hDC, hBr);
	hOldPen = (HPEN)SelectObject(hDC, hPen);

	POINT pnt[7];
	for(int i = 0; i < cnt; i++)
	{
		pnt[i].x = m_pnt[i].x + xc;
		pnt[i].y = m_pnt[i].y + yc;
	}	
	
	PolyPolygon(hDC, pnt, &cnt, 1);

	if(!empty)
	{
		CSphere::DrawSphere(hDC, pnt[0].x + size2 - m_sy + 1, pnt[0].y + 1, 
			pnt[3].x - size2 + m_sy, pnt[3].y, cColor);
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBr);
	DeleteObject(hBr);
	DeleteObject(hPen);
	DeleteObject(hC);
}

BOOL CCell::Check(int px, int py, int x, int y)
{
	int xc =     m_sx * x;
	int yc =  2* m_sy * y;

	if(x%2)
	{
		yc += m_sy;
	}

	int size2 = m_size / 2;
	xc += size2;


	int x0, x2, x3, x5;
	int y0, y2, y3, y5;
	
	double yi, ya;

	x0 = m_pnt[0].x + xc;
	x2 = m_pnt[2].x + xc;
	x3 = m_pnt[3].x + xc;
	x5 = m_pnt[5].x + xc;

	y0 = m_pnt[0].y + yc;
	y2 = m_pnt[2].y + yc;
	y3 = m_pnt[3].y + yc;
	y5 = m_pnt[5].y + yc;
	

	if(py < y0 || py > y3 || px < x5 || px > x2)
		return FALSE;

	if(px >= x0 && px <= x3)
		return TRUE;

	if(px < x0)
	{
		yi = double(x0 - px) / double(size2) * m_sy;
	}
	else
	{
		yi = double(px - x3) / double(size2) * m_sy;
	}
	ya = y3 - yi;
	yi += y0;
	if(py >= yi && py <= ya)
		return TRUE;
	return FALSE;
}

/*
void CCell::Draw(HDC hDC, int xb, int yb, int size, int sx, int sy, int m_x, int m_y)
{
	int xc, yc;
	xc = xb + 2*sx * m_x;
	yc = yb + m_y * sy;

	if(m_y%2)
	{
		xc += sx;
	}

	HBRUSH hC, hBr, hOldBr;
	HPEN hPen, hOldPen; 
	hBr = CreateSolidBrush(cBack);
	hC  = CreateSolidBrush(cColor);
	
	hPen = CreatePen(PS_SOLID, 1, cBorder);
	
	hOldBr  = (HBRUSH)SelectObject(hDC, hBr);
	hOldPen = (HPEN)SelectObject(hDC, hPen);

	POINT pnt[7];

	int size2 = int(0.5 * size);
	yc += size2;

	pnt[0].x = pnt[6].x = pnt[5].x = xc;
	pnt[1].x = pnt[4].x = xc + sx;
	pnt[2].x = pnt[3].x = pnt[1].x + sx;

	pnt[0].y = pnt[6].y = pnt[2].y = yc;
	pnt[5].y = pnt[3].y = yc + size;
	pnt[4].y = pnt[3].y + size2;
	pnt[1].y = yc - size2;	

	int cnt = 7;
	PolyPolygon(hDC, pnt, &cnt, 1);

	if(!this->isEmpty)
	{
		/*
		SelectObject(hDC, GetStockObject(NULL_PEN));
		SelectObject(hDC, hC);
		Ellipse(hDC, pnt[0].x+1, pnt[3].y - 0.5*size - sx+1, 
				 pnt[2].x+1, pnt[3].y - 0.5*size + sx+1);
		*/
/*
		CSphere::DrawSphere(hDC, pnt[0].x+1, pnt[3].y - 0.5*size - sx+1, 
				 pnt[2].x+1, pnt[3].y - 0.5*size + sx+1, cColor);
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBr);
	DeleteObject(hBr);
	DeleteObject(hPen);
	DeleteObject(hC);
}
*/

/*
BOOL CCell::IsThatCell(int size, int sx, int sy, int px, int py)
{
	int xc, yc;
	xc = 2*sx * m_x;
	yc = m_y * sy;

	if(m_y%2)
	{
		xc += sx;
	}

	int x0, x1, x3, x4;
	int y0, y1, y3, y4;
	
	double xi, xa;

	int size2 = int(0.5 * size);
	
	yc += size2;

	x0 = xc;
	x1 = x4 = xc + sx;
	x3 = x1 + sx;

	y0 = yc;
	y1 = yc - size2;
	y3 = yc + size;
	y4 = y3 + size2;
	


	if(py < y1 || py > y4 || px < x0 || px > x3)
		return FALSE;

	if(py >= y0 && py <= y3)
		return TRUE;

	if(py < y0)
	{
		xi = double(y0 - py) / double(size2) * sx;
	}
	else
	{
		xi = double(py - y3)  / double(size2) * sx;
	}

	xa = x3 - xi;
	xi += x0;
	if(px >= xi && px <= xa)
		return TRUE;
	
	return FALSE;
}
*/