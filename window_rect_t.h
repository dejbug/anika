#pragma once
#include <windows.h>


struct window_rect_t : public RECT
{
	long width, height;
	long const& x, y, w, h;
	
	window_rect_t(HWND handle, bool client=false)
		: x(left), y(top), w(width), h(height)
	{
		update(handle, client);
	}
	
	void update(HWND handle, bool client=false)
	{
		if(!handle)
		{
			left = top = 0;
			right = GetSystemMetrics(SM_CXSCREEN);
			bottom = GetSystemMetrics(SM_CYSCREEN);
		}
		else
		{
			if(client)
				GetClientRect(handle, this);
			else
				GetWindowRect(handle, this);
		}
		
		width = right - left;
		height = bottom - top;
	}
	
	SIZE size() const
	{
		const SIZE s = {right-left, bottom-top};
		return s;
	}
	
	POINT pos() const
	{
		const POINT p = {left, top};
		return p;
	}
};
