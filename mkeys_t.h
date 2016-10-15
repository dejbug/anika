#pragma once
#include <windows.h>


struct mkeys_t
{
	enum {
		MK_BUTTON_MASK = (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON),
	};

	DWORD w;

	mkeys_t(DWORD w)
	:	w(w)
	{
	}

	bool is_button_down() const
	{
		return w & MK_BUTTON_MASK;
	}

	int get_button_down_count() const
	{
		return 0 +
			(w & MK_LBUTTON ? 1 : 0) +
			(w & MK_MBUTTON ? 1 : 0) +
			(w & MK_RBUTTON ? 1 : 0);
	}

	int get_button_up_count() const
	{
		return 3 -
			(w & MK_LBUTTON ? 1 : 0) +
			(w & MK_MBUTTON ? 1 : 0) +
			(w & MK_RBUTTON ? 1 : 0);
	}

	int get_main_button_down_lmr() const
	{
		if(w & MK_LBUTTON) return 1;
		if(w & MK_MBUTTON) return 2;
		if(w & MK_RBUTTON) return 3;
		return 0;
	}

	int get_main_button_down_lrm() const
	{
		if(w & MK_LBUTTON) return 1;
		if(w & MK_RBUTTON) return 3;
		if(w & MK_MBUTTON) return 2;
		return 0;
	}

	int get_main_button_down_mlr() const
	{
		if(w & MK_MBUTTON) return 2;
		if(w & MK_LBUTTON) return 1;
		if(w & MK_RBUTTON) return 3;
		return 0;
	}

	int get_main_button_down_mrl() const
	{
		if(w & MK_MBUTTON) return 2;
		if(w & MK_RBUTTON) return 3;
		if(w & MK_LBUTTON) return 1;
		return 0;
	}

	int get_main_button_down_rlm() const
	{
		if(w & MK_RBUTTON) return 3;
		if(w & MK_LBUTTON) return 1;
		if(w & MK_MBUTTON) return 2;
		return 0;
	}

	int get_main_button_down_rml() const
	{
		if(w & MK_RBUTTON) return 3;
		if(w & MK_MBUTTON) return 2;
		if(w & MK_LBUTTON) return 1;
		return 0;
	}

	bool is_left_button_down() const
	{
		return w & MK_LBUTTON;
	}

	bool is_only_left_button_down() const
	{
		return MK_LBUTTON == (w & MK_BUTTON_MASK);
	}

	bool is_middle_button_down() const
	{
		return w & MK_MBUTTON;
	}

	bool is_only_middle_button_down() const
	{
		return MK_MBUTTON == (w & MK_BUTTON_MASK);
	}

	bool is_right_button_down() const
	{
		return w & MK_RBUTTON;
	}

	bool is_only_right_button_down() const
	{
		return MK_RBUTTON == (w & MK_BUTTON_MASK);
	}

	bool is_control_down() const
	{
		return w & MK_CONTROL;
	}

	bool is_shift_down() const
	{
		return w & MK_SHIFT;
	}
};
