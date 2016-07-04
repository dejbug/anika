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
		
		dot_t a(300,300), b(400,400);
		dot_t c(300,300), d(400,400);
		
		//~ MoveToEx(hdc, a.x,a.y, NULL);
		//~ LineTo(hdc, b.x,b.y);
		
		Arc(hdc, a.x,a.y,b.x,b.y,
			c.x,c.y,d.x,d.y);
		
		a.draw(hdc);
		b.draw(hdc);
		c.draw(hdc);
		d.draw(hdc);
		
	}
};
