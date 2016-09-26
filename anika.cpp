#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <string>

// classes
#include "window_class_t.h"
#include "window_maker_t.h"
#include "window_positioner_t.h"
#include "context_t.h"
// namespaces
#include "win.h"
// functions
#include "on_paint.h"


// globals
context_t defcon;


LRESULT CALLBACK MainFrameProc(HWND h, UINT m, WPARAM w, LPARAM l)
{
	defcon.tracker.callback(h, m, w, l);
	
	switch(m)
	{
		case WM_CREATE:
			DragAcceptFiles(h, TRUE);
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
					
				case VK_F2:
					// test resetting the canvas.
					defcon.canvas.layout.reset();
					InvalidateRect(h, NULL, TRUE);
					UpdateWindow(h);
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
	
	defcon.frame = wm.handle;
	
	SetWindowText(wm.handle, "anika");
	
	window_positioner_t wp(wm.handle);
	wp.setsize(1040, 800);
	wp.center_to_screen();
	
	UpdateWindow(wm.handle);
	ShowWindow(wm.handle, SW_SHOW);
	
	return win::run();
}
