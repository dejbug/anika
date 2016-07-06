#pragma once
#include <windows.h>

#include "canvas_t.h"
#include "mouse_tracker_t.h"


struct context_t
{
	canvas_t canvas;
	mouse_tracker_t tracker;
	
	context_t()
	{
		const int offset = 8;
		
		canvas.x = canvas.y = 16 + offset;
		
		tracker.grid.set_offsets(offset, offset);
		tracker.grid.set_layout(60+2, 45+2);
		tracker.grid.set_cell_size(16, 16);
		
		//~ add_corner_dots();
	}
	
private:
	void add_corner_dots()
	{
		canvas.dots.push_back(
			dot_t(canvas.x,canvas.y));
		canvas.dots.push_back(
			dot_t(canvas.x+canvas.w,canvas.y));
		canvas.dots.push_back(
			dot_t(canvas.x,canvas.y+canvas.h));
		canvas.dots.push_back(
			dot_t(canvas.x+canvas.w,canvas.y+canvas.h));
	}
};

