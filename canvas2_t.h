#pragma once
#include <windows.h>

#include "error_t.h"
#include "errors.h"
#include "canvas_t.h"
#include "temp_color_setter_t.h"
#include "rect_t.h"


struct canvas2_t : public canvas_t
{
	const int roundness;
	rect_t::vector boxes;
	
	canvas2_t()
	:	roundness(2)
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
	
	void draw_border(HDC hdc, COLORREF c=RGB(0,0,0))
	{
		temp_color_setter_t cs(hdc);
		cs.fb(true, false);
		cs.fg(c);
		
		for(rect_t::vector::iterator it=boxes.begin();
				it<boxes.end(); ++it)
			draw_rect(hdc, *it, roundness);
	}
	
	void reset()
	{
		/// equivalent to layout(1, 1);
		boxes.clear();
		boxes.push_back(rect_t(x, y, w, h));
	}
	
	void layout(int cols, int rows, int gap=0)
	{
		boxes.clear();
		
		const int cw = w / cols;
		const int ch = h / rows;
		
		if(cw <= 0 || ch <= 0)
			throw error_t(err::ARGS);
		
		int cx = x, cy = y;
		
		for(int i=0, cx=x; i<cols; ++i, cx+=cw)
			for(int j=0, cy=y; j<rows; ++j, cy+=ch)
			{
				boxes.push_back(
					rect_t(cx+gap, cy+gap, cw-gap, ch-gap));
			}
	}
};

