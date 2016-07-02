#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string>

#include "error_t.h"
#include "window_class_t.h"
#include "window_t.h"
#include "window_positioner_t.h"
#include "window_rect_t.h"
#include "temp_color_setter_t.h"
#include "temp_object_t.h"

#include "win.h"


struct canvas_t
{
	int x, y, w, h;
	
	canvas_t()
	{
		x = y = 0;
		w = 960;
		h = 720;
	}
	
	void draw(HDC hdc)
	{
		temp_color_setter_t cs(hdc);
		cs.bg(RGB(255,255,255));
		cs.fg(RGB(0,0,0));
		
		//~ RoundRect(hdc, gap, gap, 960, 720, 16, 16);
		Rectangle(hdc, x, y, w, h);
	}
};


struct context_t
{
	canvas_t canvas;
	
	context_t()
	{
		canvas.x = canvas.y = 16;
	}
};


context_t default_context;


struct mdc_t
{
	struct err { enum {
		bmp,
	}; };
	
	HDC parent;
	HDC handle;
	HBITMAP bmp;
	int w, h;
	
	mdc_t(HDC parent)
	:	parent(parent), handle(NULL), bmp(NULL)
	{
		if(!parent) return;
		
		handle = CreateCompatibleDC(parent);
		if(!handle) throw error_t(err::bmp);
		
		resize();
	}
	
	virtual ~mdc_t()
	{
		delete_bmp();
		delete_dc();
	}
	
	void delete_bmp()
	{
		if(handle) SelectObject(handle, (HBITMAP)NULL);
		if(bmp) { DeleteObject(bmp); bmp = NULL; }
	}
	
	void delete_dc()
	{
		if(!handle) return;
		DeleteObject(handle);
		handle = NULL;
	}
	
	void resize(int w, int h)
	{
		if(!handle) return;
		if(bmp) delete_bmp();
		
		bmp = CreateCompatibleBitmap(parent, w, h);
		this->w = w;
		this->h = h;
		
		if(!bmp) return;
		SelectObject(handle, (HBITMAP)bmp);
	}
	
	void resize()
	{
		window_rect_t r(handle, true);
		resize(r.w, r.h);
	}
	
	void flip()
	{
		BitBlt(parent, 0, 0, w, h, handle, 0, 0, SRCCOPY);
	}
};


void on_paint(HWND h, UINT m, WPARAM w, LPARAM l)
{
	PAINTSTRUCT ps;
	HDC const& hdc = ps.hdc;
	
	BeginPaint(h, &ps);
	
	mdc_t mdc(hdc);
	
	/// -- draw background.
	window_rect_t r(hdc, true);
	FillRect(mdc.handle, &r.rect, (HBRUSH)(COLOR_BTNFACE+1));
	
	//~ temp_object_t brush(CreateSolidBrush(RGB(200,100,100)));
	//~ FillRect(mdc.handle, &r.rect, (HBRUSH)brush.handle);
	
	default_context.canvas.draw(mdc.handle);
	mdc.flip();
	
	EndPaint(h, &ps);
}


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
	
	window_t wnd(wc);
	wnd.create();
	
	window_positioner_t wp(wnd);
	wp.setsize(1000, 800);
	wp.center_to_screen();
	
	UpdateWindow(wnd.handle);
	wnd.show();
	
	return win::run();
}
