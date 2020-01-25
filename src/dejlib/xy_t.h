#pragma once
#include <iostream>


template<class T>
struct xy_t
{
	T x, y;
};

using xyi_t = xy_t<int>;
using xyl_t = xy_t<long>;

template<class T>
struct wh_t
{
	T w, h;
};

using whi_t = wh_t<int>;
using whl_t = wh_t<long>;

template<class T>
struct xywh_t
{
	T x, y, w, h;
};

using xywhi_t = xywh_t<int>;
using xywhl_t = xywh_t<long>;

template<class T>
struct ltrb_t
{
	T l, t, r, b;
};

using ltrbi_t = ltrb_t<int>;
using ltrbl_t = ltrb_t<long>;










wh_t<auto> operator*(wh_t<auto> const & wh, xy_t<auto> const & xy)
{
	return {wh.w * xy.x, wh.h * xy.y};
}


xy_t<auto> operator*(xy_t<auto> const & xy, wh_t<auto> const & wh)
{
	return {xy.x * wh.w, xy.y * wh.h};
}


wh_t<auto> operator/(wh_t<auto> const & wh, xy_t<auto> const & xy)
{
	return {wh.w / xy.x, wh.h / xy.y};
}


xywh_t<auto> operator/(xywh_t<auto> const & xywh, xy_t<auto> const & xy)
{
	return {xywh.x, xywh.y, xywh.w / xy.x, xywh.h / xy.y};
}


xywh_t<auto> operator+(xy_t<auto> const & xy, wh_t<auto> const & wh)
{
	return {xy.x, xy.y, wh.w, wh.h};
}












template<class T>
xywh_t<T> & operator<<(xywh_t<T> & dst, ltrb_t<auto> const & src)
{
	dst.x = src.l;
	dst.y = src.t;
	dst.w = src.r - src.l;
	dst.h = src.b - src.t;
	return dst;
}


template<class T>
ltrb_t<T> & operator<<(ltrb_t<T> & dst, xywh_t<auto> const & src)
{
	dst.l = src.x;
	dst.t = src.y;
	dst.r = src.x + src.w;
	dst.b = src.y + src.h;
	return dst;
}


template<class T>
xy_t<T> & operator<<(xy_t<T> & dst, xywh_t<auto> const & src)
{
	dst.x = src.x;
	dst.y = src.y;
	return dst;
}


template<class T>
wh_t<T> & operator<<(wh_t<T> & dst, xywh_t<auto> const & src)
{
	dst.w = src.w;
	dst.h = src.h;
	return dst;
}


template<class T>
xy_t<T> & operator<<(xy_t<T> & dst, ltrb_t<auto> const & src)
{
	dst.x = src.l;
	dst.y = src.t;
	return dst;
}


template<class T>
wh_t<T> & operator<<(wh_t<T> & dst, ltrb_t<auto> const & src)
{
	dst.w = src.r - src.l;
	dst.h = src.b - src.t;
	return dst;
}












std::ostream & operator<<(std::ostream & os, xy_t<auto> const & xy)
{
	return os << "xy_t(x=" << xy.x << ", y=" << xy.y << ")";
}


std::ostream & operator<<(std::ostream & os, wh_t<auto> const & wh)
{
	return os << "wh_t(w=" << wh.w << ", h=" << wh.h << ")";
}


std::ostream & operator<<(std::ostream & os, xywh_t<auto> const & xywh)
{
	return os << "xywh_t(x=" << xywh.x << ", y=" << xywh.y << ", w=" << xywh.w << ", h=" << xywh.h << ")";
}


std::ostream & operator<<(std::ostream & os, ltrb_t<auto> const & ltrb)
{
	return os << "ltrb_t(l=" << ltrb.l << ", t=" << ltrb.t << ", r=" << ltrb.r << ", b=" << ltrb.b << ")";
}
