#pragma once
#include <windows.h>
#include <vector>

#include "error_t.h"
#include "mouse_tracker_t.h"
#include "canvas2_t.h"
#include "win.h"


struct context_t :
		public mouse_tracker_wheel_i,
		public box_layout_listener2_i
{
	HWND frame;
	canvas2_t canvas;
	mouse_grid_t grid;
	mouse_tracker_t tracker;
	
	const int max_cols, max_rows;
	
	const int client_offset_to_grid;
	const int grid_cell_offset_to_canvas;
	const int grid_cell_size;
	
	context_t() :
		frame(NULL),
		canvas(12),
		max_cols(12),
		max_rows(12),
		client_offset_to_grid(8),
		grid_cell_offset_to_canvas(1),
		grid_cell_size(16)
	{
		const int full_offset = client_offset_to_grid +
			grid_cell_offset_to_canvas * grid_cell_size;
		
		canvas.bounds.offset(full_offset, full_offset);
		canvas.layout.setup(canvas.bounds, 1, 1, 6);
		recalc_grid_layout();
		
		tracker.wheel_listeners.push_back(this);
		tracker.move_listeners.push_back(&canvas.layout);
		canvas.layout.listeners2.push_back(this);
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
			
		const int cols = canvas.bounds.w / grid_cell_size;
		const int rows = canvas.bounds.h / grid_cell_size;
		
		grid.set_offsets(
			client_offset_to_grid,
			client_offset_to_grid);
			
		grid.set_cell_size(grid_cell_size, grid_cell_size);
		
		grid.set_layout(
			cols + grid_cell_offset_to_canvas*2,
			rows + grid_cell_offset_to_canvas*2);
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
	
	virtual void on_enter_box(int index, int col, int row)
	{
		printf("%3d - %3d:%d   \r",
			index, col, row);
	}
	
	virtual void on_leave_box(int index, int col, int row)
	{
		printf("\t\t\t\t\t\r");
	}
	
};
