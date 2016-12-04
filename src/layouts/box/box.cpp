#include "box.h"
#include <window_class_t.h>


LRESULT CALLBACK Callback(HWND h, UINT m, WPARAM w, LPARAM l)
{
	switch(m)
	{
		case WM_CREATE:
			break;
		
		case WM_CLOSE:
			DestroyWindow(h);
			break;
		
		case WM_DESTROY:
			break;
		
		case WM_ERASEBKGND:
			break;
			
		case WM_PAINT:
			on_paint(h, m, w, l);
			return 0;
			
	}

	return DefWindowProc(h, m, w, l);
}


void register_control(HINSTANCE i)
{
	window_class_t wc("LAYOUT_BOX", Callback);
	if(i) wc.hInstance = i;
	wc.install();
}
