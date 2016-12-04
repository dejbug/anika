#include "error_t.h"
#include <windows.h>
#include <stdio.h>

	
error_t::error_t(int code) :
	code(code), extra(GetLastError())
{}

error_t::error_t(int code, int extra) :
	code(code), extra(extra)
{}


void print_error(const error_t& e)
{
	printf("! error[%d] : %08x (%d)\n",
		e.code, e.extra, e.extra);
}
