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

struct box_layout_merger_t :
		public box_layout_listener2_i,
		public mouse_tracker_click_i
{
	box_layout_t& layout;
	int src_box;
	int button;
	
	std::vector<box_layout_merge_i*> listeners;
	
	
	box_layout_merger_t(box_layout_t& layout) :
		layout(layout),
		src_box(-1),
		button(1)
	{
	}
	
	virtual void on_enter_box(int index, int col, int row)
	{
	}
	
	virtual void on_leave_box(int index, int col, int row)
	{
	}
	
	virtual void on_mouse_button(int x, int y,
			int b, int state, int keys)
	{
		int index, col, row;
		
		if(b == button)
		{
			if(1 == state)
			{
				if(layout.hittest(x, y, index, col, row))
					src_box = index;
				else
					src_box = -1;
			}
			else if(0 == state)
			{
				if(src_box > -1 &&
						layout.hittest(x, y, index, col, row))
					
					NOTIFY_LISTENERS(listeners)->
						on_merge(src_box, index);
					
				src_box = -1;
			}
		}
	}
};
