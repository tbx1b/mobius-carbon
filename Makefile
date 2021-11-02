include conf/arch
include conf/cflags
include conf/cppflags
include conf/ldflags

include i386/i386.mk
include kern/kern.mk
include libc/libc.mk
include debug/debug.mk
include io/io.mk
include vm/vm.mk

include conf/toolchain.mk
include conf/rules.mk

PROJECT := kernel8.img
DEPS := \
			$(KERN_DEP_FILES) \
			$(LIBC_DEP_FILES) \
			$(X64_DEP_FILES) \
			$(STAND_DEP_FILES) \
			$(TERMIO_DEP_FILES) \
			$(DEBUG_DEP_FILES) \
			$(VM_DEP_FILES) \
			$(IO_DEP_FILES)

OBJ := \
			$(KERN_OBJ_FILES) \
			$(X64_OBJ_FILES) \
			$(LIBC_OBJ_FILES) \
			$(STAND_OBJ_FILES) \
			$(TERMIO_OBJ_FILES) \
			$(DEBUG_OBJ_FILES) \
			$(VM_OBJ_FILES) \
			$(IO_OBJ_FILES)

#########################################################################

all : $(PROJECT)

clean: 
	rm $(OBJ) build/boot/kernel8.* image.iso || true

run:
	qemu-system-x86_64 image.iso

image:
	mkdir -p build/boot
	cp -v conf/limine.cfg limine/limine.sys \
      limine/limine-cd.bin limine/limine-eltorito-efi.bin build/
	
	xorriso -as mkisofs -b limine-cd.bin \
	-no-emul-boot -boot-load-size 4 -boot-info-table \
	--efi-boot limine-eltorito-efi.bin \
	-efi-boot-part --efi-boot-image --protective-msdos-label \
	build -o image.iso

	./limine/limine-install image.iso

.PHONY : all clean run image

$(PROJECT) : $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o build/boot/kernel8.elf
	$(STRIP) build/boot/kernel8.elf