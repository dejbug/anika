#include "window_class_t.h"
#include "errors.h"
#include "error_t.h"


window_class_t::window_class_t(LPCSTR name, WNDPROC callback)
{
	init();
	
	lpszClassName = name;
	lpfnWndProc = callback;
}

void window_class_t::zeromemory()
{
	memset(this, 0, sizeof(WNDCLASSEX));
}

void window_class_t::init()
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

void window_class_t::install()
{
	if(!RegisterClassEx(this))
		throw error_t(err::WINDOW_CLASS_INSTALL);
}

void window_class_t::uninstall()
{
	if(!UnregisterClass(lpszClassName, hInstance))
		throw error_t(err::WINDOW_CLASS_UNINSTALL);
}

void window_class_t::load()
{
	if(!GetClassInfoEx(hInstance, lpszClassName, this))
		throw error_t(err::WINDOW_CLASS_LOAD);
}
