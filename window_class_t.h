#pragma once
#include <windows.h>

#include "error.h"


struct window_class_t : public WNDCLASSEX
{
	struct err { enum {
		install,
		uninstall,
		load,
	}; };
	
	window_class_t(LPCSTR name, WNDPROC callback=DefWindowProc)
	{
		init();
		
		lpszClassName = name;
		lpfnWndProc = callback;
	}
	
	void zeromemory()
	{
		memset(this, 0, sizeof(WNDCLASSEX));
	}
	
	void init()
	{
		cbSize = sizeof(WNDCLASSEX);
		
		cbClsExtra = 0;
		cbWndExtra = 0;
		
		style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		
		hInstance = GetModuleHandle(NULL);
		hIcon = hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		hCursor = LoadCursor(NULL, IDC_ARROW);
		hbrBackground = (HBRUSH)COLOR_WINDOW;
		
		lpszMenuName = NULL;
		lpszClassName = NULL;
		lpfnWndProc = DefWindowProc;
	}
	
	void install()
	{
		if(!RegisterClassEx(this))
			throw error_t(err::install);
	}
	
	void uninstall()
	{
		if(!UnregisterClass(lpszClassName, hInstance))
			throw error_t(err::uninstall);
	}
	
	void load()
	{
		if(!GetClassInfoEx(hInstance, lpszClassName, this))
			throw error_t(err::load);
	}
};
