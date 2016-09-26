#pragma once
#include "mouse_tracker_t.h"
#include "dnd_tracker_t.h"


struct multi_tracker_t
{
	mouse_tracker_t mouse;
	dnd_tracker_t dnd;

	void callback(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		mouse.callback(h, m, w, l);
		dnd.callback(h, m, w, l);
	}
};

