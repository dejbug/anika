#include "temp_color_setter_t.h"


temp_color_setter_t::temp_color_setter_t(HDC hdc) :
	hdc(hdc),
	null_pen(CreatePen(PS_NULL, 0, 0))
{
	old_brush = SelectObject(hdc,
		(HBRUSH)GetStockObject(DC_BRUSH));
	
	old_pen = SelectObject(hdc,
		(HPEN)GetStockObject(DC_PEN));
}

temp_color_setter_t::~temp_color_setter_t()
{
	reset();
	
	if(null_pen) DeleteObject(null_pen);
}

void temp_color_setter_t::reset()
{
	SelectObject(hdc, old_brush);
	SelectObject(hdc, old_pen);
}

void temp_color_setter_t::fb(bool fg, bool bg)
{
	ff(fg);
	bb(bg);
}

void temp_color_setter_t::ff(bool fg, bool bg)
{
	if(fg)
		SelectObject(hdc, (HPEN)GetStockObject(DC_PEN));
	else
		SelectObject(hdc, null_pen);
}

void temp_color_setter_t::bb(bool bg, bool fg)
{
	if(bg)
		SelectObject(hdc, (HBRUSH)GetStockObject(DC_BRUSH));
	else
		SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
}

void temp_color_setter_t::fg(unsigned char r, unsigned char g, unsigned char b)
{
	SetDCPenColor(hdc, RGB(r,g,b));
}

void temp_color_setter_t::bg(unsigned char r, unsigned char g, unsigned char b)
{
	SetDCBrushColor(hdc, RGB(r,g,b));
}

void temp_color_setter_t::fg(COLORREF c)
{
	SetDCPenColor(hdc, c);
}

void temp_color_setter_t::bg(COLORREF c)
{
	SetDCBrushColor(hdc, c);
}
