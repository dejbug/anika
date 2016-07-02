#pragma once
#include <windows.h>


struct window_rect_base_t
{
	RECT rect;
	long width, height;
	long &left, &top, &right, &bottom;
	long &l, &t, &r, &b;
	long &x, &y, &w, &h;
	
	window_rect_base_t()
	:	width(0), height(0),
		left(rect.left), top(rect.top),
		right(rect.right), bottom(rect.bottom),
		l(left), t(top), r(right), b(bottom),
		x(left), y(top), w(width), h(height)
	{
		left = top = right = bottom = 0;
	}
};


struct window_rect_t : public window_rect_base_t
{
	HWND parent;
	
	window_rect_t(HWND parent, bool client=false)
	:	parent(parent)
	{
		update(client);
	}
	
	window_rect_t(HDC hdc, bool client=false)
	:	parent(WindowFromDC(hdc))
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
