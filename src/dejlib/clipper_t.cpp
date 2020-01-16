#include "clipper_t.h"

clipper_t::clipper_t(HDC hdc)
{
	this->hdc = hdc;
}

void clipper_t::clear()
{
	SelectClipRgn(hdc, NULL);
}

void clipper_t::fill()
{
	HWND h = WindowFromDC(hdc);
	window_rect_t r(h);
	
	temp_object_t reg(
		CreateRectRgn(r.x, r.y, r.x+r.w, r.y+r.h));
	
	SelectClipRgn(hdc, (HRGN)reg.handle);
}

void clipper_t::merge(int x, int y, int w, int h)
{
	temp_object_t reg(CreateRectRgn(x, y, x+w, y+h));
	ExtSelectClipRgn(hdc, (HRGN)reg.handle, RGN_OR);
}

void clipper_t::cut(int x, int y, int w, int h)
{
	ExcludeClipRect(hdc, x, y, x+w, y+h);
}

void clipper_t::crop(int x, int y, int w, int h)
{
	IntersectClipRect(hdc, x, y, x+w, y+h);
}
