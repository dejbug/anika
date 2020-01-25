#pragma once
#include "rect_t.h"
#include "xy_t.h"


struct grid_t
{
	using coord_t = xy_t<int>;
	using span_t = xy_t<int>;
	using step_t = wh_t<int>;

	rect_t<long> bounds;
	int cols, rows;
	int cw, ch, gap;

	grid_t();

	void setup(rect_t<long> const &, int cols, int rows, int gap=0);
	void reset();
	bool are_neighbors(int src, int dst) const;

	coord_t hittest(int x, int y) const;

	rect_t<long> cell(coord_t) const;
	rect_t<long> box(coord_t) const;

	int ctoi(coord_t) const;
	coord_t itoc(int) const;
};
