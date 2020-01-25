#pragma once
#include <windows.h>
#include "box_layout_t.h"

#include "palettes.h"
#include "temp_color_setter_t.h"


struct box_layout2_t :
		public box_layout_t,
		public box_layout_t::listener2_i
{
	int last_hilit_box;
	COLORREF hilit_fg_color;

	box_layout2_t() :
		box_layout_t(),
		last_hilit_box(-1),
		hilit_fg_color(colors::red)
	{
		listeners2.push_back(this);
	}

	void setup(const rect_t<LONG> & r, int cols, int rows, int gap=0)
	{
		box_layout_t::setup(r, cols, rows, gap);
	}

	void reset()
	{
		box_layout_t::reset();
	}

	void draw_single_area(HDC hdc, int index)
	{
		if(index < 0) index = last_hilit_box;

		if(index < 0 || static_cast<size_t>(index) >= boxes.size())
			return;

		temp_color_setter_t cs(hdc);
		cs.fb(false, true);
		cs.bg(colors::white);

		auto it = boxes.begin() + index;
		it->draw(hdc, roundness);
	}

	void draw_single_frame(HDC hdc, int index, bool hilite=false)
	{
		if(index < 0) index = last_hilit_box;

		if(index < 0 ||
				static_cast<size_t>(index) >= boxes.size())
			return;

		COLORREF const & normal_fg_color = colors::black;

		temp_color_setter_t cs(hdc);
		cs.fb(true, false);

		cs.fg(hilite ? hilit_fg_color : normal_fg_color);

		auto it = boxes.begin() + index;
		it->draw(hdc, roundness);
	}

	void draw_areas(HDC hdc)
	{
		temp_color_setter_t cs(hdc);
		cs.fb(false, true);
		cs.bg(colors::white);

		for(auto const & box : boxes)
			box.draw(hdc, roundness);
	}

	void draw_frames(HDC hdc)
	{
		COLORREF const & normal_fg_color = colors::black;

		temp_color_setter_t cs(hdc);
		cs.fb(true, false);

		int n=0;
		for(auto it=boxes.begin(); it<boxes.end(); ++it, ++n)
		{
			if(n == last_hilit_box)
				cs.fg(hilit_fg_color);
			else
				cs.fg(normal_fg_color);

			it->draw(hdc, roundness);
		}
	}

	virtual void on_enter_box(int index, int col, int row)
	{
		if(last_index > -1)
		{
			last_hilit_box = last_index;
		}
	}

	virtual void on_leave_box(int index, int col, int row)
	{
		last_hilit_box = -1;
	}
};
