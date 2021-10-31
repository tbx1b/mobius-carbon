include config/defaults.make

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

LIBKERN_O = $(call rwildcard, libkern/build/CMakeFiles/libkern.dir, *.o)
OSCK_O = $(call rwildcard, osck/build/CMakeFiles/kernel.dir, *.o)
ARCH_O = $(call rwildcard, pexpert/build/CMakeFiles/kernel.dir, *.o)

# all
OBJ_FILES = $(LIBKERN_O) $(OSCK_O) $(ARCH_O)

.PHONY : all
all: obj
	$(LD) $(LDFLAGS) -o $(KERN_TERGET)/a.out -T$(LSCRIPT) $(OBJ_FILES)

.PHONY : obj
obj:
	@make -C libsa
	@make -C osck
	@make -C pexpert
	@make -C libkern

.PHONY : clean
clean:
	@make -C libsa clean
	@make -C osck clean
	@make -C pexpert clean
	@make -C libkern clean

.PHONY : qemu
qemu:
	@make -C EXTERNAL test

# update when adding new modules
.PHONY : configure
configure:
	@mkdir -p osck/build
	@mkdir -p libkern/build
	@cd osck/build && cmake ../
	@cd libkern/build && cmake ../
	@make clean

.PHONY : release_ready
push: release_ready
	@rm -rf osck/build
	@rm -rf libkern/build
	git push

.PHONY : rebuild_cache
rebuild_cache:
	@make -C osck rebuild_cache
	@make -C pexpert rebuild_cache
	@make -C libkern rebuild_cache
	@make clean

.PHONY : help
help:
	@printf '\e[1;32m%-6s\e[m\n' "[make help: 			Display this help message]"
	@printf '\e[1;32m%-6s\e[m\n' "[make configure: 		Configure the repository to be built with make]"
	@printf '\e[1;32m%-6s\e[m\n' "[make all: 			Build the whole project$@]"
	@printf '\e[1;32m%-6s\e[m\n' "[make rebuild_cache: 		Rebuild the CMake cache (when adding/removing files)]"
	@printf '\e[1;32m%-6s\e[m\n' "[make qemu: 			Run the QEMU emulator with the rootfs as boot medium]"

