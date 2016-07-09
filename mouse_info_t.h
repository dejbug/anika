#pragma once
#include <windows.h>


struct mouse_info_t
{
	bool has_mouse;
	bool has_wheel;
	bool buttons_swapped;
	int buttons_count;
	
	mouse_info_t()
	{
		has_mouse = GetSysteMetrics(SM_MOUSEPRESENT);
		has_wheel = GetSysteMetrics(SM_MOUSEWHEELPRESENT);
		buttons_swapped = GetSysteMetrics(SM_SWAPBUTTON);
		buttons_count = GetSysteMetrics(SM_CMOUSEBUTTONS);
	}
};
