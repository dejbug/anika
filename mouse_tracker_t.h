#pragma once
#include <windows.h>
#include <zmouse.h>
#include <vector>
#include "listeners.h"
#include "dnd_tracker_t.h"


struct mouse_tracker_move_i
{
	virtual void on_mouse_move(int x, int y) = 0;
};

struct mouse_tracker_wheel_i
{
	virtual void on_mouse_wheel(int x, int y,
		int delta, unsigned int keys) = 0;
};

struct mouse_tracker_click_i
{
	virtual void on_mouse_button(int x, int y,
		int b, int state, unsigned int keys) = 0;
};

struct mouse_tracker_click2_i
{
	virtual void on_mouse_button_down(int x, int y,
		int b, unsigned int keys) = 0;

	virtual void on_mouse_button_up(int x, int y,
		int b, unsigned int keys) = 0;
};


struct mouse_tracker_t
{
	std::vector<mouse_tracker_move_i*> move;
	std::vector<mouse_tracker_wheel_i*> wheel;
	std::vector<mouse_tracker_click_i*> click;
	std::vector<mouse_tracker_click2_i*> click2;

	void callback(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		switch(m)
		{
			case WM_MOUSEMOVE:
			{
				// const unsigned int keys = w;
				const int x = LOWORD(l);
				const int y = HIWORD(l);

				NOTIFY_LISTENERS(move)
					->on_mouse_move(x, y);

			}	break;

			case WM_MOUSEWHEEL:
			{
				const unsigned int keys = LOWORD(w);
				const short delta = HIWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);

				NOTIFY_LISTENERS(wheel)
					->on_mouse_wheel(x, y, delta, keys);

			}	break;

			case WM_LBUTTONDOWN:
			{
				const unsigned int keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);

				NOTIFY_LISTENERS(click)
					->on_mouse_button(x, y, 1, 1, keys);

				NOTIFY_LISTENERS(click2)
					->on_mouse_button_down(x, y, 1, keys);

			}	break;

			case WM_LBUTTONUP:
			{
				const unsigned int keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);

				NOTIFY_LISTENERS(click)
					->on_mouse_button(x, y, 1, 0, keys);

				NOTIFY_LISTENERS(click2)
					->on_mouse_button_up(x, y, 1, keys);

			}	break;

			case WM_MBUTTONDOWN:
			{
				const unsigned int keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);

				NOTIFY_LISTENERS(click)
					->on_mouse_button(x, y, 2, 1, keys);

				NOTIFY_LISTENERS(click2)
					->on_mouse_button_down(x, y, 2, keys);

			}	break;

			case WM_MBUTTONUP:
			{
				const unsigned int keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);

				NOTIFY_LISTENERS(click)
					->on_mouse_button(x, y, 2, 0, keys);

				NOTIFY_LISTENERS(click2)
					->on_mouse_button_up(x, y, 2, keys);

			}	break;

			case WM_RBUTTONDOWN:
			{
				const unsigned int keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);

				NOTIFY_LISTENERS(click)
					->on_mouse_button(x, y, 3, 1, keys);

				NOTIFY_LISTENERS(click2)
					->on_mouse_button_down(x, y, 3, keys);

			}	break;

			case WM_RBUTTONUP:
			{
				const unsigned int keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);

				NOTIFY_LISTENERS(click)
					->on_mouse_button(x, y, 3, 0, keys);

				NOTIFY_LISTENERS(click2)
					->on_mouse_button_up(x, y, 3, keys);

			}	break;
		}
	}
};
