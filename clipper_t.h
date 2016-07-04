#pragma once
#include <windows.h>

#include "errors.h"
#include "temp_object_t.h"


struct clipper_t
{
	HDC hdc;
	
	clipper_t(HDC hdc)
	{
		this->hdc = hdc;
	}
	
	void clear()
	{
		SelectClipRgn(hdc, NULL);
	}
	
	void fill()
	{
		HWND h = WindowFromDC(hdc);
		window_rect_t r(h);
		
		temp_object_t reg(
			CreateRectRgn(r.l, r.t, r.r, r.b));
		
		SelectClipRgn(hdc, (HRGN)reg.handle);
	}
	
	void merge(int x, int y, int w, int h)
	{
		temp_object_t reg(CreateRectRgn(x, y, x+w, y+h));
		ExtSelectClipRgn(hdc, (HRGN)reg.handle, RGN_OR);
	}
	
	void cut(int x, int y, int w, int h)
	{
		ExcludeClipRect(hdc, x, y, x+w, y+h);
	}
	
	void crop(int x, int y, int w, int h)
	{
		IntersectClipRect(hdc, x, y, x+w, y+h);
	}
};
