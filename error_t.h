#pragma once
#include <stdio.h>


struct error_t
{
	int code, extra;
	
	error_t(int code=-1) :
		code(code), extra(GetLastError())
	{}
	
	error_t(int code, int extra) :
		code(code), extra(extra)
	{}
};


void print_error(const error_t& e)
{
	printf("! error[%d] : %08x (%d)\n",
		e.code, e.extra, e.extra);
}
