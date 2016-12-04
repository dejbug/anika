#include "color_t.h"


color_t::color_t(COLORREF c) :
	c(c)
{
}

color_t::color_t(char r, char g, char b)
:	c(RGB(r,g,b))
{
}

color_t::color_t(int h, bool soft, bool bright)
:	c(hsv(float(h),
		soft ? 0.33f : 0.66f,
		bright ? 0.88f : 0.55f))
{
}

color_t::color_t(int h, float s, float v)
:	c(hsv(float(h),s,v))
{
}

color_t::color_t(int h, double s, double v)
:	c(hsv(float(h),s,v))
{
}

void color_t::print()
{
	printf("cref %08lx (%ld,%ld,%ld)\n",
		c, c&0xff, (c>>8)&0xff, (c>>16)&0xff);
}


// [ source:] <https://www.cs.rit.edu/~ncs/color/t_convert.html>
COLORREF hsv(float h, float s, float v)
{
	int i;
	float r,g,b;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		//~ r = g = b = v;
		float c = 255*v;
		return RGB(c, c, c);
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		default:		// case 5:
			r = v;
			g = p;
			b = q;
			break;
	}
	
	return RGB(r*255, g*255, b*255);
}
