#pragma once
#include <windows.h>

#include "mdc_t.h"
#include "temp_color_setter_t.h"
#include "window_rect_t.h"


struct mdc2_t : public mdc_t
{
	mdc2_t(HDC hdc) :
		mdc_t(hdc)
	{}
	
	void clear(UINT id)
	{
		window_rect_t r(handle, true);
		FillRect(handle, &r.rect, (HBRUSH)(id+1));
	}
	
	void clear(color_t c)
	{
		temp_color_setter_t cs(handle);
		cs.fb(false, true);
		cs.bg(c.c);
		
		window_rect_t r(handle, true);
		//~ FillRect(handle, &r.rect, (HBRUSH)(id+1));
		Rectangle(handle, r.l, r.t, r.r, r.b);
	}
};
