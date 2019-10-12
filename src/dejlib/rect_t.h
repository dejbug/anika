#pragma once
#include <windows.h>
#include <type_traits>
#include <vector>

template<typename T=long>
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
		static_assert(std::is_same<T,LONG>(), "RECT uses LONGs");
	}

	rect_t & operator=(rect_t const & _)
	{
		x = _.x;
		y = _.y;
		w = _.w;
		h = _.h;
		return *this;
	}

	void offset(long dx, long dy)
	{
		x += dx;
		y += dx;
	}

	void inflate(long dw, long dh)
	{
		x -= dw;
		y -= dh;
		w += dw << 1;
		h += dw << 1;
	}

	bool contains(int x_, int y_) const
	{
		return x_ >= x && x_ <= x+w && y_ >= y && y_ <= y+h;
	}

	void draw(HDC hdc, int radius=0)
	{
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
