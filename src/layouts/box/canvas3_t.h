#pragma once
#include <windows.h>

#include "canvas2_t.h"
#include "temp_color_setter_t.h"
#include "box_layout2_t.h"
#include "mouse_grid_t.h"


struct canvas3_t : public canvas2_t
{
	box_layout2_t& layout;
	
	canvas3_t(box_layout2_t& layout, int roundness=2) :
		layout(layout)
	{
		layout.roundness = roundness;
	}
	
	void draw_area(HDC hdc, COLORREF c=RGB(255,255,255))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(false, true);
		cs.bg(c);
		
		layout.draw_areas(hdc);
	}
	
	void draw_border(HDC hdc, COLORREF c=RGB(0,0,0))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(true, false);
		cs.fg(c);
		
		layout.draw_frames(hdc);
	}
};

