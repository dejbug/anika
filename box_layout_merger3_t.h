#pragma once
#include <windows.h>
#include <vector>

#include "error_t.h"
#include "errors.h"
#include "rect_t.h"
#include "mouse_tracker_t.h"
#include "listeners.h"


struct box_layout_merge2_i
{
	typedef std::vector<int> trace_t;
	virtual void on_merge(int button, trace_t const & trace) = 0;
};

struct box_layout_merger3_t :
		public box_layout_listener2_i,
		public mouse_tracker_click2_i
{
	box_layout_t& layout;
	int src_box;
	int drag_button;
	std::vector<int> trace;

	std::vector<box_layout_merge2_i*> listeners;


	box_layout_merger3_t(box_layout_t& layout) :
		layout(layout),
		src_box(-1),
		drag_button(0)
	{
	}

	virtual void on_mouse_button_down(int x, int y,
		int b, unsigned int keys)
	{
		int index, col, row;

		if(layout.hittest(x, y, index, col, row))
		{
			src_box = index;

			drag_button = b;
			trace.push_back(index);
		}
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
				on_merge(drag_button, trace);

		drag_button = 0;
		trace.clear();

		src_box = -1;
	}

	virtual void on_enter_box(int index, int col, int row)
	{
		if(drag_button > 0)
		{
			trace.push_back(index);
		}
	}

	virtual void on_leave_box(int index, int col, int row)
	{
	}
};
