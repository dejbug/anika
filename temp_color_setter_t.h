#pragma once
#include <windows.h>

#include "color_t.h"


struct temp_color_setter_t
{
	HDC hdc;
	HPEN const null_pen;
	HGDIOBJ old_brush, old_pen;
	
	temp_color_setter_t(HDC hdc) :
		hdc(hdc),
		null_pen(CreatePen(PS_NULL, 0, 0))
	{
		old_brush = SelectObject(hdc,
			(HBRUSH)GetStockObject(DC_BRUSH));
		
		old_pen = SelectObject(hdc,
			(HPEN)GetStockObject(DC_PEN));
	}
	
	virtual ~temp_color_setter_t()
	{
		reset();
		
		if(null_pen) DeleteObject(null_pen);
	}
	
	void reset()
	{
		SelectObject(hdc, old_brush);
		SelectObject(hdc, old_pen);
	};
	
	void fb(bool fg=true, bool bg=true)
	{
		ff(fg);
		bb(bg);
	}
	
	void ff(bool fg, bool bg=false)
	{
		if(fg)
			SelectObject(hdc, (HPEN)GetStockObject(DC_PEN));
		else
			SelectObject(hdc, null_pen);
	}
	
	void bb(bool bg, bool fg=false)
	{
		if(bg)
			SelectObject(hdc, (HBRUSH)GetStockObject(DC_BRUSH));
		else
			SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
	}
	
	void fg(char r, char g, char b)
	{
		SetDCPenColor(hdc, RGB(r,g,b));
	}
	
	void bg(char r, char g, char b)
	{
		SetDCBrushColor(hdc, RGB(r,g,b));
	}
	
	void fg(COLORREF c)
	{
		SetDCPenColor(hdc, c);
	}
	
	void bg(COLORREF c)
	{
		SetDCBrushColor(hdc, c);
	}
};
