#pragma once
#include <windows.h>


struct temp_color_setter_t
{
	HDC hdc;
	HGDIOBJ old_brush, old_pen;
	
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
	}
	
	void reset()
	{
		SelectObject(hdc, old_brush);
		SelectObject(hdc, old_pen);
	};
	
	void fg(char r, char g, char b)
	{
		SetDCPenColor(hdc, RGB(r,g,b));
	}
	
	void fg(COLORREF c)
	{
		SetDCPenColor(hdc, c);
	}
	
	void bg(char r, char g, char b)
	{
		SetDCBrushColor(hdc, RGB(r,g,b));
	}
	
	void bg(COLORREF c)
	{
		SetDCBrushColor(hdc, c);
	}
};
