#pragma once
#include <windows.h>

#include "canvas_t.h"


struct context_t
{
	canvas_t canvas;
	
	context_t()
	{
		canvas.x = canvas.y = 16;
		
		canvas.dots.push_back(dot_t(100,200));
		canvas.dots.push_back(dot_t(600,200));
	}
};

