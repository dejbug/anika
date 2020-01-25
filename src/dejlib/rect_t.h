#pragma once
#include <windows.h>
#include <type_traits>
#include <vector>


template<typename T>
struct rect_t
{
	typedef std::vector<rect_t<T>> vector;

	T x, y, w, h;

	rect_t(T x_=0, T y_=0, T w_=0, T h_=0) :
		x(x_), y(y_), w(w_), h(h_)
	{
	}

	rect_t(rect_t const & _) :
		x( _.x), y( _.y), w( _.w), h( _.h)
	{
	}

	rect_t(RECT const & _) :
		x( _.left), y( _.right), w( _.right - _.left), h( _.bottom - _.top)
	{
		static_assert(std::is_same<T,LONG>::value, "RECT uses LONGs");
	}

	rect_t & operator=(rect_t const & _)
	{
		x = _.x;
		y = _.y;
		w = _.w;
		h = _.h;
		return *this;
	}

	operator LPRECT()
	{
		static_assert(std::is_same<T,LONG>::value, "LPRECT uses LONGs");
		return reinterpret_cast<LPRECT>(this);
	}

	operator LPSIZE()
	{
		static_assert(std::is_same<T,LONG>::value, "LPSIZE uses LONGs");
		return reinterpret_cast<LPSIZE>(&static_cast<LONG *>(this)[2]);
	}

	operator LPPOINT()
	{
		static_assert(std::is_same<T,LONG>::value, "LPPOINT uses LONGs");
		return reinterpret_cast<LPPOINT>(this);
	}

	operator RECT() const
	{
		static_assert(std::is_same<T,LONG>::value, "RECT uses LONGs");
		return RECT{x, y, x+w, y+h};
	}

	operator SIZE() const
	{
		static_assert(std::is_same<T,LONG>::value, "SIZE uses LONGs");
		return SIZE{w, h};
	}

	operator POINT() const
	{
		static_assert(std::is_same<T,LONG>::value, "POINT uses LONGs");
		return POINT{x, y};
	}

	operator SMALL_RECT() const
	{
		static_assert(std::is_same<T,SHORT>::value, "SMALL_RECT uses SHORTs");
		return SMALL_RECT{x, y};
	}

	operator POINTS() const
	{
		static_assert(std::is_same<T,SHORT>::value, "POINTSSMALL_RECT uses SHORTs");
		return POINTS{x, y};
	}

	rect_t<T> & operator +=(rect_t<T> const & r)
	{
		// FIXME: Turns out that the Win32 layout (i.e. left,
		// top, right, bottom) is better suited for boolean
		// combinations (than x, y, w, h). We shall refactor.
		RECT a, b, z;
		*this >> a;
		r >> b;
		UnionRect(&z, &a, &b);
		*this << z;
		return *this;
	}

	void reset()
	{
		x = y = w = h = 0;
	}

	void offset(T dx, T dy)
	{
		x += dx;
		y += dx;
	}

	void inflate(T dw, T dh)
	{
		x -= dw;
		y -= dh;
		w += dw << 1;
		h += dw << 1;
	}

	bool contains(T x_, T y_) const
	{
		return x_ >= x && x_ <= x+w && y_ >= y && y_ <= y+h;
	}

	void draw(HDC hdc, int radius=0) const
	{
		static_assert(std::is_integral<T>::value, "RoundRect uses int");
		RoundRect(hdc, x, y, x+w+1, y+h+1, radius, radius);
	}
};


template<typename T>
void draw(rect_t<T> const & r, HDC hdc, int radius=0)
{
	r.draw(hdc, radius);
}


template<typename T>
rect_t<T> & operator<<(rect_t<T> & r, RECT const & _)
{
	r.x = _.left;
	r.y = _.top;
	r.w = _.right - _.left;
	r.h = _.bottom - _.top;
	return r;
}


template<typename T>
rect_t<T> const & operator>>(rect_t<T> const & r, RECT & _)
{
	_.left = r.x;
	_.top = r.y;
	_.right = r.x + r.w;
	_.bottom = r.y + r.h;
	return r;
}
