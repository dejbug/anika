#pragma once
#include <windows.h>

#include "errors.h"
#include "window_rect_t.h"


struct mdc_t
{
	HDC parent;
	HDC handle;
	HBITMAP bmp;
	int w, h;
	
	mdc_t(HDC parent) :
		parent(parent), handle(NULL), bmp(NULL)
	{
		if(!parent) return;
		
		handle = CreateCompatibleDC(parent);
		if(!handle) throw error_t(err::MDC);
		
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
		DeleteDC(handle);
		handle = NULL;
	}
	
	void resize(int w, int h)
	{
		if(!handle) return;
		if(bmp) delete_bmp();
		
		bmp = CreateCompatibleBitmap(parent, w, h);
		if(!bmp) throw error_t(err::MDC_BMP);

		SelectObject(handle, (HBITMAP)bmp);

		this->w = w;
		this->h = h;
	}
	
	void resize()
	{
		window_rect_t r(parent, true);
		resize(r.w, r.h);
	}
	
	void flip()
	{
		BitBlt(parent, 0, 0, w, h, handle, 0, 0, SRCCOPY);
	}
};
