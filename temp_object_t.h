#pragma once
#include <windows.h>


struct temp_object_t
{
	HGDIOBJ handle;
	
	temp_object_t(HGDIOBJ handle=NULL) : handle(handle)
	{
	}
	
	virtual ~temp_object_t()
	{
		if(handle)
		{
			DeleteObject(handle);
			handle = NULL;
		}
	}
};
