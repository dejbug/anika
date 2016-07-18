#pragma once
#include <windows.h>
#include <vector>

#include "error_t.h"
#include "mouse_tracker_t.h"
#include "canvas2_t.h"
#include "win.h"


struct context_t : public mouse_tracker_wheel_i
{
	HWND frame;
	canvas2_t canvas;
	mouse_grid_t grid;
	mouse_tracker_t tracker;
	
	const int max_cols, max_rows;
	const int resolution;
	const int offset, extra;
	
	context_t() :
		frame(NULL),
		canvas(12),
		max_cols(12), max_rows(12),
		resolution(16),
		offset(8),
		extra(1)	/// extra cols/rows as framing
	{
		const int full_offset = offset + extra * resolution;
		
		canvas.bounds.offset(full_offset, full_offset);
		canvas.layout.setup(canvas.bounds, 1, 1, 6);
		recalc_grid_layout();
		
		tracker.wheel_listeners.push_back(this);
	}
	
	void update_canvas()
	{
		try {
			canvas.layout.setup(canvas.bounds,
				canvas.layout.cols,
				canvas.layout.rows,
				canvas.layout.gap);
			
			recalc_grid_layout();
		}
		catch(error_t& e)
		{
			print_error(e);
		}
	}
	
	void recalc_grid_layout()
	{
		if(canvas.layout.cell_width <= 0 ||
				canvas.layout.cell_height <= 0)
			return;
			
		const int cols = canvas.bounds.w / resolution;
		const int rows = canvas.bounds.h / resolution;
		
		grid.set_offsets(offset, offset);
		grid.set_cell_size(resolution, resolution);
		grid.set_layout(cols + extra*2, rows + extra*2);
	}
	
	virtual void on_mouse_wheel(int x, int y, int delta, int keys)
	{
		const int inc = delta > 0 ? +1 : -1;
		
		const bool can_decrease = canvas.layout.cols > 1 &&
			canvas.layout.rows > 1;
			
		const bool can_increase = canvas.layout.cols < max_cols &&
			canvas.layout.rows < max_rows;
		
		if((inc < 0 && can_decrease) || (inc > 0 && can_increase))
		{
			canvas.layout.cols += inc;
			canvas.layout.rows += inc;
			
			update_canvas();
			win::repaint_window(frame);
		}
	}
};
