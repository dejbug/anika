#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string>

#include "error_t.h"
#include "window_class_t.h"
#include "window_t.h"
#include "window_positioner_t.h"

#include "win.h"

LRESULT CALLBACK MainFrameProc(HWND h, UINT m, WPARAM w, LPARAM l)
{
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
		
		default:
			return DefWindowProc(h, m, w, l);
	}
	return 0;
}



int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	window_class_t wc("MAINFRAME", MainFrameProc);
	wc.install();
	
	window_t wnd(wc);
	wnd.create();
	
	window_positioner_t wp(wnd);
	wp.setsize(800, 700);
	wp.center_to_screen();
	
	wnd.show();
	
	return win::run();
}
