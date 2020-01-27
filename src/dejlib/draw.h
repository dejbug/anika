#pragma once
#include <windows.h>


namespace dejlib {


template<class T>
void draw(HDC hdc, T const &);

template<> void draw(HDC hdc, xywh<auto> const & t)
{
	auto const & [x, y, w, h] = t;
	Rectangle(hdc, x, y, x+w+1, y+h+1);
}

template<> void draw(HDC hdc, xywh<auto> const & t, int radius)
{
	auto const & [x, y, w, h] = t;
	RoundRect(hdc, x, y, x+w+1, y+h+1, radius, radius);
}

void draw_area(HDC hdc, COLORREF c=RGB(255,255,255))
{
	temp_color_setter_t cs(hdc);
	cs.fb(false, true);
	cs.bg(c);

	bounds.draw(hdc, 16);
}

void draw_border(HDC hdc, COLORREF c=RGB(0,0,0))
{
	temp_color_setter_t cs(hdc);
	cs.fb(true, false);
	cs.fg(c);

	bounds.draw(hdc, 16);
}


} // !namespace dejlib
