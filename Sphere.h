// Sphere.h: interface for the CSphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPHERE_H__90354406_EABB_47A6_85FB_5AA9AC5643CB__INCLUDED_)
#define AFX_SPHERE_H__90354406_EABB_47A6_85FB_5AA9AC5643CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSphere  
{
public:
	static void DrawSphere(HDC hDC, int x1, int y1, int x2, int y2, COLORREF color, BOOL bflat = FALSE);
	CSphere();
	virtual ~CSphere();

};

#endif // !defined(AFX_SPHERE_H__90354406_EABB_47A6_85FB_5AA9AC5643CB__INCLUDED_)
