#pragma once
#include <windows.h>

#include "temp_color_setter_t.h"
#include "dot_t.h"


struct canvas_t
{
	int x, y, w, h;
	dot_t::vector dots;
	
	canvas_t()
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
	
	void draw_area(HDC hdc)
	{
		temp_color_setter_t cs(hdc);
		cs.fg(false);
		cs.bg(RGB(255,255,255));
		
		RoundRect(hdc, x, y, x+w+1, y+h+1, 16, 16);
	}
	
	void draw_border(HDC hdc)
	{
		temp_color_setter_t cs(hdc);
		cs.fg(RGB(0,0,0));
		cs.bg(false);
		
		RoundRect(hdc, x, y, x+w+1, y+h+1, 16, 16);
	}
};
