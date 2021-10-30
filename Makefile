include config/defaults.make

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

LIBKERN_O = $(call rwildcard, libkern/build/CMakeFiles/libkern.dir, *.o)
OSCK_O = $(call rwildcard, osck/build/CMakeFiles/kernel.dir, *.o)

# all
OBJ_FILES = $(LIBKERN_O) $(OSCK_O)

.PHONY : all
all: obj
	$(LD) $(LDFLAGS) -o $(KERN_TERGET)/a.out -T$(LSCRIPT) $(OBJ_FILES)

.PHONY : obj
obj:
	@make -C libsa
	@make -C osck
	@make -C libkern

.PHONY : clean
clean:
	@make -C libsa clean
	@make -C osck clean
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

.PHONY : push
push: clean
	@rm -rf osck/build
	@rm -rf libkern/build
	git push

.PHONY : rebuild_cache
rebuild_cache:
	@make -C osck rebuild_cache
	@make -C libkern rebuild_cache
	@make clean
