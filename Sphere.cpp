// Sphere.cpp: implementation of the CSphere class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sphere.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSphere::CSphere()
{

}

CSphere::~CSphere()
{

}


static inline int lin(int x, int x0, int x1, int y0, int y1) 
{
	return (y1-y0)*(x-x0)/(x1-x0)+y0;
}

void CSphere::DrawSphere(HDC hDC, int x1, int y1, int x2, int y2, COLORREF color, BOOL bflat)
{

#ifndef _WIN32_WCE
if(!bflat)
{
	int cnt = min(64, min(x2-x1, y2-y1));

	double xstep1 = 0.4*abs(x2-x1)/(cnt);
	double ystep1 = 0.4*abs(y2-y1)/(cnt);
	double xstep2 = 0.6*abs(x2-x1)/(cnt);
	double ystep2 = 0.6*abs(y2-y1)/(cnt);
	HPEN hPen = (HPEN)GetStockObject(NULL_PEN);
	hPen = (HPEN)SelectObject(hDC, hPen);

/*
	BYTE minR = GetRValue(color)/3;
	BYTE minG = GetGValue(color)/3;
	BYTE minB = GetBValue(color)/3;
*/
	BYTE minR = GetRValue(color)/2;
	BYTE minG = GetGValue(color)/2;
	BYTE minB = GetBValue(color)/2;
/*
	BYTE minR = GetRValue(color) - GetRValue(color)/3;
	BYTE minG = GetGValue(color) - GetGValue(color)/3;
	BYTE minB = GetBValue(color) - GetBValue(color)/3;
*/
	BYTE maxR = GetRValue(color);
	BYTE maxG = GetGValue(color);
	BYTE maxB = GetBValue(color);

	for(int i = 0; i < cnt; i++)
	{		
		COLORREF c=RGB(
				lin(i,1,cnt,minR, maxR),
				lin(i,1,cnt,minG, maxG),
				lin(i,1,cnt,minB, maxB)
		);
		int dx1 = int(i * xstep1);
		int dy1 = int(i * ystep1);
		int dx2 = int(i * xstep2);
		int dy2 = int(i * ystep2);

		HBRUSH hBr = CreateSolidBrush(c);
		HBRUSH hOld = (HBRUSH)SelectObject(hDC, hBr);
		Ellipse(hDC, x1 + dx1, y1 + dy1, x2 - dx2, y2 - dy2);
		SelectObject(hDC, hOld);
		DeleteObject(hBr);
	}
	SelectObject(hDC, hPen);
}
else
#endif
{

   HBRUSH br = CreateSolidBrush(color);
   HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, br);
   HPEN pen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
   HPEN hOldPen = (HPEN)SelectObject(hDC, pen);
   Ellipse(hDC, x1, y1, x2, y2);
   SelectObject(hDC, hOldBrush);
   SelectObject(hDC, hOldPen);
}
}
