#pragma once
#include <optional>


namespace dejlib {


template<class T>
struct XY { T x{}, y{}; };


template<class T>
struct grid
{
	using XY = XY<T>;

	XY const size, span, step;

	static grid calc_size(XY span, XY step)
	{
		return {span.x * step.x, span.y * step.y,
			span.x, span.y,
			step.x, step.y};
	}

	static grid calc_span(XY size, XY step)
	{
		return {size.x, size.y,
			size.x / step.x, size.y / step.y,
			step.x, step.y};
	}

	static grid calc_step(XY size, XY span)
	{
		return {size.x, size.y,
			span.x, span.y,
			size.x / span.x, size.y / span.y};
	}

	XY itoc(T index) const { return {index % span.x, index / span.x}; }

	T ctoi(XY coord) const { return coord.x + coord.y * span.x; }

	XY ptoc(XY pixel) const { return {pixel.x / step.x, pixel.y / step.y}; }

	XY ctop(XY coord) const { return {coord.x * step.x, coord.y * step.y}; }

	XY operator[](T index) const
	{
		return ctop(itoc(index));
	}

	XY operator[](XY pixel) const
	{
		return ptoc(pixel);
	}

	std::optional<XY> hittest(XY pixel) const
	{
		return contains(pixel) ? ptoc(pixel) : std::optional<XY>{};
	}

	bool contains(XY pixel) const
	{
		return pixel.x >= 0 && pixel.y >= 0 && pixel.x <= size.x && pixel.y <= size.y;
	}

	T count() const
	{
		return span.x * span.y;
	}

	struct iterator
	{
		grid const & parent;
		T index;

		bool operator!=(iterator const & it) const
		{
			return index != it.index;
		}

		void operator++()
		{
			++index;
		}

		XY operator*() const
		{
			return parent[index];
		}
	};

	iterator begin() const
	{
		return iterator{*this, 0};
	}

	iterator end() const
	{
		return iterator{*this, count()};
	}
};


} // !namespace dejlib


#ifndef NO_PRINTING
#include <iostream>


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


#endif
