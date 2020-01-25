#pragma once
#include <iostream>


namespace geom {

template<class T>
struct XY
{
	T x{}, y{};
};

using XYi = XY<int>;
using XYl = XY<long>;

template<class T>
struct LTRB
{
	T l{}, t{}, r{}, b{};
};

using LTRBi = LTRB<int>;
using LTRBl = LTRB<long>;

template<class T>
struct XYWH
{
	T x{}, y{}, w{}, h{};
};

using XYWHi = XYWH<int>;
using XYWHl = XYWH<long>;

template<class T>
struct WH
{
	T w{}, h{};
};

using WHi = WH<int>;
using WHl = WH<long>;

} // !namespace geom


WH<auto> operator*(WH<auto> const & s, XY<auto> const & b)
{
	return {s.w * b.x, s.h * b.y};
}


WH<auto> operator/(WH<auto> const & s, XY<auto> const & b)
{
	return {s.w / b.x, s.h / b.y};
}


WH<auto> operator/(XYWH<auto> const & a, XY<auto> const & b)
{
	return {b.x, b.y, b.w / b.x, b.h / b.y};
}


template<class T>
XYWH<T> operator+(XY<T> const & a, WH<T> const & b)
{
	return {a.x, a.y, b.w, b.h};
}












template<class T>
XYWH<T> & operator<<(XYWH<T> & a, LTRB<auto> const & b)
{
	a.x = b.l;
	a.y = b.t;
	a.w = b.r - b.l;
	a.h = b.b - b.t;
	return a;
}


template<class T>
LTRB<T> & operator<<(LTRB<T> & a, XYWH<auto> const & b)
{
	a.l = b.x;
	a.t = b.y;
	a.r = b.x + b.w;
	a.b = b.y + b.h;
	return a;
}


template<class T>
XY<T> & operator<<(XY<T> & a, XYWH<auto> const & b)
{
	a.x = b.x;
	a.y = b.y;
	return a;
}


template<class T>
WH<T> & operator<<(WH<T> & a, XYWH<auto> const & b)
{
	a.w = b.w;
	a.h = b.h;
	return a;
}


template<class T>
XY<T> & operator<<(XY<T> & a, LTRB<auto> const & b)
{
	a.x = b.l;
	a.y = b.t;
	return a;
}


template<class T>
WH<T> & operator<<(WH<T> & a, LTRB<auto> const & b)
{
	a.w = b.r - b.l;
	a.h = b.b - b.t;
	return a;
}


template<class T>
XYWH<T> operator<<(XYWH<T> const & a, XY<auto> const & b)
{
	return {b.x, b.y, a.w, a.h};
}


template<class T>
XYWH<T> operator<<(XYWH<T> const & a, WH<auto> const & b)
{
	return {a.x, a.y, b.w, b.h};
}







std::ostream & operator<<(std::ostream & os, XY<auto> const & p)
{
	return os << "XY(x=" << p.x << ", y=" << p.y << ")";
}


std::ostream & operator<<(std::ostream & os, WH<auto> const & s)
{
	return os << "WH(w=" << s.w << ", h=" << s.h << ")";
}


std::ostream & operator<<(std::ostream & os, XYWH<auto> const & b)
{
	return os << "XYWH(x=" << b.x << ", y=" << b.y << ", w=" << b.w << ", h=" << b.h << ")";
}


std::ostream & operator<<(std::ostream & os, LTRB<auto> const & r)
{
	return os << "LTRB(l=" << r.l << ", t=" << r.t << ", r=" << r.r << ", b=" << r.b << ")";
}
