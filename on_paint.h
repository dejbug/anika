#pragma once
#include <windows.h>

#include "mdc2_t.h"
#include "line_t.h"
#include "temp_color_setter_t.h"
#include "window_rect_t.h"


extern context_t defcon;;


void on_paint(HWND h, UINT m, WPARAM w, LPARAM l)
{
	PAINTSTRUCT ps;
	
	BeginPaint(h, &ps);
	mdc2_t mdc(ps.hdc);
	mdc.clear(COLOR_BTNFACE);
	
	defcon.canvas.draw_area(mdc.handle);
	
	temp_color_setter_t cs(mdc.handle);
	
	//~ cs.fg(255,200,200);
	cs.fg(color_t(30*11,.20f,.9f).c);
	cs.bg(false);
	
	defcon.tracker.grid.draw(mdc.handle);
	
	cs.reset();
	
	defcon.canvas.draw_border(mdc.handle);
	
	mdc.flip();
	EndPaint(h, &ps);
}
