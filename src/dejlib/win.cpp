#include "win.h"
#include "error_t.h"


int win::run()
{
	MSG msg;
	
	while(1)
	{
		int res = GetMessage(&msg, NULL, 0, 0);
		
		if(0 == res)
		{
			// WM_QUIT
			break;
		}
		
		else if(res < 0)
		{
			// errors!
			throw error_t();
		}
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}


void win::close_window(HWND h)
{
	SendMessage(h, WM_CLOSE, 0, 0);
}

void win::repaint_window(HWND h)
{
	InvalidateRect(h, NULL, TRUE);
	UpdateWindow(h);
}
