
SHELL := cmd.exe

define del_build_tree
@IF EXIST build rmdir /S /Q build 2>NUL
endef


all:
	@make -C src
	$(call del_build_tree)
	@mkdir build
	@move src\anika.exe build\
	
.PHONY: clean
clean:
	$(call del_build_tree)
	make clean -C src
	make clean -C src/dejlib
	
