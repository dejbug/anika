#pragma once
#include <windows.h>

#include "error_t.h"
#include "errors.h"
#include "rect_t.h"


struct box_layout_t
{
	rect_t::vector boxes;
	int cols, rows;
	int cell_width, cell_height, gap;
	int roundness;
	
	static bool allow_rounding_errors;
	
	box_layout_t() :
		cols(1), rows(1),
		roundness(0)
	{
	}
	
	void draw(HDC hdc)
	{
		for(rect_t::vector::iterator it=boxes.begin();
				it<boxes.end(); ++it)
			draw_rect(hdc, *it, roundness);
	}
	
	void setup(const rect_t& r, int cols, int rows, int gap=0)
	{
		boxes.clear();
		
		if(cols <= 0 || rows <= 0)
			throw error_t(err::ARGS);
		
		if(!allow_rounding_errors)
			if(r.w % cols != 0 || r.h % rows != 0)
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
					rect_t(cx+gap, cy+gap, cw-gap-gap, ch-gap-gap));
			}
		
		this->cols = cols;
		this->rows = rows;
		this->cell_width = cw;
		this->cell_height = ch;
		this->gap = gap;
	}
	
	void reset()
	{
		boxes.clear();
	}
};


bool box_layout_t::allow_rounding_errors = true;
