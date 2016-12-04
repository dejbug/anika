#include "rect_t.h"


rect_t::rect_t(long x, long y, long w, long h) :
	width(w), height(h),
	left(rect.left), top(rect.top),
	right(rect.right), bottom(rect.bottom),
	l(left), t(top), r(right), b(bottom),
	x(left), y(top), w(width), h(height)
{
	left = x;
	top = y;
	right = x+w;
	bottom = y+h;
}

rect_t::rect_t(const rect_t& o)
:	width(o.w), height(o.h),
	left(rect.left), top(rect.top),
	right(rect.right), bottom(rect.bottom),
	l(left), t(top), r(right), b(bottom),
	x(left), y(top), w(width), h(height)
{
	left = o.l;
	top = o.t;
	right = o.r;
	bottom = o.b;
}

rect_t& rect_t::operator=(const rect_t& o)
{
	left = o.l;
	top = o.t;
	right = o.r;
	bottom = o.b;
	width = o.width;
	height = o.height;
	
	return *this;
}

void rect_t::offset(long dx, long dy)
{
	l += dx;
	r += dx;
	t += dy;
	b += dy;
}

void rect_t::inflate(long dw, long dh)
{
	l -= dw;
	r += dw;
	t -= dh;
	b += dh;
	w = r-l;
	h = b-t;
}

bool rect_t::contains(int x, int y) const
{
	return x >= l && x <= r && y >= t && y <= b;
}


void draw_rect(HDC hdc, const rect_t& r, int radius)
{
	RoundRect(hdc, r.l, r.t, r.r+1, r.b+1, radius, radius);
}
