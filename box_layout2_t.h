#pragma once
#include <windows.h>
#include "box_layout_t.h"
#include "palettes.h"


struct box_layout2_t :
	public box_layout_t
{
	int last_hilit_box;
	
	std::vector<int> groups;

	box_layout2_t() :
		box_layout_t()
	{
	}
	
	void setup(const rect_t& r, int cols, int rows, int gap=0)
	{
		box_layout_t::setup(r, cols, rows, gap);
		groups.resize(boxes.size());
		
		printf("\ngroups %d\n", groups.size());
	}
	
	void reset()
	{
		box_layout_t::reset();
	}
	
	void draw_areas(HDC hdc)
	{
		temp_color_setter_t cs(hdc);
		cs.fb(false, true);
		cs.bg(colors::white);
		
		for(auto it=boxes.begin(); it<boxes.end(); ++it)
			draw_rect(hdc, *it, roundness);
	}
	
	void draw_frames(HDC hdc)
	{
		temp_color_setter_t cs(hdc);
		cs.fb(true, false);
		cs.fg(colors::black);
		
		int n=0;
		for(auto it=boxes.begin(); it<boxes.end(); ++it, ++n)
		{
			if(n == last_hilit_box)
				cs.fg(colors::blue);
			else
				cs.fg(colors::black);
			
			draw_rect(hdc, *it, roundness);
		}
	}
};
