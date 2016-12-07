
SHELL := cmd.exe

# -- linker flags
LDFLAGS :=
LDFLAGS_RELEASE := -Wl,--subsystem=windows

# -- compiler flags
CXXFLAGS :=
CXXFLAGS += -std=c++11 -O2 -Wall -pedantic
CXXFLAGS += -lgdi32 -lshell32
CXXFLAGS += -I"dejlib/" -I"app/"
# CXXFLAGS += -Wl,--subsystem=windows

CXX := g++
NAME := anika
OBJ := 
OBJ += layouts/box/box.o
OBJ += dejlib/dejlib.a


.PHONY: all
all: $(OBJ) $(NAME).exe

dejlib/dejlib.a:
	@make -C dejlib

$(NAME).exe: $(NAME).o $(OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)

release: $(NAME).cpp
	@g++ $< -o $(NAME).exe $(CXXFLAGS) $(LDFLAGS_RELEASE)

.PHONY: clean
clean:
	@del $(NAME).exe 2>NUL
	@del *.o 2>NUL
	@del layouts\box\box.o 2>NUL

.PHONY: run
run: $(NAME).exe
	@$(NAME).exe
