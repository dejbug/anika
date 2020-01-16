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
