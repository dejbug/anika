#pragma once
#include <windows.h>
#include <map>

#include "temp_hdc_t.h"
#include "box_layout2_t.h"


struct mergers_t
{
	HWND & frame;
	box_layout2_t & layout;
	std::map<int,int> mapping;

	mergers_t(HWND & frame, box_layout2_t & layout) :
		frame(frame),
		layout(layout)
	{
	}

	void recalc_layout()
	{
		printf("mergers::recalc_layout\n");
	}

	void join(int src, int dst)
	{
		if(layout.grid.are_neighbors(src, dst))
		{
			int const a = src < dst ? src : dst;
			int const b = src < dst ? dst : src;

			layout.boxes[a].r = layout.boxes[b].r;
			layout.boxes[a].b = layout.boxes[b].b;
			layout.boxes[b] = rect_t();

			// win::repaint_window(frame);
			temp_hdc_t hdc(frame);
			layout.draw_single_area(hdc.handle, dst);
			layout.draw_single_frame(hdc.handle, dst, true);
			layout.draw_single_area(hdc.handle, src);
			layout.draw_single_frame(hdc.handle, src, false);
		}
	}

	void split(int src, int dst)
	{
	}
};


struct box_t {

	HRGN handle;
	rect_t r;
	int roundness;

	box_t(rect_t & r, int roundness=0)
	{
		handle = CreateRoundRectRgn(r.l, r.t, r.r, r.b,
			roundness, roundness);
	}

};


struct rgn_t {

	HRGN handle;

	rgn_t(rect_t & r, int roundness=0)
	{
		handle = CreateRoundRectRgn(r.l, r.t, r.r, r.b,
			roundness, roundness);
	}
};
