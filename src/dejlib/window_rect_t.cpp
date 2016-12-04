#include "window_rect_t.h"


window_rect_t::window_rect_t(HWND parent, bool client)
:	parent(parent)
{
	update(client);
}

window_rect_t::window_rect_t(HDC hdc, bool client)
:	parent(WindowFromDC(hdc))
{
	update(client);
}

void window_rect_t::update(bool client)
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

SIZE window_rect_t::size() const
{
	const SIZE s = {w, h};
	return s;
}

POINT window_rect_t::pos() const
{
	const POINT p = {x, y};
	return p;
}
