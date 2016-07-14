#pragma once
#include <windows.h>
#include <vector>

#include "mouse_tracker_t.h"
#include "canvas2_t.h"


struct context_t :
		public mouse_tracker_wheel_i
{
	canvas2_t canvas;
	mouse_tracker_t tracker;
	HWND frame;
	
	struct {
		int cols, rows;
		int gap;
	} layout;
	
	context_t()
	:	frame(NULL)
	{
		const int offset = 8;
		
		layout.cols = 2;
		layout.rows = 2;
		layout.gap = 4;
		
		canvas.r.offset(16 + offset, 16 + offset);
		update_canvas();
		
		tracker.grid.set_offsets(offset, offset);
		tracker.grid.set_layout(60+2, 45+2);
		tracker.grid.set_cell_size(16, 16);
		
		//~ add_corner_dots();
		
		tracker.wheel_listeners.push_back(this);
	}
	
	void update_canvas()
	{
		canvas.layout.setup(
			layout.cols, layout.rows, layout.gap);
	}
	
	virtual void on_mouse_wheel(int x, int y, int delta, int keys)
	{
		const int max_cols = 12, max_rows = 12;
		
		int inc = delta > 0 ? +1 : -1;
		
		if((inc < 0 && layout.cols > 1 && layout.rows > 1)
			|| (inc > 0 && layout.cols < max_cols
			&& layout.rows < max_rows))
		{
			layout.cols += inc;
			layout.rows += inc;
		
			update_canvas();
			
			InvalidateRect(frame, NULL, TRUE);
			UpdateWindow(frame);
		}
	}
};
