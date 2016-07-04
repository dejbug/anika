#pragma once
#include <windows.h>

#include "color_t.h"


struct temp_color_setter_t
{
	HDC hdc;
	HGDIOBJ old_brush, old_pen;
	HPEN null_pen;
	
	temp_color_setter_t(HDC hdc)
	{
		this->hdc = hdc;
		
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
	
	void fg(bool on=true)
	{
		if(on)
			SelectObject(hdc, (HPEN)GetStockObject(DC_PEN));
		
		else
		{
			if(!null_pen) null_pen = CreatePen(PS_NULL,0,0);
			SelectObject(hdc, null_pen);
		}
	}
	
	void bg(bool on=true)
	{
		if(on)
			SelectObject(hdc, (HBRUSH)GetStockObject(DC_BRUSH));
		
		else
			SelectObject(hdc, (HPEN)NULL_PEN);
	}
	
	void fg(int c)
	{
		SetDCPenColor(hdc, RGB(c,c,c));
	}
	
	void fg(char r, char g, char b)
	{
		SetDCPenColor(hdc, RGB(r,g,b));
	}
	
	void fg(COLORREF c)
	{
		SetDCPenColor(hdc, c);
	}
	
	void fg(color_t c)
	{
		SetDCPenColor(hdc, c.c);
	}
	
	void bg(int c)
	{
		SetDCBrushColor(hdc, RGB(c,c,c));
	}
	
	void bg(char r, char g, char b)
	{
		SetDCBrushColor(hdc, RGB(r,g,b));
	}
	
	void bg(COLORREF c)
	{
		SetDCBrushColor(hdc, c);
	}
	
	void bg(color_t c)
	{
		SetDCBrushColor(hdc, c.c);
	}
};
