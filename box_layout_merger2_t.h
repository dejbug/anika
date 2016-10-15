#pragma once
#include <windows.h>

#include "error_t.h"
#include "errors.h"
#include "rect_t.h"
#include "mouse_tracker_t.h"
#include "listeners.h"


struct box_layout_merge_i
{
	virtual void on_merge(int src, int dst) = 0;
};

struct box_layout_merger2_t :
		public box_layout_listener2_i,
		public mouse_tracker_click2_i,
		public mouse_tracker_move_i
{
	box_layout_t& layout;
	int src_box;
	int button;
	std::vector<char> states;

	std::vector<box_layout_merge_i*> listeners;


	box_layout_merger2_t(box_layout_t& layout) :
		layout(layout),
		src_box(-1),
		button(1)
	{
	}

	virtual void on_mouse_button_down(int x, int y,
		int b, unsigned int keys)
	{
		int index, col, row;

		if(layout.hittest(x, y, index, col, row))
			src_box = index;
		else
			src_box = -1;
	}

	virtual void on_mouse_button_up(int x, int y,
		int b, unsigned int keys)
	{
		int index, col, row;

		if(src_box > -1 &&
				layout.hittest(x, y, index, col, row))

			NOTIFY_LISTENERS(listeners)->
				on_merge(src_box, index);

		src_box = -1;
	}

	virtual void on_enter_box(int index, int col, int row)
	{
	}

	virtual void on_leave_box(int index, int col, int row)
	{
	}

	virtual void on_mouse_move(int x, int y)
	{

	}
};
