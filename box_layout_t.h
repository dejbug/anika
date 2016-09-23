#pragma once
#include <windows.h>

#include "error_t.h"
#include "errors.h"
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
	rect_t::vector boxes;
	rect_t bounds;
	int cols, rows;
	int cell_width, cell_height, gap;
	int roundness;
	
	int last_hovered_box;
	
	std::vector<box_layout_listener1_i*> listeners1;
	std::vector<box_layout_listener2_i*> listeners2;
	
	static bool allow_rounding_errors;
	static bool only_hit_test_visible;
	
	box_layout_t() :
		cols(0), rows(0),
		roundness(0),
		last_hovered_box(-1)
	{
	}
	
	void draw(HDC hdc)
	{
		for(rect_t::vector::iterator it=boxes.begin();
				it<boxes.end(); ++it)
			draw_rect(hdc, *it, roundness);
	}
	
	void setup(const rect_t& r, int cols, int rows, int gap=0)
	{
		reset();
		
		if(cols <= 0 || rows <= 0)
			throw error_t(err::ARGS);
		
		if(!allow_rounding_errors)
			if(r.w % cols != 0 || r.h % rows != 0)
				throw error_t(err::ARGS);
		
		const int cw = r.w / cols;
		const int ch = r.h / rows;
		
		if(cw <= 0 || ch <= 0)
			throw error_t(err::ARGS);
		
		int cx = r.x, cy = r.y;
		
		for(int j=0, cy=r.y; j<rows; ++j, cy+=ch)
			for(int i=0, cx=r.x; i<cols; ++i, cx+=cw)
			{
				boxes.push_back(
					rect_t(cx+gap, cy+gap, cw-gap-gap, ch-gap-gap));
			}
		
		bounds = r;
		this->cols = cols;
		this->rows = rows;
		this->cell_width = cw;
		this->cell_height = ch;
		this->gap = gap;
	}
	
	void reset()
	{
		boxes.clear();
		bounds = rect_t();
		last_hovered_box = -1;
		cols = rows = gap = 0;
		cell_width = cell_height = 0;
	}
	
	virtual void on_leave_box(int index, int col, int row)
	{
		NOTIFY_LISTENERS(listeners2)->
			on_leave_box(index, col, row);
			
		printf("\t\t\t\t\t\r");
	}
	
	bool hittest(int x, int y, int &index, int &col, int &row) const
	{
		if(!bounds.contains(x,y))
			return false;
			
		col = (x-bounds.x) / cell_width;
		row = (y-bounds.y) / cell_height;
		index = row * cols + col;
		
		if(index >= 0 && index < (int)boxes.size())
		{
			if(only_hit_test_visible)
			{
				if(	boxes[index].contains(x, y))
					return true;
			}
			else
				return true;
		}
		
		return false;
	}
	
	virtual void on_mouse_move(int x, int y)
	{
		int index, col, row;
		
		if(hittest(x, y, index, col, row))
		{
			NOTIFY_LISTENERS(listeners1)->
				on_hover_box(index, col, row);
			
			if(index != last_hovered_box)
			{
				last_hovered_box = index;
				
				NOTIFY_LISTENERS(listeners2)->
					on_enter_box(index, col, row);
			}
		}
		else
		{
			if(last_hovered_box > -1)
				NOTIFY_LISTENERS(listeners2)->
					on_leave_box(index, col, row);
					
			last_hovered_box = -1;
		}
	}
};


bool box_layout_t::allow_rounding_errors = true;
bool box_layout_t::only_hit_test_visible = true;
