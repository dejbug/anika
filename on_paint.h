#pragma once
#include <windows.h>

#include "mdc2_t.h"
#include "line_t.h"
#include "temp_color_setter_t.h"
#include "window_rect_t.h"

#include "tests.h"
#include "palettes.h"


extern context_t defcon;


void on_paint(HWND h, UINT m, WPARAM w, LPARAM l)
{
	PAINTSTRUCT ps;
	
	BeginPaint(h, &ps);
	
	mdc2_t mdc(ps.hdc);

	// mdc.clear(COLOR_BTNFACE);
	mdc.clear(color_t(RGB(220,200,180)));
	
	defcon.on_pre_grid_draw(mdc.handle);
	
	// temp_color_setter_t cs(mdc.handle);
	// cs.fb(true, false);
	
	// cs.fg(colors::mistyrose);
	// defcon.grid.draw(mdc.handle);
	
	defcon.on_post_grid_draw(mdc.handle);

	mdc.flip();

	EndPaint(h, &ps);
}
