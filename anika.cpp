#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string>

#include "errors.h"
#include "error_t.h"
#include "window_class_t.h"
#include "window_maker_t.h"
#include "window_positioner_t.h"
#include "window_rect_t.h"
#include "temp_color_setter_t.h"
#include "temp_object_t.h"
#include "canvas_t.h"
#include "context_t.h"
#include "mdc_t.h"
#include "line_t.h"
#include "color_t.h"

#include "win.h"


context_t defcon;


struct mdc2_t : public mdc_t
{
	mdc2_t(HDC hdc)
	:	mdc_t(hdc)
	{}
	
	void clear(UINT id)
	{
		window_rect_t r(handle, true);
		FillRect(handle, &r.rect, (HBRUSH)(id+1));
	}
	
	void clear(color_t c)
	{
		temp_color_setter_t cs(handle);
		cs.bg(c.c);
		
		window_rect_t r(handle, true);
		//~ FillRect(handle, &r.rect, (HBRUSH)(id+1));
		Rectangle(handle, r.l, r.t, r.r, r.b);
	}
};


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


LRESULT CALLBACK MainFrameProc(HWND h, UINT m, WPARAM w, LPARAM l)
{
	defcon.tracker.callback(h,m,w,l);
	
	switch(m)
	{
		case WM_CREATE:
			break;
		
		case WM_CLOSE:
			DestroyWindow(h);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
		case WM_KEYDOWN:
			switch(w)
			{
				case VK_ESCAPE:
					win::close_window(h);
					break;
			}
			break;
		
		case WM_ERASEBKGND:
			break;
			
		case WM_PAINT:
			on_paint(h, m, w, l);
			break;
		
		default:
			return DefWindowProc(h, m, w, l);
	}
	return 0;
}


int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	window_class_t wc("MAINFRAME", MainFrameProc);
	wc.install();
	
	window_maker_t wm(wc);
	wm.create();
	
	window_positioner_t wp(wm.handle);
	wp.setsize(1040, 800);
	wp.center_to_screen();
	
	UpdateWindow(wm.handle);
	ShowWindow(wm.handle, SW_SHOW);
	
	return win::run();
}
