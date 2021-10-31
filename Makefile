.PHONY : all
all:
	@bear -- make -C head/mcos

.PHONY : clean
clean:
	@make -C head/mcos clean
	@(rm Carbon.iso) || true

.PHONY : iso
iso:
	@mkdir -p rootfs/System
	@mkdir -p rootfs/boot
 
	@cp -v head/mcos/com.mobius.System rootfs/System/com.mobius.System
	
	@cp -v dwb/limine.cfg head/libsa/limine.sys rootfs/boot

	@cp -v head/libsa/limine-cd.bin head/libsa/limine-eltorito-efi.bin rootfs

	@xorriso -as mkisofs -b limine-cd.bin \
	-no-emul-boot -boot-load-size 4 -boot-info-table \
	--efi-boot limine-eltorito-efi.bin \
	-efi-boot-part --efi-boot-image --protective-msdos-label \
	rootfs -o Carbon.iso

	@./head/libsa/limine-install Carbon.iso

.PHONY : qemu
qemu:
	qemu-system-x86_64 -m 4G Carbon.iso