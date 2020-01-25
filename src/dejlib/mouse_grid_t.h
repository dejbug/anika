#pragma once
#include <windows.h>


struct mouse_grid_t
{
	int cols{0}, rows{0};
	int gx{0}, gy{0};		/// grid offsets
	int cw{0}, ch{0};		/// cell size

	void set_layout(int cols, int rows);
	void set_offsets(int x, int y);
	void set_cell_size(int w, int h);

	bool is_valid() const;

	void draw(HDC hdc) const;
};
