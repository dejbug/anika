#include "mouse_drag_tracker_t.h"
#include "listeners.h"
#include "mkeys_t.h"


mouse_drag_tracker_t::mouse_drag_tracker_t()
{
	dragging_button = 0;
}

void mouse_drag_tracker_t::callback(HWND h, UINT m, WPARAM w, LPARAM l)
{
	switch(m)
	{
		case WM_MOUSEMOVE:
		{
			const unsigned int keys = w;
			const int x = LOWORD(l);
			const int y = HIWORD(l);

			if(dragging_button)
				NOTIFY_LISTENERS(drag)
					->on_mouse_drag_move(x, y, dragging_button, keys);

		}	break;

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			const unsigned int keys = w;
			const int x = LOWORD(l);
			const int y = HIWORD(l);

			dragging_button = mkeys_t(keys).get_main_button_down_lrm();

			SetCapture(h);

			NOTIFY_LISTENERS(drag)
				->on_mouse_drag_start(x, y, dragging_button, keys);

		}	break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		{
			const unsigned int keys = w;
			const int x = LOWORD(l);
			const int y = HIWORD(l);

			if(GetCapture() == h)
				ReleaseCapture();

			if(dragging_button)
			{
				NOTIFY_LISTENERS(drag)
					->on_mouse_drag_end(x, y, dragging_button, keys);

				dragging_button = 0;
			}

		}	break;

		case WM_CAPTURECHANGED:
		{
			// const HWND lost_to = (HWND)l;

			if(dragging_button)
			{
				NOTIFY_LISTENERS(drag)
					->on_mouse_drag_lost(dragging_button);

				dragging_button = 0;
			}

		}	break;
	}
}
