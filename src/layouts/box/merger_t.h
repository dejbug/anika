#pragma once
#include <windows.h>

#include "box_layout2_t.h"
#include "temp_hdc_t.h"


struct merger_t
{
	HWND & frame;
	box_layout2_t & layout;

	merger_t(HWND & frame, box_layout2_t & layout) :
		frame(frame),
		layout(layout)
	{
	}

	void recalc_layout()
	{
	}

	void join(int src, int dst)
	{
		auto const [sx, sy] = layout.grid.itoc(src);
		auto const [dx, dy] = layout.grid.itoc(dst);

		printf("mergers::join(%d, %d) (%d:%d, %d:%d)\n", src, dst, sx, sy, dx, dy);

		return;
/* 
		// layout.boxes[dst].reset();
		rect_t<long> grid_box = layout.grid.box({sx, sy});
		layout.boxes[dst] = grid_box;


		temp_hdc_t hdc(frame);
		layout.draw_single_area(hdc.handle, src);
		layout.draw_single_frame(hdc.handle, src, true);
*/
	}

	void split(int src, int dst)
	{
	}
};
