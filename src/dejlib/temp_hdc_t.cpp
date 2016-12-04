#include "temp_hdc_t.h"


temp_hdc_t::temp_hdc_t(HWND parent) :
	parent(parent),
	handle(GetDC(parent))
{
}

temp_hdc_t::~temp_hdc_t()
{
	if(handle)
		ReleaseDC(parent, handle);
}
