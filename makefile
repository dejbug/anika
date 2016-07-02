
LDFLAGS:=-Wl,--subsystem=windows
LDFLAGS:=-lgdi32
CXXFLAGS:=-Wall -Wno-unused-variable

INC_DIRS:=\
	"c:\Programme\3\libpng\include"
	
LIB_DIRS:=\
	"c:\Programme\3\libpng\lib"
	
INCS:=$(addprefix -I,$(INC_DIRS))
LIBS:=$(addprefix -L,$(LIB_DIRS))
	
all: anika.exe

anika.exe: anika.o
	@g++ -o $@ $< $(LDFLAGS)

anika.o: anika.cpp
	@g++ -o $@ -c $< $(CXXFLAGS)
	
