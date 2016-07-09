#pragma once
#include <windows.h>

#include "dot_t.h"


struct line_t
{
	int ax, ay, bx, by;
	
	line_t(int ax, int ay, int bx, int by)
	:	ax(ax), ay(ay), bx(bx), by(by)
	{
	}
	
	void draw(HDC hdc)
	{
		MoveToEx(hdc, ax, ay, NULL);
		LineTo(hdc, bx, by);
	}
	
	void draw_dots(HDC hdc)
	{
		dot_t a(ax,ay), b(bx,by);
		a.draw(hdc);
		b.draw(hdc);
	}
};
