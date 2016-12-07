#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <string>

// classes
#include <window_class_t.h>
#include <window_maker_t.h>
#include <window_positioner_t.h>
// namespaces
#include <win.h>

#include "layouts/box/box.h"

#define IDC_LAYOUT_BOX	1001


HWND create_layout_box(HWND parent)
{
	window_class_t wc("LAYOUT_BOX");
	window_maker_t wm(wc);
	wm.create(parent, IDC_LAYOUT_BOX);

	window_positioner_t wp(wm.handle);
	wp.setsize(1040, 800);
	wp.setpos(0,0);
	
	UpdateWindow(wm.handle);
	ShowWindow(wm.handle, SW_SHOW);
	SetFocus(wm.handle);

	return wm.handle;
}


LRESULT CALLBACK MainFrameProc(HWND h, UINT m, WPARAM w, LPARAM l)
{
	static HWND layout_box = nullptr;

	switch(m)
	{
		case WM_KEYDOWN:
			switch(w)
			{
				case VK_ESCAPE:
					win::close_window(h);
					break;
					
				case VK_F5:
					InvalidateRect(h, NULL, TRUE);
					UpdateWindow(h);
					break;
			}
			return 0;

		case WM_SETFOCUS:
			if(layout_box) SetFocus(layout_box);
			return 0;
		
		case WM_CREATE:
		{
			layout_box = create_layout_box(h);
			return 0;
		}

		case WM_CLOSE:
			DestroyWindow(h);
			return 0;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	
	return DefWindowProc(h, m, w, l);
}


int WinMain(HINSTANCE i, HINSTANCE, LPSTR, int)
{
	layouts::box::register_control(i);

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
