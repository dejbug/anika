#include "matrix_t.h"

// struct rect_t : public thing_i {
// 	RECT r;
// 	Id id;

// 	thing_t(Id id) : id(id) {
// 	}

// 	Id get_thing_id() const {
// 		return id;
// 	}

// 	thing_i merge_with(thing_i & other) {
// 		return *this;
// 	}
// };

struct canvas_t;


struct drawable_i {
	virtual void draw(canvas_t & canvas) = 0;
};


struct canvas_t {
	size_t cols, rows;
	char * chars = nullptr;

	canvas_t(size_t cols=78, size_t rows=23) {
		create(cols, rows, '*');
	}

	virtual ~canvas_t() {
		delete[] chars;
	}

	canvas_t(canvas_t && other) {
		cols = other.cols;
		rows = other.rows;
		chars = other.chars;
		other.chars = nullptr;
	}

	create(size_t cols, size_t rows, char background) {
		delete[] chars;
		chars = new char[cols * rows];
		this->cols = cols;
		this->rows = rows;
		fill(background);
	}

	void fill(char color) {
		// memset(chars, color, cols * rows);
		for(size_t i=0; i<cols * rows; ++i)
			chars[i] = color;
	}

	void set(int x, int y, int c) {
		chars[x + y * cols] = c;
	}

	template<class T>
	void draw(std::vector<T> & drawables) {
		for(auto & t : drawables) {
			drawable_i * d =
				dynamic_cast<drawable_i *>(&t);
			d->draw(*this);
		}
	}

	void draw(canvas_t const & other, char transparent='-') {

		for(int y=0; y<rows; ++y)
			for(int x=0; x<cols; ++x) {
				int const i = x + y * cols;
				if(transparent != other.chars[i])
					chars[i] = other.chars[i];
			}
	}

	void print() const {

		printf("\n");

		for(size_t i=0; i<cols*rows; ++i) {
			if(i > 0 && i % cols == 0)
				printf("\n");
			printf("%c", chars[i]);
		}

		printf("\n");
	}
};


struct shape_t : public RECT, public drawable_i {
	int l, t, r, b;
	char color;
	canvas_t bitmap;

	shape_t(RECT r_, char color=' ') : l(r_.left), t(r_.top), r(r_.right), b(r_.bottom), color(color) {

		reset();
	}

	void reset() {
		bitmap.fill('-');
		for(int y=t; y<=b; ++y)
			for(int x=l; x<=r; ++x)
				bitmap.set(x, y, color);
	}

	void draw(canvas_t & canvas) {
		canvas.draw(bitmap, '-');
	}

	void merge_with(shape_t & other) {
		other.draw(bitmap);
		spill();
	}

	void spill() {

		for(int y=1; y<bitmap.rows-1; ++y)
			for(int x=1; x<bitmap.cols-1; ++x) {

				int const i = x + y * bitmap.cols;

				if(color != bitmap.chars[i] && (color == bitmap.chars[i-1] && color == bitmap.chars[i+1] || color == bitmap.chars[i-bitmap.cols] && color == bitmap.chars[i+bitmap.cols]))

					bitmap.chars[i] = color;
			}
	}
};


int main()
{
	std::vector<shape_t> shapes;

	shapes.push_back(shape_t({1,1,3,3}));
	shapes.push_back(shape_t({5,1,10,10}));
	shapes.push_back(shape_t({1,5,3,10}));

	shapes[0].merge_with(shapes[1]);
	shapes[2].merge_with(shapes[1]);
	
	shapes[0].bitmap.print();
	shapes[1].bitmap.print();
	shapes[2].bitmap.print();

	canvas_t canvas;

	// matrix_t<shape_t> matrix;
	// matrix.attach(shapes);

	// matrix.merge(2, 1);

	canvas.draw(shapes);
	canvas.print();



	// matrix.reset(geometry_t{6, 3});
	// matrix.print();

	// matrix.merge(2, 1);
	// matrix.merge(12, 13);
	// matrix.merge(17, 17);
	// matrix.print();

	// matrix.merge(1, 12);
	// matrix.print();
	
}
