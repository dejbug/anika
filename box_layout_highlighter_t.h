#pragma once
#include "box_layout_t.h"
#include "temp_color_setter_t.h"
#include "palettes.h"


struct box_layout_highlighter_t
{
	box_layout_t& layout;
	int last_hilit_box;
	
	
	box_layout_highlighter_t(box_layout_t& layout) :
		layout(layout),
		last_hilit_box(0)
	{
	}
	
	void on_pre_grid_draw(HDC hdc, COLORREF bg)
	{	
		rect_t r = layout.boxes[last_hilit_box];
		
		temp_color_setter_t cs(hdc);
		cs.fb(true, false);
		cs.fg(colors::blue);
		
		r.inflate(1, 1);
		
		if(layout.last_hovered_box > -1)
			draw_rect(hdc, r, layout.roundness);
	}
	
};
