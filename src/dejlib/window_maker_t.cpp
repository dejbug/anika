#include "window_maker_t.h"
#include "errors.h"
#include "error_t.h"


window_maker_t::window_maker_t(window_class_t& wc)
:	handle(NULL)
{
	hinstance = wc.hInstance;
	clsname = wc.lpszClassName;
}

HWND window_maker_t::create()
{
	handle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW|WS_EX_ACCEPTFILES|
			WS_EX_CONTEXTHELP|WS_EX_CONTROLPARENT,
		clsname.c_str(),
		"",
		WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hinstance,
		NULL
	);
	
	if(!handle)
		throw error_t(err::WINDOW_MAKER_CREATE);
	
	return handle;
}

HWND window_maker_t::create(HWND parent, UINT id)
{
	handle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		clsname.c_str(),
		"",
		WS_CHILD|WS_CLIPSIBLINGS|WS_TABSTOP,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		parent,
		(HMENU)id,
		hinstance,
		NULL
	);
	
	if(!handle)
		throw error_t(err::WINDOW_MAKER_CREATE);
	
	return handle;
}
