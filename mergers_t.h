#pragma once
#include <windows.h>
#include <map>


struct mergers_t {

	std::map<int,int> mapping;

	void join(int src, int dst)
	{

	}

	void split()
	{
	}
};


struct box_t {

	HRGN handle;
	rect_t r;
	int roundness;

	box_t(rect_t & r, int roundness=0)
	{
		handle = CreateRoundRectRgn(r.l, r.t, r.r, r.b,
			roundness, roundness);
	}

};


struct rgn_t {

	HRGN handle;

	rgn_t(rect_t & r, int roundness=0)
	{
		handle = CreateRoundRectRgn(r.l, r.t, r.r, r.b,
			roundness, roundness);
	}
};
