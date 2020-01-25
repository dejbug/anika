#include "grid_t.h"
#include "error_t.h"
#include "errors.h"


grid_t::grid_t()
{
	reset();
}

void grid_t::setup(const rect_t<LONG> & r, int cols, int rows, int gap)
{
	reset();

	cw = r.w / cols;
	ch = r.h / rows;

	if(cw <= 0 || ch <= 0)
		throw error_t(err::ARGS);

	bounds = r;
	this->cols = cols;
	this->rows = rows;
	this->gap = gap;
}

void grid_t::reset()
{
	bounds = rect_t<LONG>();
	cols = rows = gap = 0;
	cw = ch = 0;
}

bool grid_t::are_neighbors(int src, int dst) const
{
	return (
		src + 1 == dst ||
		src - 1 == dst ||
		src + cols == dst ||
		src - cols == dst
	);
}

grid_t::coord_t grid_t::hittest(int x, int y) const
{
	return {(x-bounds.x) / cw, (y-bounds.y) / ch};
}

rect_t<long> grid_t::cell(coord_t c) const
{
	return rect_t<long>{bounds.x + cw * c.x, bounds.y + ch * c.y, cw, ch};
}

rect_t<long> grid_t::box(coord_t c) const
{
	return rect_t<long>{bounds.x + (cw + gap) * c.x - gap, bounds.y + (ch + gap) * c.y - gap, cw - gap - gap, ch - gap - gap};
}

int grid_t::ctoi(grid_t::coord_t c) const
{
	return c.y * cols + c.x;
}

grid_t::coord_t grid_t::itoc(int index) const
{
	return {index % cols, index / cols};
}
