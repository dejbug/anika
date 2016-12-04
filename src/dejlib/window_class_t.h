#pragma once
#include <windows.h>


struct window_class_t : public WNDCLASSEX
{
	window_class_t(LPCSTR name, WNDPROC callback=DefWindowProc);
	void zeromemory();
	void init();
	void install();
	void uninstall();
	void load();
};
