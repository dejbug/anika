#pragma once
#include <windows.h>
#include <vector>
#include <map>

#include "temp_hdc_t.h"
#include "box_layout2_t.h"


struct rgn_t {

	struct error_t {};
	struct create_error_t : public error_t {};

	HRGN handle;

	rgn_t(rect_t<LONG> & r, int roundness=0)
	{
		handle = CreateRoundRectRgn(r.x, r.y, r.x+r.w, r.y+r.h,
			roundness, roundness);
		if(!handle) throw create_error_t();
	}

	virtual ~rgn_t()
	{
		if(handle) DeleteObject(handle);
	}

	void merge(rgn_t & other)
	{
	}
};


struct rgns_t {

	std::vector<rgn_t> bubbles;
	std::map<int,int> links;

	rgns_t()
	{
	}

	void reset(int cols, int rows, rect_t<LONG>::vector & boxes, int roundness)
	{
		printf("rgns_t::reset(%d, %d, ..., %d)\n", cols, rows, roundness);

		bubbles.clear();
		links.clear();

		for(size_t i=0; i<boxes.size(); ++i) {
			bubbles.push_back(rgn_t(boxes[i], roundness));
			links[i] = boxes.size();
		}
	}

	void join(int src, int dst)
	{
		printf("rgns_t::join(%d, %d)\n", src, dst);
		bubbles[src].merge(bubbles[dst]);
		// bubbles[dst] = nullptr;
		links[dst] = src;
	}

	void split(int src, int dst)
	{
		printf("rgns_t::split(%d, %d)\n", src, dst);
	}
};


struct mergers_t
{
	HWND & frame;
	box_layout2_t & layout;
	rgns_t regions;

	mergers_t(HWND & frame, box_layout2_t & layout) :
		frame(frame),
		layout(layout)
	{
	}

	void recalc_layout()
	{
		// printf("mergers::recalc_layout\n");
		regions.reset(
			layout.grid.cols, layout.grid.rows,
			layout.boxes, layout.roundness);
	}

	void join(int src, int dst)
	{
		// printf("mergers::join(%d, %d)\n", src, dst);
		regions.join(src, dst);

		if(layout.grid.are_neighbors(src, dst))
		{
			int const a = src < dst ? src : dst;
			int const b = src < dst ? dst : src;

			auto & abox = layout.boxes[a];
			auto & bbox = layout.boxes[b];
			
			abox.w = bbox.w;
			abox.h = bbox.h;
			bbox.reset();

			// win::repaint_window(frame);
			temp_hdc_t hdc(frame);
			layout.draw_single_area(hdc.handle, dst);
			layout.draw_single_frame(hdc.handle, dst, true);
			layout.draw_single_area(hdc.handle, a);
			layout.draw_single_frame(hdc.handle, src, false);
		}
	}

	void split(int src, int dst)
	{
		regions.split(src, dst);
	}
};


struct box_t {

	HRGN handle;
	rect_t<LONG> r;
	int roundness;

	box_t(rect_t<LONG> & r, int roundness=0)
	{
		handle = CreateRoundRectRgn(r.x, r.y, r.x+r.w, r.y+r.h,
			roundness, roundness);
	}

};
