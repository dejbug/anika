#pragma once
#include <windows.h>

#include "mouse_grid_t.h"


struct mouse_tracker_t
{
	mouse_grid_t grid;
	
	mouse_tracker_t()
	{
	}
	
	void callback(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		switch(m)
		{
			case WM_MOUSEMOVE:
			{
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				//~ printf("%d:%d\n", x, y);
				
			}	break;
		}
	}
};
