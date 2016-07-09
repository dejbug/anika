#pragma once
#include <windows.h>

#include "canvas_t.h"
#include "temp_color_setter_t.h"
#include "rect_t.h"


struct canvas2_t : public canvas_t
{
	const int roundness;
	rect_t::vector boxes;
	
	canvas2_t()
	:	roundness(16)
	{
	}
	
	void draw_area(HDC hdc, COLORREF c=RGB(255,255,255))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(false, true);
		cs.bg(c);
		
		for(rect_t::vector::iterator it=boxes.begin();
				it<boxes.end(); ++it)
			draw_rect(hdc, *it, roundness);
	}
	
	void reset()
	{
		boxes.clear();
		boxes.push_back(rect_t(x, y, w, h));
	}
	
};

