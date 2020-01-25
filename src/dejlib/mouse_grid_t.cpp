#include "mouse_grid_t.h"


void mouse_grid_t::set_layout(int c, int r)
{
	cols = c; rows = r;
}

void mouse_grid_t::set_offsets(int x, int y)
{
	gx = x; gy = y;
}

void mouse_grid_t::set_cell_size(int w, int h)
{
	cw = w; ch = h;
}

bool mouse_grid_t::is_valid() const
{
	if (cols <= 0 || rows <= 0) return false;
	if (cw <= 0 || ch <= 0) return false;
	return true;
}

void mouse_grid_t::draw(HDC hdc) const
{
	if (!is_valid()) return;

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
