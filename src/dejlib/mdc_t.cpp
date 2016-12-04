#include "mdc_t.h"
#include "error_t.h"
#include "errors.h"
#include "window_rect_t.h"


mdc_t::mdc_t(HDC parent) :
	parent(parent), handle(NULL), bmp(NULL)
{
	if(!parent) return;
	
	handle = CreateCompatibleDC(parent);
	if(!handle) throw error_t(err::MDC);
	
	resize();
}

mdc_t::~mdc_t()
{
	delete_bmp();
	delete_dc();
}

void mdc_t::delete_bmp()
{
	if(handle) SelectObject(handle, (HBITMAP)NULL);
	if(bmp) { DeleteObject(bmp); bmp = NULL; }
}

void mdc_t::delete_dc()
{
	if(!handle) return;
	DeleteDC(handle);
	handle = NULL;
}

void mdc_t::resize(int w, int h)
{
	if(!handle) return;
	if(bmp) delete_bmp();
	
	bmp = CreateCompatibleBitmap(parent, w, h);
	if(!bmp) throw error_t(err::MDC_BMP);

	SelectObject(handle, (HBITMAP)bmp);

	this->w = w;
	this->h = h;
}

void mdc_t::resize()
{
	window_rect_t r(parent, true);
	resize(r.w, r.h);
}

void mdc_t::flip()
{
	BitBlt(parent, 0, 0, w, h, handle, 0, 0, SRCCOPY);
}
