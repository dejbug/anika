#pragma once
#include <windows.h>

#include "temp_color_setter_t.h"
#include "dot_t.h"


void test_1(HDC hdc)
{
	dot_t a(300,300), b(400,400);
	dot_t c(a.x,a.y+(b.y-a.y)/2);
	dot_t d(b.x-(b.x-a.x)/2,b.y);
	
	//~ MoveToEx(hdc, a.x,a.y, NULL);
	//~ LineTo(hdc, b.x,b.y);
	
	temp_color_setter_t cs(hdc);
	cs.fb(true, false);
	
	cs.fg(0,100,200);
	//~ Rectangle(hdc, a.x, a.y, b.x, b.y);
	MoveToEx(hdc, c.x, c.y, NULL);
	LineTo(hdc, a.x, a.y);
	LineTo(hdc, b.x, a.y);
	LineTo(hdc, b.x, b.y);
	LineTo(hdc, d.x, b.y);
	
	cs.fg(200,100,0);
	Arc(hdc, a.x,a.y,b.x,b.y,
		c.x,c.y,d.x,d.y);
	
	a.draw(hdc);
	b.draw(hdc);
	c.draw(hdc);
	d.draw(hdc);
	
}


void test_2(HDC hdc)
{
	temp_color_setter_t cs(hdc);
	cs.fb(true, false);
	
	//~ cs.fg(200,0,0);
	cs.fg(100,100,200);
	
	dot_t::vector dots;
	dots.push_back(dot_t(100,100));
	dots.push_back(dot_t(200,200));
	
	draw_dots(hdc, dots);
}

