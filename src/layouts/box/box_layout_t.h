#pragma once
#include <windows.h>

#include "error_t.h"
#include "errors.h"
#include "grid_t.h"
#include "rect_t.h"
#include "mouse_tracker_t.h"
#include "listeners.h"




template<typename T>
struct rects_t : rect_t<T>::vector
{
	using super = typename rect_t<T>::vector;
	using cref_t = typename rect_t<T>::vector::const_reference;
	using index_t = typename rect_t<T>::vector::size_type;

	using ocref_t = std::optional<cref_t>;

	inline bool contains(index_t index) const
	{
		return index >= 0 && index < super::size();
	}

	// inline ocref_t get(index_t index) const
	// {
		// return contains(index) ? *at(index) : ocref_t{};
	// }
};




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

	using boxes_t = rects_t<LONG>;

	grid_t grid;
	boxes_t boxes;
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

	// void draw(HDC hdc)
	// {
		// for(auto const & box : boxes)
			// box.draw(hdc, roundness);
	// }

	// void draw(HDC hdc, int n)
	// {
		// boxes.at(n).draw(hdc, roundness);
	// }

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

	bool hittest(int x, int y, int & index, int & col, int & row, bool only_visible=true) const
	{
		if (!grid.bounds.contains(x, y))
			return false;

		// col = (x-grid.bounds.x) / grid.cw;
		// row = (y-grid.bounds.y) / grid.ch;
		// index = row * grid.cols + col;

		auto const cell = grid.hittest(x, y);
		col = cell.x;
		row = cell.y;
		index = grid.ctoi(cell);

		if (!boxes.contains(index))
			return false;

		if (!only_visible)
			return true;

		return boxes[index].contains(x, y);
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
