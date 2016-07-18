#pragma once
#include <windows.h>


struct mouse_grid_t
{
	int cols, rows;
	int gx, gy;		/// grid offsets
	int cw, ch;		/// cell size
	
	mouse_grid_t() :
		cols(0), rows(0),
		gx(0), gy(0),
		cw(0), ch(0)
	{
		recalc();
	}
	
	mouse_grid_t(
		int cols, int rows,
		int offset_x=0, int offset_y=0,
		int cell_width=16, int cell_height=16)
	:
		cols(cols), rows(rows),
		gx(offset_x), gy(offset_y),
		cw(cell_width), ch(cell_height)
	{
		recalc();
	}
	
	void set_layout(int cols, int rows)
	{
		this->cols = cols;
		this->rows = rows;
	}
	
	void set_offsets(int x, int y)
	{
		gx = x; gy = y;
	}
	
	void set_cell_size(int w, int h)
	{
		cw = w; ch = h;
	}
	
	void recalc()
	{
	}
	
	void draw(HDC hdc)
	{
		const int gw = cw * cols;
		const int gh = ch * rows;
		
		int x = gx;
		for(int i=0; i<cols; ++i)
		{
			MoveToEx(hdc, x, gy, NULL);
			LineTo(hdc, x, gy+gh);
			
			x += cw;
		}
		
		int y = gx;
		for(int i=0; i<rows; ++i)
		{
			MoveToEx(hdc, gx, y, NULL);
			LineTo(hdc, gx+gw, y);
			
			y += ch;
		}
		
		MoveToEx(hdc, gx, gy, NULL);
		LineTo(hdc, gx+gw, gy);
		LineTo(hdc, gx+gw, gy+gh);
		LineTo(hdc, gx, gy+gh);
	}
};
