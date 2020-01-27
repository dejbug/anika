#pragma once
#include <windows.h>

// #include <optional>

#include "box_layout_t.h"

#include "palettes.h"
#include "temp_color_setter2_t.h"


struct box_layout2_t :
		public box_layout_t,
		public box_layout_t::listener2_i
{
	COLORREF const normal_bg_color { colors::white };
	COLORREF const normal_fg_color { colors::gray };
	COLORREF const hilit_bg_color { colors::pink };
	COLORREF const hilit_fg_color { colors::pink };

	struct hilight_tracker_t
	{
		size_t index{ 0 };
		bool valid{ false };

		void set(size_t index_)
		{
			index = index_;
			valid = true;
		}

		void reset()
		{
			valid = false;
		}

		bool match(size_t index_)
		{
			return valid && index == index_;
		}
	};

	hilight_tracker_t hilight_tracker;

	box_layout2_t()
	{
		listeners2.push_back(this);
	}

	void setup(const rect_t<LONG> & r, int cols, int rows, int gap=0)
	{
		hilight_tracker.reset();

		box_layout_t::setup(r, cols, rows, gap);
	}

	void draw_single_area(HDC hdc, int index, bool lit)
	{
		if (!boxes.contains(index))
			return;

		dejlib::auto_brush_t const brush{ hdc, lit ?
			hilit_bg_color : normal_bg_color };

		dejlib::auto_pen_t const pen{ hdc };

		boxes[index].draw(hdc, roundness);
	}

	void draw_single_frame(HDC hdc, int index, bool lit)
	{
		if (!boxes.contains(index))
			return;

		dejlib::auto_brush_t const brush{ hdc };

		dejlib::auto_pen_t const pen{ hdc, lit ?
			hilit_fg_color : normal_fg_color };

		boxes[index].draw(hdc, roundness);
	}

	void draw_areas(HDC hdc)
	{
		dejlib::auto_brush_t const brush{ hdc, normal_bg_color };
		dejlib::auto_pen_t const pen{ hdc };

		for(auto const & box : boxes)
			box.draw(hdc, roundness);

		if (hilight_tracker.valid)
		{
			brush.set(hilit_bg_color);
			boxes[hilight_tracker.index].draw(hdc, roundness);
		}
	}

	void draw_frames(HDC hdc)
	{
		dejlib::auto_brush_t const brush{ hdc };
		dejlib::auto_pen_t const pen(hdc, normal_fg_color);

		for(auto const & box : boxes)
			box.draw(hdc, roundness);

		if (hilight_tracker.valid)
		{
			pen.set(hilit_fg_color);
			boxes[hilight_tracker.index].draw(hdc, roundness);
		}
	}

	virtual void on_enter_box(int index, int col, int row)
	{
		hilight_tracker.set(index);
	}

	virtual void on_leave_box(int index, int col, int row)
	{
		hilight_tracker.reset();
	}
};
