#pragma once
#include <windows.h>
#include <vector>

#include "error_t.h"
#include "errors.h"
#include "rect_t.h"
#include "mouse_tracker_t.h"
#include "listeners.h"
#include "box_layout_merger_t.h"


struct box_layout_merger_listener2_i
{
	typedef std::vector<int> trace_t;
	virtual void on_merge2(int button, trace_t const & trace) = 0;
};

struct box_layout_merger_listener3_i
{
	virtual void on_merge3(int button, int src, int dst) = 0;
};


struct box_layout_merger3_t :
		public box_layout_listener2_i,
		public mouse_tracker_click2_i
{
	using listener1_i = box_layout_merger_t::listener_i;
	using listener2_i = box_layout_merger_listener2_i;
	using listener3_i = box_layout_merger_listener3_i;

	box_layout_t& layout;
	int src_box;
	int last_box;
	int drag_button;
	std::vector<int> trace;

	std::vector<listener2_i *> listeners2;
	std::vector<listener3_i *> listeners3;


	box_layout_merger3_t(box_layout_t& layout) :
		layout(layout),
		src_box(-1),
		last_box(-1),
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
			last_box = index;

			drag_button = b;
			trace.push_back(index);
		}
		else
			src_box = -1;
	}

	virtual void on_mouse_button_up(int x, int y,
		int b, unsigned int keys)
	{
		if(src_box > -1)
		{
			NOTIFY_LISTENERS(listeners2)->
				on_merge2(drag_button, trace);
		}

		drag_button = 0;
		trace.clear();

		src_box = -1;
	}

	virtual void on_enter_box(int index, int col, int row)
	{
		if(drag_button > 0)
		{
			NOTIFY_LISTENERS(listeners3)->
				on_merge3(drag_button, last_box, index);

			trace.push_back(index);

			last_box = index;
		}
	}

	virtual void on_leave_box(int index, int col, int row)
	{
	}
};
