#pragma once
#include <windows.h>

#include "error_t.h"
#include "errors.h"
#include "grid_t.h"
#include "rect_t.h"
#include "mouse_tracker_t.h"
#include "listeners.h"


struct box_layout_listener1_i
{
	virtual void on_hover_box(int index, int col, int row) = 0;
};

struct box_layout_listener2_i
{
	virtual void on_enter_box(int index, int col, int row) = 0;
	virtual void on_leave_box(int index, int col, int row) = 0;
};


struct box_layout_t :
		public mouse_tracker_move_i
{
	using listener1_i = box_layout_listener1_i;
	using listener2_i = box_layout_listener2_i;

	grid_t grid;
	rect_t<LONG>::vector boxes;
	int roundness;

	int last_index, last_col, last_row;

	std::vector<listener1_i*> listeners1;
	std::vector<listener2_i*> listeners2;

	box_layout_t() :
		roundness(0),
		last_index(-1),
		last_col(-1),
		last_row(-1)
	{
	}

	void draw(HDC hdc)
	{
		for(rect_t<LONG>::vector::iterator it=boxes.begin();
				it<boxes.end(); ++it)
			it->draw(hdc, roundness);
	}

	void draw(HDC hdc, int n)
	{
		boxes[n].draw(hdc, roundness);
	}

	void setup(const rect_t<LONG> & r, int cols, int rows, int gap=0,
			bool allow_rounding_errors=true)
	{
		reset();

		if(cols <= 0 || rows <= 0)
			throw error_t(err::ARGS);

		if(!allow_rounding_errors)
			if(r.w % cols != 0 || r.h % rows != 0)
				throw error_t(err::ARGS);

		grid.setup(r, cols, rows, gap);

		// int cx = r.x, cy = r.y;

		for(int j=0, cy=r.y; j<rows; ++j, cy+=grid.ch)
			for(int i=0, cx=r.x; i<cols; ++i, cx+=grid.cw)
			{
				boxes.push_back({cx+gap, cy+gap,
					grid.cw-gap-gap, grid.ch-gap-gap});
			}
	}

	void reset()
	{
		grid.reset();
		boxes.clear();
		last_index = last_col = last_row = -1;
	}

	bool hittest(int x, int y, int &index, int &col, int &row,
			bool only_visible=true) const
	{
		if(!grid.bounds.contains(x,y))
			return false;

		auto cell = grid.hittest(x, y);
		index = grid.ctoi(cell);
		// col = (x-grid.bounds.x) / grid.cw;
		// row = (y-grid.bounds.y) / grid.ch;
		// index = row * grid.cols + col;

		if(index >= 0 && index < (int)boxes.size())
		{
			return !only_visible || boxes[index].contains(x, y);
		}

		return false;
	}

	virtual void on_mouse_move(int x, int y)
	{
		int index, col, row;

		if(hittest(x, y, index, col, row, false))
		{
			NOTIFY_LISTENERS(listeners1)->
				on_hover_box(index, col, row);

			if(index != last_index)
			{
				if(last_index > -1)
				{
					NOTIFY_LISTENERS(listeners2)->
						on_leave_box(last_index, last_col, last_row);
				}

				last_index = index;
				last_col = col;
				last_row = row;

				NOTIFY_LISTENERS(listeners2)->
					on_enter_box(index, col, row);
			}
		}
		else
		{
			if(last_index > -1)
			{
				NOTIFY_LISTENERS(listeners2)->
					on_leave_box(last_index, last_col, last_row);

				last_index = last_col = last_row = -1;

			}
		}
	}
};
