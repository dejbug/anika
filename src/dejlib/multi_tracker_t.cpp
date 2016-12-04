#include "multi_tracker_t.h"


void multi_tracker_t::callback(HWND h, UINT m, WPARAM w, LPARAM l)
{
	mouse.callback(h, m, w, l);
	drag.callback(h, m, w, l);
	dnd.callback(h, m, w, l);
}
