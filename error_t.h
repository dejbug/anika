#pragma once


struct error_t
{
	int code, extra;
	
	error_t(int code=-1)
		: code(code), extra(GetLastError()) {}
	
	error_t(int code, int extra)
		: code(code), extra(extra) {}
};
