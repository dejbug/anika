#pragma once
#include <windows.h>

#include "temp_color_setter_t.h"
#include "dot_t.h"


struct canvas_t
{
	int x, y, w, h;
	dot_t::vector dots;
	
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
		
		RoundRect(hdc, x, y, w, h, 16, 16);
		//~ Rectangle(hdc, x, y, w, h);
		
		for(dot_t::vector::reverse_iterator it=dots.rbegin();
			it<dots.rend(); ++it)
		{
			it->draw(hdc);
		}
	}
};
