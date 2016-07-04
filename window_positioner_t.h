#pragma once
#include <windows.h>

#include "errors.h"
#include "error_t.h"
#include "window_rect_t.h"


struct window_positioner_t
{
	HWND handle;
	UINT extra_flags;
	
	window_positioner_t(HWND handle)
		: handle(handle), extra_flags(SWP_NOACTIVATE)
	{
		if(!handle)
			throw error_t(err::WINDOW_POSITIONER_HANDLE);
	}
	
	void move(int dx, int dy) const
	{
		window_rect_t r(handle);
		
		SetWindowPos(handle, NULL, r.left+dx, r.top+dy, 0, 0,
			extra_flags|SWP_NOZORDER|SWP_NOSIZE);
	}
	
	void setpos(int x, int y) const
	{
		SetWindowPos(handle, NULL, x, y, 0, 0,
			extra_flags|SWP_NOZORDER|SWP_NOSIZE);
	}
	
	void setsize(int w, int h) const
	{
		SetWindowPos(handle, NULL, 0, 0, w, h,
			extra_flags|SWP_NOZORDER|SWP_NOMOVE);
	}
	
	void below(HWND other) const
	{
		SetWindowPos(handle, other, 0, 0, 0, 0,
			extra_flags|SWP_NOMOVE|SWP_NOSIZE);
	}
	
	void to_bottom() const
	{
		SetWindowPos(handle, HWND_BOTTOM, 0, 0, 0, 0,
			extra_flags|SWP_NOMOVE|SWP_NOSIZE);
	}
	
	void to_top() const
	{
		SetWindowPos(handle, HWND_TOP, 0, 0, 0, 0,
			extra_flags|SWP_NOMOVE|SWP_NOSIZE);
	}
	
	void to_permanent_top() const
	{
		SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0,
			extra_flags|SWP_NOMOVE|SWP_NOSIZE);
	}
	
	void to_quasi_top() const
	{
		SetWindowPos(handle, HWND_NOTOPMOST, 0, 0, 0, 0,
			extra_flags|SWP_NOMOVE|SWP_NOSIZE);
	}
	
	void center_to_screen() const
	{
		window_rect_t c(handle);
		window_rect_t p(GetParent(handle));
		
		const int dx = (p.width - c.width) >> 1;
		const int dy = (p.height - c.height) >> 1;
		
		setpos(p.left + dx, p.top + dy);
	}
};
