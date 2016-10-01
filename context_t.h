#pragma once
#include <windows.h>
#include <vector>

#include "error_t.h"
#include "multi_tracker_t.h"
#include "canvas3_t.h"
#include "box_layout2_t.h"
#include "box_layout_merger_t.h"
#include "rect_t.h"
#include "win.h"


struct context_t :
		public mouse_tracker_wheel_i,
		public dnd_tracker_drops_i,
		public box_layout_listener2_i,
		public box_layout_merge_i
{
	HWND frame;
	box_layout2_t layout;
	canvas3_t canvas;
	mouse_grid_t grid;
	multi_tracker_t tracker;
	box_layout_merger_t box_merger;
	
	const int max_cols, max_rows;
	
	const int client_offset_to_grid;
	const int grid_cell_offset_to_canvas;
	const int grid_cell_size;
	
	context_t() :
		frame(NULL),
		canvas(layout, 12),
		box_merger(layout),
		max_cols(12),
		max_rows(12),
		client_offset_to_grid(8),
		grid_cell_offset_to_canvas(1),
		grid_cell_size(16)
	{
		const int full_offset = client_offset_to_grid +
			grid_cell_offset_to_canvas * grid_cell_size;
		
		canvas.bounds.offset(full_offset, full_offset);
		layout.setup(canvas.bounds, 1, 1, 6);
		recalc_grid_layout();
		
		tracker.mouse.wheel.push_back(this);
		tracker.mouse.move.push_back(&layout);
		tracker.dnd.listeners.push_back(this);
		
		layout.listeners2.push_back(this);
		
		tracker.mouse.click.push_back(&box_merger);
		layout.listeners2.push_back(&box_merger);
		
		box_merger.listeners.push_back(this);
	}
	
	void update_canvas()
	{
		try {
			canvas.layout.setup(canvas.bounds,
				layout.grid.cols,
				layout.grid.rows,
				layout.grid.gap);
			
			recalc_grid_layout();
		}
		catch(error_t& e)
		{
			print_error(e);
		}
	}
	
	void recalc_grid_layout()
	{
		if(layout.grid.cw <= 0 ||
				layout.grid.ch <= 0)
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
	
	void on_pre_grid_draw(HDC hdc)
	{	
		layout.draw_areas(hdc);
	}
	
	void on_post_grid_draw(HDC hdc)
	{	
		layout.draw_frames(hdc);
	}
	
	virtual void on_mouse_wheel(int x, int y, int delta, int keys)
	{
		const int inc = delta > 0 ? +1 : -1;
		
		const bool can_decrease = layout.grid.cols > 1 &&
			layout.grid.rows > 1;
			
		const bool can_increase = layout.grid.cols < max_cols &&
			layout.grid.rows < max_rows;
		
		if((inc < 0 && can_decrease) || (inc > 0 && can_increase))
		{
			layout.grid.cols += inc;
			layout.grid.rows += inc;
			
			update_canvas();
			layout.last_hilit_box = -1;
			win::repaint_window(frame);
		}
	}
	
	virtual void on_enter_box(int index, int col, int row)
	{
		win::repaint_window(frame);
	}
	
	virtual void on_leave_box(int index, int col, int row)
	{
		win::repaint_window(frame);
	}
	
	virtual void on_drop(int x, int y,
			std::vector<std::string>& names)
	{
		printf("* dropped %d files at (%d:%d)\n",
			names.size(), x, y);
		
		int n = 0;
		
		for(auto it=names.begin(); it<names.end(); ++it, ++n)
			printf(" - %d '%s'\n", n+1, it->c_str());
	}
	
	virtual void on_merge(int src, int dst)
	{
		printf("\t\t\t\t\t\r");
		printf("merge %d -> %d\n", src, dst);
		
		/// are boxes neighbors?
		if(
				src + 1 == dst ||
				src - 1 == dst ||
				src + layout.grid.cols == dst ||
				src - layout.grid.cols == dst
				)
		{
			printf(" ok\n");
			
			int const a = src < dst ? src : dst;
			int const b = src < dst ? dst : src;
			
			layout.boxes[a].r = layout.boxes[b].r;
			layout.boxes[a].b = layout.boxes[b].b;
			layout.boxes[b] = rect_t();
			
			win::repaint_window(frame);
		}
	}
};
