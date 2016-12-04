#pragma once
#include <windows.h>


struct mouse_grid_t
{
	int cols, rows;
	int gx, gy;		/// grid offsets
	int cw, ch;		/// cell size
	
	mouse_grid_t();
	mouse_grid_t(
		int cols, int rows,
		int offset_x=0, int offset_y=0,
		int cell_width=16, int cell_height=16);
	void set_layout(int cols, int rows);
	void set_offsets(int x, int y);
	void set_cell_size(int w, int h);
	void recalc();
	void draw(HDC hdc);
};
