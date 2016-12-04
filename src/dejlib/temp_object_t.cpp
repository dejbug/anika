#include "temp_object_t.h"


temp_object_t::temp_object_t(HGDIOBJ handle)
:	handle(handle)
{
}

temp_object_t::~temp_object_t()
{
	if(handle)
	{
		DeleteObject(handle);
		handle = NULL;
	}
}
