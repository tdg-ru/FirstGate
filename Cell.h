// Cell.h: interface for the CCell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELL_H__EBCFEE25_D8F1_42B7_A868_02C7E328CFD2__INCLUDED_)
#define AFX_CELL_H__EBCFEE25_D8F1_42B7_A868_02C7E328CFD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCell  
{
public:	
	CCell();
	CCell(const CCell &);
	virtual ~CCell();

private:
	int m_size;
	int m_sx;
	int m_sy;
	POINT m_pnt[7];
protected:
//	BOOL IsThatCell(int s, int xs, int ys, int px, int py);
//	void Draw(HDC hDC, int xb, int yb, int s, int sx, int sy, int x, int y, BOOL isEmpty = TRUE);

	void SetSize(int bx, int by, int size, int sx, int sy);
	void Draw(HDC hDC, int x, int y, BOOL empty = TRUE);
	BOOL Check(int px, int py, int x, int y);

	COLORREF cBorder;
	COLORREF cBack;
	COLORREF cColor;

friend class CMapLayer;
};

#endif // !defined(AFX_CELL_H__EBCFEE25_D8F1_42B7_A868_02C7E328CFD2__INCLUDED_)
