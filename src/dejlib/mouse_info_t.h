#pragma once
#include <windows.h>


struct mouse_info_t
{
	static bool has_mouse()
	{
		return GetSystemMetrics(SM_MOUSEPRESENT);
	}
	
	static bool has_wheel()
	{
		return GetSystemMetrics(SM_MOUSEWHEELPRESENT);
	}
	
	static bool buttons_swapped()
	{
		return GetSystemMetrics(SM_SWAPBUTTON);
	}
	
	static int get_buttons_count()
	{
		return GetSystemMetrics(SM_CMOUSEBUTTONS);
	}
};
