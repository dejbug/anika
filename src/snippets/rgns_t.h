

struct rgn_t {

	struct error_t {};
	struct create_error_t : public error_t {};

	HRGN handle;
	rect_t<LONG> & bounds;
	int roundness;

	rgn_t(rect_t<LONG> & r, int roundness=0) : bounds(r), roundness(roundness)
	{
		handle = CreateRoundRectRgn(r.x, r.y, r.x+r.w, r.y+r.h,
			roundness, roundness);
		if(!handle) throw create_error_t();
	}

	virtual ~rgn_t()
	{
		free();
	}

	void free()
	{
		if(handle) DeleteObject(handle);
		handle = nullptr;
	}

	void merge(rgn_t & other)
	{
		// free();
		// other.free();

		bounds += other.bounds;
		handle = CreateRoundRectRgn(bounds.x, bounds.y, bounds.x+bounds.w, bounds.y+bounds.h, roundness, roundness);
	}
};


struct rgns_t {

	std::vector<rgn_t> bubbles;
	std::map<int,int> links;

	rgns_t()
	{
	}

	void reset(int cols, int rows, rect_t<LONG>::vector & boxes, int roundness)
	{
		printf("rgns_t::reset(%d, %d, ..., %d)\n", cols, rows, roundness);

		bubbles.clear();
		links.clear();

		for(size_t i=0; i<boxes.size(); ++i) {
			bubbles.push_back(rgn_t(boxes[i], roundness));
			links[i] = boxes.size();
		}
	}

	void join(int src, int dst)
	{
		printf("rgns_t::join(%d, %d)\n", src, dst);
		bubbles[dst].merge(bubbles[src]);
		// bubbles[dst] = nullptr;
		links[dst] = src;
	}

	void split(int src, int dst)
	{
		printf("rgns_t::split(%d, %d)\n", src, dst);
	}
};
