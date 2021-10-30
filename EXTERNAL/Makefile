OVMF = /usr/share/qemu/bios-TianoCoreEFI.bin

all: $(wildcard examples/*)

.PHONY: Makefile

%: Makefile
	@test -f $@/Makefile && make -C $@ all 2>/dev/null

test:
	qemu-system-x86_64 -m 256M -hda fat:rw:../rootfs \
	-drive if=pflash,format=raw,unit=0,file="OVMF_CODE-pure-efi.fd",readonly=on \
	-drive if=pflash,format=raw,unit=1,file="OVMF_VARS-pure-efi.fd" -net none
