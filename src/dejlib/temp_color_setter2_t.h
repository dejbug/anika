#pragma once


namespace dejlib {


static inline HGDIOBJ SelectStockObject(HDC hdc, int id)
{
	return SelectObject(hdc, GetStockObject(id));
}


struct auto_brush_t
{
	HDC const hdc;
	HGDIOBJ const old;

	auto_brush_t(HDC hdc)
		: hdc { hdc }, old { SelectStockObject(hdc, NULL_BRUSH) }
	{
	}

	auto_brush_t(HDC hdc, COLORREF c)
		: hdc{ hdc }, old{ SelectStockObject(hdc, DC_BRUSH) }
	{
		SetDCBrushColor(hdc, c);
	}

	~auto_brush_t()
	{
		SelectObject(hdc, old);
	}

	inline explicit operator bool() const
	{
		return GetStockObject(DC_BRUSH) == GetCurrentObject(hdc, OBJ_BRUSH);
	}

	inline COLORREF set(COLORREF c) const
	{
		return SelectStockObject(hdc, DC_BRUSH), SetDCBrushColor(hdc, c);
	}

	inline COLORREF get() const
	{
		return GetDCBrushColor(hdc);
	}
};


struct auto_pen_t
{
	HDC const hdc;
	HGDIOBJ const old;

	auto_pen_t(HDC hdc)
		: hdc { hdc }, old { SelectStockObject(hdc, NULL_PEN) }
	{
	}

	auto_pen_t(HDC hdc, COLORREF c)
		: hdc { hdc }, old { (SetDCPenColor(hdc, c), SelectStockObject(hdc, DC_PEN)) }
	{
	}

	~auto_pen_t()
	{
		SelectObject(hdc, old);
	}

	inline operator bool() const
	{
		return GetStockObject(DC_PEN) == GetCurrentObject(hdc, OBJ_PEN);
	}

	inline COLORREF set(COLORREF c) const
	{
		return SelectStockObject(hdc, DC_PEN), SetDCPenColor(hdc, c);
	}

	inline COLORREF set() const
	{
		return SelectStockObject(hdc, NULL_PEN), GetDCPenColor(hdc);
	}

	inline COLORREF get() const
	{
		return GetDCPenColor(hdc);
	}
};





template<bool P=true, bool B=true>
struct temp_color_setter2_t
{
	HDC const hdc;
	HGDIOBJ const old_pen, old_brush;

	temp_color_setter2_t(HDC hdc) :
			hdc{hdc},
			old_pen{SelectStockObject(hdc, DC_PEN)},
			old_brush{SelectStockObject(hdc, NULL_BRUSH)}
	{
	}

	temp_color_setter2_t(HDC hdc, COLORREF f) :
			hdc{hdc},
			old_pen{(SetDCPenColor(hdc, f), SelectStockObject(hdc, DC_PEN))},
			old_brush{SelectStockObject(hdc, DC_BRUSH)}
	{
	}

	temp_color_setter2_t(HDC hdc, COLORREF f, COLORREF b) :
			hdc{hdc},
			old_pen{(SetDCPenColor(hdc, f), SelectStockObject(hdc, DC_PEN))},
			old_brush{(SetDCBrushColor(hdc, b), SelectStockObject(hdc, DC_BRUSH))}
	{
	}

	~temp_color_setter2_t()
	{
		SelectObject(hdc, old_pen);
		SelectObject(hdc, old_brush);
	}

	inline COLORREF pen(COLORREF const & c) const
	{
		return SetDCPenColor(hdc, c);
	}

	inline COLORREF brush(COLORREF const & c) const
	{
		return SetDCBrushColor(hdc, c);
	}
};


template<>
struct temp_color_setter2_t<true, false>
{
	HDC const hdc;
	HGDIOBJ const old_pen;

	temp_color_setter2_t(HDC hdc) :
			hdc{hdc},
			old_pen{SelectStockObject(hdc, DC_PEN)}
	{
	}

	temp_color_setter2_t(HDC hdc, COLORREF f) :
			hdc{hdc},
			old_pen{(SetDCPenColor(hdc, f), SelectStockObject(hdc, DC_PEN))}
	{
	}

	~temp_color_setter2_t()
	{
		SelectObject(hdc, old_pen);
	}

	inline COLORREF pen(COLORREF const & c) const
	{
		return SetDCPenColor(hdc, c);
	}
};


template<>
struct temp_color_setter2_t<false, true>
{
	HDC const hdc;
	HGDIOBJ const old_brush;

	temp_color_setter2_t(HDC hdc) :
			hdc{hdc},
			old_brush{SelectStockObject(hdc, DC_BRUSH)}
	{
	}

	temp_color_setter2_t(HDC hdc, COLORREF b) :
			hdc{hdc},
			old_brush{(SetDCBrushColor(hdc, b), SelectStockObject(hdc, DC_BRUSH))}
	{
	}

	~temp_color_setter2_t()
	{
		SelectObject(hdc, old_brush);
	}

	inline COLORREF brush(COLORREF const & c) const
	{
		return SetDCBrushColor(hdc, c);
	}
};


using temp_pen_setter_t = temp_color_setter2_t<true, false>;

using temp_brush_setter_t = temp_color_setter2_t<false, true>;


} // !namespace dejlib
