#pragma once
#include <windows.h>

#include "mouse_grid_t.h"


struct mouse_grid_picker_t
{
	mouse_grid_t& grid;
	
	mouse_grid_picker_t(mouse_grid_t& grid)
	:	grid(grid)
	{
	}
	
	
};
