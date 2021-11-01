#!/usr/bin/env sh

mkdir -p Root\ File\ System/boot

cp -v limine.cfg limine/limine.sys \
      limine/limine-cd.bin limine/limine-eltorito-efi.bin Root\ File\ System/
 
# Create the bootable ISO.
xorriso -as mkisofs -b limine-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot limine-eltorito-efi.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        Root\ File\ System/ -o image.iso
 
# Install Limine stage 1 and 2 for legacy BIOS boot.
./limine/limine-install image.iso