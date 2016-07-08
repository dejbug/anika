#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string>

// classes
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
#include "line_t.h"
#include "color_t.h"
#include "mdc2_t.h"
// namespaces
#include "win.h"
// functions
#include "on_paint.h"
// globals
context_t defcon;


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
	
	SetWindowText(wm.handle, "anika");
	
	window_positioner_t wp(wm.handle);
	wp.setsize(1040, 800);
	wp.center_to_screen();
	
	UpdateWindow(wm.handle);
	ShowWindow(wm.handle, SW_SHOW);
	
	return win::run();
}
