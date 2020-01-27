#pragma once
#include <windows.h>
#include <vector>

#include "multi_tracker_t.h"
#include "box_layout2_t.h"
#include "box_layout_merger3_t.h"
#include "canvas3_t.h"
#include "merger_t.h"

#include "error_t.h"
#include "rect_t.h"
#include "temp_hdc_t.h"
#include "mdc2_t.h"
#include "win.h"

#include "context_t.h"


struct box_layout_context_t :
		public context_t<box_layout_context_t>,
		public mouse_tracker_wheel_i,
		public dnd_tracker_drops_i,
		public box_layout2_t::listener2_i,
		public box_layout_merger3_t::listener2_i,
		public box_layout_merger3_t::listener3_i
{
	constexpr static char const * const name = "LAYOUT_BOX";

	multi_tracker_t tracker;
	box_layout2_t layout;
	box_layout_merger3_t box_merger;
	merger_t merger;
	canvas3_t canvas;

	int const max_cols{12}, max_rows{12};
	int const client_offset_to_grid{8};
	int const grid_cell_offset_to_canvas{1};
	int const grid_cell_size{16};

	static void install(HINSTANCE i=nullptr)
	{
		window_class_t wc(name, callback);
		wc.hInstance = i ? i : GetModuleHandle(nullptr);
		wc.cbWndExtra = 4;	// to hold the context
		wc.install();
	}

	box_layout_context_t() :
		box_merger(layout),
		merger(frame, layout),
		canvas(layout, 12)
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

		tracker.mouse.click2.push_back(&box_merger);
		layout.listeners2.push_back(&box_merger);

		box_merger.listeners2.push_back(this);
		box_merger.listeners3.push_back(this);
	}

	void paint(HDC dc)
	{
		printf("* paint\n");

		mdc2_t mdc(dc);
		mdc.clear(COLOR_BTNFACE);

		layout.draw_areas(mdc.handle);
		layout.draw_frames(mdc.handle);

		mdc.flip();
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
		merger.recalc_layout();
	}

	virtual void on_mouse_wheel(int x, int y, int delta, unsigned int keys)
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
			win::repaint_window(frame);
		}
	}

	virtual void on_enter_box(int index, int col, int row)
	{
		// printf("* on_enter_box %d at (%d:%d)\n", index, col, row);

		// win::repaint_window(frame);
		temp_hdc_t hdc(frame);
		layout.draw_single_area(hdc.handle, index, true);
		layout.draw_single_frame(hdc.handle, index, true);
	}

	virtual void on_leave_box(int index, int col, int row)
	{
		// printf("* on_leave_box %d at (%d:%d)\n", index, col, row);

		// win::repaint_window(frame);
		temp_hdc_t hdc(frame);
		layout.draw_single_area(hdc.handle, index, false);
		layout.draw_single_frame(hdc.handle, index, false);
	}

	virtual void on_drop(int x, int y, std::vector<std::string>& names)
	{
		printf("* dropped %d files at (%d:%d)\n", names.size(), x, y);

		int n = 0;

		for(auto it=names.begin(); it<names.end(); ++it, ++n)
			printf(" - %d '%s'\n", n+1, it->c_str());
	}

	virtual void on_merge3(int button, int src, int dst)
	{
		if(button == 1)
			merger.join(src, dst);
		else if(button == 2)
			merger.split(src, dst);

		// InvalidateRect(frame, nullptr, FALSE);
		// UpdateWindow(frame);
	}

	virtual void on_merge2(int button, trace_t const & trace)
	{
		// printf("\t\t\t\t\t\r");

		for(auto it = trace.begin(); it < trace.end(); ++it)
		{
			if(trace.begin() == it)
				printf("merge-trace (button %d) %d", button, *it);
			else
				printf("->%d", *it);
		}
		printf("\n");

		InvalidateRect(frame, nullptr, TRUE);
		UpdateWindow(frame);
	}
};
