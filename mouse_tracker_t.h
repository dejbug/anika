#pragma once
#include <windows.h>
#include <zmouse.h>
#include <vector>


struct mouse_tracker_move_i
{
	typedef std::vector<mouse_tracker_move_i*> pvector;
	
	virtual void on_mouse_move(int x, int y) = 0;
};

struct mouse_tracker_wheel_i
{
	typedef std::vector<mouse_tracker_wheel_i*> pvector;
	
	virtual void on_mouse_wheel(int x, int y,
		int delta, int keys) = 0;
};

struct mouse_tracker_clicks_i
{
	typedef std::vector<mouse_tracker_clicks_i*> pvector;
	
	virtual void on_mouse_down(int x, int y,
		int b, int keys) = 0;
	
	virtual void on_mouse_up(int x, int y,
		int b, int keys) = 0;
};


struct mouse_tracker_t
{
	mouse_tracker_move_i::pvector move_listeners;
	mouse_tracker_wheel_i::pvector wheel_listeners;
	mouse_tracker_clicks_i::pvector clicks_listeners;
	
	mouse_tracker_t()
	{
	}
	
	void callback(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		switch(m)
		{
			case WM_MOUSEMOVE:
			{
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				for(mouse_tracker_move_i::pvector::iterator
						it=move_listeners.begin();
						it < move_listeners.end();
						++it)
						
					(*it)->on_mouse_move(x, y);
				
			}	break;
			
			case WM_MOUSEWHEEL:
			{
				const unsigned short keys = LOWORD(w);
				const short delta = HIWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				for(mouse_tracker_wheel_i::pvector::iterator
						it=wheel_listeners.begin();
						it < wheel_listeners.end();
						++it)
						
					(*it)->on_mouse_wheel(x, y, delta, keys);
					
			}	break;
			
			case WM_LBUTTONDOWN:
			{
				const unsigned short keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				for(mouse_tracker_clicks_i::pvector::iterator
						it=clicks_listeners.begin();
						it < clicks_listeners.end();
						++it)
						
					(*it)->on_mouse_down(x, y, 1, keys);
				
			}	break;
			
			case WM_LBUTTONUP:
			{
				const unsigned short keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				for(mouse_tracker_clicks_i::pvector::iterator
						it=clicks_listeners.begin();
						it < clicks_listeners.end();
						++it)
						
					(*it)->on_mouse_up(x, y, 1, keys);
				
			}	break;
			
			case WM_MBUTTONDOWN:
			{
				const unsigned short keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				for(mouse_tracker_clicks_i::pvector::iterator
						it=clicks_listeners.begin();
						it < clicks_listeners.end();
						++it)
						
					(*it)->on_mouse_down(x, y, 2, keys);
				
			}	break;
			
			case WM_MBUTTONUP:
			{
				const unsigned short keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				for(mouse_tracker_clicks_i::pvector::iterator
						it=clicks_listeners.begin();
						it < clicks_listeners.end();
						++it)
						
					(*it)->on_mouse_up(x, y, 2, keys);
				
			}	break;
			
			case WM_RBUTTONDOWN:
			{
				const unsigned short keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				for(mouse_tracker_clicks_i::pvector::iterator
						it=clicks_listeners.begin();
						it < clicks_listeners.end();
						++it)
						
					(*it)->on_mouse_down(x, y, 3, keys);
				
			}	break;
			
			case WM_RBUTTONUP:
			{
				const unsigned short keys = LOWORD(w);
				const int x = LOWORD(l);
				const int y = HIWORD(l);
				
				for(mouse_tracker_clicks_i::pvector::iterator
						it=clicks_listeners.begin();
						it < clicks_listeners.end();
						++it)
						
					(*it)->on_mouse_up(x, y, 3, keys);
				
			}	break;
		}
	}
};
