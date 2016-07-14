#pragma once
#include <windows.h>

#include "canvas_t.h"
#include "temp_color_setter_t.h"
#include "box_layout_t.h"


struct canvas2_t : public canvas_t
{
	box_layout_t layout;
	
	canvas2_t()
	:	layout(r)
	{
		layout.roundness = 2;
	}
	
	void draw_area(HDC hdc, COLORREF c=RGB(255,255,255))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(false, true);
		cs.bg(c);
		
		layout.draw(hdc);
	}
	
	void draw_border(HDC hdc, COLORREF c=RGB(0,0,0))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(true, false);
		cs.fg(c);
		
		layout.draw(hdc);
	}
};

