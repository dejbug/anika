#include "box.h"
#include <window_class_t.h>
#include <mdc2_t.h>
#include "context_t.h"
#include "on_paint.h"


LRESULT CALLBACK Callback(HWND h, UINT m, WPARAM w, LPARAM l)
{
	auto ctx = context_t::retrieve(h);
	if(ctx) ctx->tracker.callback(h, m, w, l);

	switch(m)
	{
		case WM_ERASEBKGND:
			return 0;
			
		case WM_PAINT:
			on_paint(h, m, w, l);
			return 0;

		case WM_KEYDOWN:
			switch(w)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
			}
			return 0;

		case WM_CLOSE:
			DestroyWindow(h);
			return 0;

		case WM_DESTROY:
			context_t::destroy(h);
			return 0;

		case WM_CREATE:
			context_t::create(h);
			DragAcceptFiles(h, TRUE);
			return 0;
	}

	return DefWindowProc(h, m, w, l);
}


void layouts::box::register_control(HINSTANCE i)
{
	window_class_t wc("LAYOUT_BOX", Callback);
	if(i) wc.hInstance = i;
	wc.cbWndExtra = 4;	// to hold the context
	wc.install();
}
