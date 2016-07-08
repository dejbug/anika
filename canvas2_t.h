#pragma once
#include <windows.h>

#include "temp_color_setter_t.h"
#include "dot_t.h"


struct canvas2_t
{
	int x, y, w, h;
	dot_t::vector dots;
	
	canvas2_t()
	{
		x = y = 0;
		w = 960;
		h = 720;
	}
	
	void draw(HDC hdc)
	{
		draw_area(hdc);
		draw_border(hdc);
	}
	
	void draw_area(HDC hdc, COLORREF c=RGB(255,255,255))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(false, true);
		cs.bg(c);
		
		RoundRect(hdc, x, y, x+w+1, y+h+1, 16, 16);
	}
	
	void draw_border(HDC hdc, COLORREF c=RGB(0,0,0))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(true, false);
		cs.fg(c);
		
		RoundRect(hdc, x, y, x+w+1, y+h+1, 16, 16);
	}
};
