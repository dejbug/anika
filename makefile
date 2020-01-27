SHELL := cmd.exe
CXX := g++
CXXFLAGS :=
CXXFLAGS += -Wall -Wextra -pedantic
CXXFLAGS += -std=c++17 -fconcepts
CXXFLAGS += -I"src/dejlib"
CXXFLAGS += -lgdi32 -lshell32
CXXFLAGS += -Wno-unused-parameter
# CXXFLAGS += -Wl,--subsystem=windows

deploy/anika.exe: build/anika.o
deploy/anika.exe: build/dejlib.a

build: ; $(call MAKEDIR,$@)
deploy: ; $(call MAKEDIR,$@)
build/dejlib: | build ; $(call MAKEDIR,$@)
build/layouts: | build ; $(call MAKEDIR,$@)
build/layouts/box: | build/layouts ; $(call MAKEDIR,$@)

build/%.d: src/%.cpp ; $(call GEN_PREREQ,$@,$<)

DEJLIB_SOURCES := $(wildcard src/dejlib/*.cpp)
DEJLIB_PREREQS := $(DEJLIB_SOURCES:src/%.cpp=build/%.d)
DEJLIB_OBJECTS := $(DEJLIB_SOURCES:src/%.cpp=build/%.o)

deploy/%.exe: | deploy ; $(call LINK,$@,$^)
build/dejlib.a: $(DEJLIB_OBJECTS) | build/dejlib ; @ar ru $@ $^
build/dejlib/%.o: src/dejlib/%.cpp | build/dejlib ; $(call COMPILE,$@,$<)
build/dejlib/%.d: src/dejlib/%.cpp | build/dejlib ; $(call GEN_PREREQ,$@,$<)
build/layouts/box/%.d: src/layouts/box/%.cpp | build/layouts/box ; $(call GEN_PREREQ,$@,$<)
build/%.o: src/%.cpp | build ; $(call COMPILE,$@,$<)
build/%.d: src/%.cpp | build ; $(call GEN_PREREQ,$@,$<)
# build/layouts/box/%.o: src/layouts/box/%.cpp | build/layouts/box ; $(call COMPILE,$@,$<)

.PHONY: clean reset
clean:: ; $(call DELTREE,build)
reset:: | clean ; $(call DELTREE,deploy)

.PHONY: run
run: deploy/anika.exe
	$(subst /,\,$<)

.DELETE_ON_ERROR:


include build/anika.d
include $(DEJLIB_PREREQS)
# include $(wildcard src/**.cpp:%.cpp=%.d)


define GEN_PREREQ
$(CXX) -MF $1 -MM $2 -MT "$(subst .d,.o,$1) $1" $(CXXFLAGS)
endef

define COMPILE
$(CXX) -o $1 -c $(filter %.cpp,$2) $(CXXFLAGS)
endef

define LINK
$(CXX) -o $1 $(filter %.o %.a,$2) $(CXXFLAGS) $(LDFLAGS)
endef

define MAKEDIR
IF NOT EXIST $(subst /,\,$1) MKDIR $(subst /,\,$1)
endef

define DELTREE
IF EXIST $(subst /,\,$1) RMDIR /S /Q $(subst /,\,$1)
endef
