#pragma once
#include <windows.h>
#include <string>
#include "window_class_t.h"


struct window_maker_t
{
	HWND handle;
	HINSTANCE hinstance;
	std::string clsname;
	
	window_maker_t(window_class_t& wc);
	HWND create();
	HWND create(HWND parent, UINT id);
};
