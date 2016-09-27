#pragma once
#include "rect_t.h"


struct grid_t
{
	rect_t bounds;
	int cols, rows;
	int cw, ch, gap;
	
	grid_t()
	{
		reset();
	}
	
	void setup(const rect_t& r, int cols, int rows, int gap=0)
	{
		reset();
		
		cw = r.w / cols;
		ch = r.h / rows;
		
		if(cw <= 0 || ch <= 0)
			throw error_t(err::ARGS);
		
		bounds = r;
		this->cols = cols;
		this->rows = rows;
		this->gap = gap;
	}
	
	void reset()
	{
		bounds = rect_t();
		cols = rows = gap = 0;
		cw = ch = 0;
	}
};
