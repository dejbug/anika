#pragma once
#include <windows.h>

#include "rect_t.h"


struct window_rect_t : public rect_t
{
	HWND parent;
	
	window_rect_t(HWND parent, bool client=false) :
		parent(parent)
	{
		update(client);
	}
	
	window_rect_t(HDC hdc, bool client=false) :
		parent(WindowFromDC(hdc))
	{
		update(client);
	}
	
	void update(bool client=false)
	{
		if(!parent)
		{
			left = top = 0;
			right = GetSystemMetrics(SM_CXSCREEN);
			bottom = GetSystemMetrics(SM_CYSCREEN);
		}
		else
		{
			BOOL(WINAPI *method_f)(HWND,LPRECT) =
				client ? GetClientRect : GetWindowRect;
			
			method_f(parent, &rect);
		}
		
		width = right - left;
		height = bottom - top;
	}
	
	SIZE size() const
	{
		const SIZE s = {w, h};
		return s;
	}
	
	POINT pos() const
	{
		const POINT p = {x, y};
		return p;
	}
};
