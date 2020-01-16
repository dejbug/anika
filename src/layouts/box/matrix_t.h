#pragma once
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <map>


/// The |canvas| is the main drawing area of our
///	control: the place where we will draw the images.
/// It will be partitioned into a grid of |bubbles|.
/// An |atomic bubbles| corresponds to the cells of the
/// grid. They can be merged to larger bubbles.
/// These bubbles are the zones into which images
/// will be dropped and in which images will be drawn.
/// In this module, we will deal with the merging of
/// atomic bubbles into larger ones.
/// Non-atomic bubbles are a.k.a. |groups|.


using Id = unsigned int;


struct geometry_t {
	size_t cols;
	size_t rows;
};


struct groups_t {
	/// A |group| is an integer (|Id|) that identifies
	/// either an atomic bubble (right after |reset|
	/// is called) or a set of bubbles that have been
	/// merged together.

	std::vector<Id> data;

	void reset(unsigned int count) {
		data.resize(count);
		for(unsigned int i=0; i<count; ++i)
			data[i] = i;
	}

	// Id & merge(Id a, Id b) {
	// 	/// Make the |a|-th item have the same value
	// 	/// as the |b|-th item; the value will be the
	// 	/// lesser of their previous values (if they
	// 	/// were different). IOW after every item pair
	// 	/// had been merged, all items will have the
	// 	/// value 0.
	// 	Id const & le = a <= b ? a : b;
	// 	Id const & ge = a <= b ? b : a;

	// 	data[ge] = data[le];
	// 	return data[ge];
	// }

	void print() const {
		for(auto it : data) {
			printf("%d ", it);
		}
		printf("\n");
	}
};


struct mappings_t {
	std::map<Id, Id *> links;
	groups_t & groups;

	mappings_t(groups_t & groups) : groups(groups) {
	}

	void reset(unsigned int count) {
		links.clear();
		groups.reset(count);
	}

	void assign(Id key, Id value) {
		links[key] = &groups.data[value];
	}

	void print() const {
		groups.print();
		for(auto p : links)
			printf("= %d -> %d\n", p.first, *p.second);
	}
};


/// ok let's think this trough.
/// we have a vector of drawables (e.g. rectangles): v1.
/// we have an index: index = [0 1 2 3 4 5]
/// so: index[2] = 2, etc.
/// now we merge two rectangles: 1 + 2
/// it means we need a second vector of drawables: v2.
/// v2 will hold the merged rectangles and index needs
/// to point the source rectangle's indices to the
/// new dest rectangle index.
/// But we also need to distinguish between indices into
/// v1 and indices into v2; it is best to have only one
/// kind of index: indices into v2; but this would mean
/// copying the whole of v1 into v2 at init; though we
/// could get away with mere references (weak copies).
///
///

// template<class T>
// struct mergable_i {
// 	virtual mergable_i merge_with(mergable_i & other) = 0;
// };


template<class T>
struct matrix_t {

	std::map<Id, Id> links;
	std::vector<T> * mergables;

	matrix_t() : mergables(nullptr) {
	}

	void attach(std::vector<T> & mergables) {
		this->mergables = &mergables;
		links.clear();
		for(size_t i=0; i<mergables.size(); ++i) {
			links[i] = i;
		}
	}

	void merge(Id a, Id b) {
		printf("-- matrix: merging %d with %d\n",
			a, b);
		links[a] = b;
	}

	void print() const {
		printf("-- marix: printing\n");
		for(auto link : links)
			printf(" %d->%d",
				link.first, link.second);
	}

};

// class matrix_t {
//
// 	geometry_t geometry;
// 	mappings_t mappings;
// 	groups_t groups;

// public:
	// matrix_t() : mappings(groups) {
	// }

	// void reset(geometry_t const & g={1,1}) {
	// 	printf("matrix: resetting to geometry"
	// 		" (%d,%d)\n", g.cols, g.rows);

	// 	geometry = g;
	// 	mappings.reset(geometry.cols * geometry.rows);
	// }

	// void merge(Id a, Id b) {
	// 	/// The run-down.
	// 	/// 0. The user has just joined two rects.
	// 	/// 1. We create a new rect (a+b) from the
	// 	/// 	two rects pointed to by a and b.
	// 	/// 2. And point slots a and b -> (a+b).



	// 	static Id dummy = 4711;

	// 	Id const & m = a <= b ? a : b;

	// 	mappings.assign(a, m);
	// 	mappings.assign(b, m);
	// }

	// void print() const {
	// 	mappings.print();
	// 	printf("\n");
	// }
// };
