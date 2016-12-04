#pragma once
#include <windows.h>
#include <vector>

#include "temp_color_setter_t.h"
#include "color_t.h"


struct dot_t
{
	typedef std::vector<dot_t> vector;
	
	int x, y;
	int r;
	
	dot_t(int x, int y) :
		x(x), y(y), r(6)
	{
	}
	
	void draw(HDC hdc)
	{
		//~ RECT rc = {x-r, y-r, x+r, y+r};
		//~ FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		
		temp_color_setter_t cs(hdc);
		cs.fg(30,30,30);
		cs.bg(200,200,200);
		
		Ellipse(hdc, x-r, y-r, x+r, y+r);
	}
};



void draw_dots(HDC hdc, dot_t::vector& dots)
{
	for(dot_t::vector::reverse_iterator it=dots.rbegin();
		it<dots.rend(); ++it)
	{
		it->draw(hdc);
	}
}
