
LDFLAGS_RELEASE:=-Wl,--subsystem=windows
LDFLAGS:=-lgdi32
CXXFLAGS:=-Wall -Wno-unused-variable

INC_DIRS:=\
	"c:\Programme\3\libpng\include"
	
LIB_DIRS:=\
	"c:\Programme\3\libpng\lib"
	
INCS:=$(addprefix -I,$(INC_DIRS))
LIBS:=$(addprefix -L,$(LIB_DIRS))

.PHONY: all clean run release

all: anika.exe

anika.exe: anika.o
	@g++ -o $@ $< $(LDFLAGS)

anika.o: anika.cpp *.h
	@g++ -o $@ -c $< $(CXXFLAGS)

run: anika.exe
	@anika.exe

clean:
	@del *.o 2>NUL
	@del *.exe 2>NUL

release: anika.o
	@g++ -o anika.exe $< $(LDFLAGS) $(LDFLAGS_RELEASE)
