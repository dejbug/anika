#include "dnd_tracker_t.h"
#include "error_t.h"
#include "listeners.h"


void dnd_tracker_t::callback(HWND h, UINT m, WPARAM w, LPARAM l)
{
	switch(m)
	{
		case WM_DROPFILES:
		{
			HDROP const hDrop = (HDROP)w;
			
			POINT pt = {0,0};
			DragQueryPoint(hDrop, &pt);
			
			UINT const file_count =
				DragQueryFile(hDrop, (UINT)-1, NULL, 0);
			
			char name[MAX_PATH] = {0};
			
			names.clear();
			
			for(UINT i=0; i<file_count; ++i)
			{
				UINT const file_name_length =
					DragQueryFile(hDrop, i, NULL, 0);
					
				UINT const chars_copied =
					DragQueryFile(hDrop, i,
						name, sizeof(name));
						
				/// this should never happen.
				if(chars_copied != file_name_length)
					error_t(OUT_OF_BUFFER);
			
				names.push_back(name);
			}
			
			DragFinish(hDrop);
			
			NOTIFY_LISTENERS(listeners)->
				on_drop(pt.x, pt.y, names);
			
			break;
		}
	}
}
