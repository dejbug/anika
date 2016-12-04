
SHELL := cmd.exe

# -- linker flags
LDFLAGS :=

# -- compiler flags
CXXFLAGS :=
CXXFLAGS += -std=c++11 -O2 -Wall -pedantic


CXX := @g++
NAME := dejlib
OBJS := 
OBJS += clipper_t color_t dnd_tracker_t error_t 
OBJS += grid_t mdc2_t mdc_t mkeys_t mouse_drag_tracker_t 
OBJS += mouse_grid_picker_t mouse_grid_t mouse_tracker_t 
OBJS += multi_tracker_t palettes rect_t temp_color_setter_t 
OBJS += temp_hdc_t temp_object_t win window_class_t 
OBJS += window_maker_t window_positioner_t window_rect_t 
OBJS := $(addsuffix .o,$(OBJS))

$(NAME).a: $(OBJS)
	@ar ru $@ $^

%.o: %.cpp %.h
	@echo building $@
	$(CXX) $< -c -o $@ $(CXXFLAGS)

.PHONY: clean
clean:
	@del $(NAME).a 2>NUL
	@del *.o 2>NUL
