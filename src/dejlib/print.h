#pragma once
#include <iostream.h>


namespace dejlib {


std::ostream & operator<<(std::ostream & os, dejlib::XY<auto> const & xy)
{
	return os << xy.x << ":" << xy.y;
}


std::ostream & operator<<(std::ostream & os, std::optional<dejlib::XY<auto>> const & xy_opt)
{
	if (xy_opt) os << xy_opt.value(); else os << "?:?";
	return os;
}


std::ostream & operator<<(std::ostream & os, dejlib::grid<auto> const & grid)
{
	return os << "grid{ "
		<< "size=" << grid.size << ", "
		<< "step=" << grid.step << ", "
		<< "span=" << grid.span << " }";
}


} // !namespace dejlib
