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
	HDC const& hdc = ps.hdc;
	
	BeginPaint(h, &ps);
	
	mdc2_t mdc(hdc);
	
	mdc.clear(COLOR_BTNFACE);
	//~ mdc.clear(color_t(70, true, true));
	
	//~ temp_object_t brush(CreateSolidBrush(RGB(200,100,100)));
	//~ FillRect(mdc.handle, &r.rect, (HBRUSH)brush.handle);
	
	defcon.canvas.draw_area(mdc.handle);
	
	temp_color_setter_t cs(mdc.handle);
	
	cs.fg(255,200,200);
	cs.bg(false);
	
	defcon.tracker.grid.draw(mdc.handle);
	
	cs.reset();
	
	line_t line(100,100,600,100);
	line.draw(mdc.handle);
	
	defcon.canvas.draw_border(mdc.handle);
	
	mdc.flip();
	
	EndPaint(h, &ps);
}
