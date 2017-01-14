SHELL := cmd.exe
CXX := g++
CXXFLAGS :=
CXXFLAGS += -std=c++11 -O2 -Wall -pedantic
CXXFLAGS += -I"src/dejlib"
CXXFLAGS += -lgdi32 -lshell32
# CXXFLAGS += -Wl,--subsystem=windows

build/anika.exe: src/anika.o
build/anika.exe: src/layouts/box/box.o
build/anika.exe: src/dejlib/dejlib.a
build/anika.exe: ; $(CXX) $^ -o $@ $(CXXFLAGS)

src/anika.o: src/dejlib/dejlib.a
src/anika.o: src/layouts/box/box.o
src/anika.o: src/anika.cpp

src/layouts/box/box.o: src/layouts/box/box.cpp
src/layouts/box/box.o: src/layouts/box/*.h
src/layouts/box/box.o: ; $(CXX) $(filter %.cpp,$^) -c -o $@ $(CXXFLAGS)

src/dejlib/dejlib.a: src/dejlib/clipper_t.o
src/dejlib/dejlib.a: src/dejlib/color_t.o
src/dejlib/dejlib.a: src/dejlib/dnd_tracker_t.o
src/dejlib/dejlib.a: src/dejlib/error_t.o
src/dejlib/dejlib.a: src/dejlib/grid_t.o
src/dejlib/dejlib.a: src/dejlib/mdc2_t.o
src/dejlib/dejlib.a: src/dejlib/mdc_t.o
src/dejlib/dejlib.a: src/dejlib/mkeys_t.o
src/dejlib/dejlib.a: src/dejlib/mouse_drag_tracker_t.o
src/dejlib/dejlib.a: src/dejlib/mouse_grid_picker_t.o
src/dejlib/dejlib.a: src/dejlib/mouse_grid_t.o
src/dejlib/dejlib.a: src/dejlib/mouse_tracker_t.o
src/dejlib/dejlib.a: src/dejlib/multi_tracker_t.o
src/dejlib/dejlib.a: src/dejlib/palettes.o
src/dejlib/dejlib.a: src/dejlib/rect_t.o
src/dejlib/dejlib.a: src/dejlib/temp_color_setter_t.o
src/dejlib/dejlib.a: src/dejlib/temp_hdc_t.o
src/dejlib/dejlib.a: src/dejlib/temp_object_t.o
src/dejlib/dejlib.a: src/dejlib/win.o
src/dejlib/dejlib.a: src/dejlib/window_class_t.o
src/dejlib/dejlib.a: src/dejlib/window_maker_t.o
src/dejlib/dejlib.a: src/dejlib/window_positioner_t.o
src/dejlib/dejlib.a: src/dejlib/window_rect_t.o
src/dejlib/dejlib.a: ; @ar ru $@ $^

.PHONY: clean
clean:
	@del build\anika.exe 2>NUL
	@del src\*.o 2>NUL
	@del src\dejlib\*.a 2>NUL
	@del src\dejlib\*.o 2>NUL
	@del src\layouts\box\*.o 2>NUL

.PHONY: run
run: build/anika.exe
	@build\anika.exe
