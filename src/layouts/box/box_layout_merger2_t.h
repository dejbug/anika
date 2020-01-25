#pragma once
#include <windows.h>

#include "error_t.h"
#include "errors.h"
#include "rect_t.h"
#include "mouse_tracker_t.h"
#include "listeners.h"
#include "box_layout_merger_t.h"


struct box_layout_merger2_t :
		public mouse_tracker_click2_i
{
	using listener1_i = box_layout_merger_t::listener_i;

	box_layout_t& layout;
	int src_box;
	int button;
	std::vector<char> states;

	std::vector<listener_i *> listeners;


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
};
