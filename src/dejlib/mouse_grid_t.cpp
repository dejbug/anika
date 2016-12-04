#include "mouse_grid_t.h"


mouse_grid_t::mouse_grid_t() :
	cols(0), rows(0),
	gx(0), gy(0),
	cw(0), ch(0)
{
	recalc();
}

mouse_grid_t::mouse_grid_t(
	int cols, int rows,
	int offset_x, int offset_y,
	int cell_width, int cell_height)
:
	cols(cols), rows(rows),
	gx(offset_x), gy(offset_y),
	cw(cell_width), ch(cell_height)
{
	recalc();
}

void mouse_grid_t::set_layout(int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;
}

void mouse_grid_t::set_offsets(int x, int y)
{
	gx = x; gy = y;
}

void mouse_grid_t::set_cell_size(int w, int h)
{
	cw = w; ch = h;
}

void mouse_grid_t::recalc()
{
}

void mouse_grid_t::draw(HDC hdc)
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
