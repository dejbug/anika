#pragma once
#include <windows.h>

#include "error_t.h"
#include "errors.h"
#include "rect_t.h"


struct box_layout_t
{
	int roundness;
	rect_t& r;
	rect_t::vector boxes;
	
	box_layout_t(rect_t& r)
	:	roundness(0), r(r)
	{
	}
	
	void draw(HDC hdc)
	{
		for(rect_t::vector::iterator it=boxes.begin();
				it<boxes.end(); ++it)
			draw_rect(hdc, *it, roundness);
	}
	
	void setup(int cols, int rows, int gap=0)
	{
		boxes.clear();
		
		if(cols <= 0 || rows <= 0)
			throw error_t(err::ARGS);
		
		const int cw = r.w / cols;
		const int ch = r.h / rows;
		
		if(cw <= 0 || ch <= 0)
			throw error_t(err::ARGS);
		
		int cx = r.x, cy = r.y;
		
		for(int i=0, cx=r.x; i<cols; ++i, cx+=cw)
			for(int j=0, cy=r.y; j<rows; ++j, cy+=ch)
			{
				boxes.push_back(
					rect_t(cx+gap, cy+gap, cw-gap, ch-gap));
			}
	}
	
	void reset()
	{
		boxes.clear();
	}
};
