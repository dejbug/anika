#pragma once
#include <windows.h>

#include "rect_t.h"
#include "temp_color_setter2_t.h"
#include "box_layout2_t.h"
#include "mouse_grid_t.h"


struct canvas3_t
{
	box_layout2_t & layout;
	rect_t<LONG> bounds;

	canvas3_t(box_layout2_t& layout, int roundness=2) :
			layout(layout), bounds(0,0,960,720)
	{
		layout.roundness = roundness;
	}
};

