#pragma once
#include <windows.h>

#include "temp_color_setter_t.h"
#include "rect_t.h"


struct canvas_t
{
	rect_t bounds;
	
	canvas_t() :
		bounds(0,0,960,720)
	{
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
		
		draw_rect(hdc, bounds, 16);
	}
	
	void draw_border(HDC hdc, COLORREF c=RGB(0,0,0))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(true, false);
		cs.fg(c);
		
		draw_rect(hdc, bounds, 16);
	}
};
