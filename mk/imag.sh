#!/usr/bin/env sh

mkdir -p rootfs

cp -v limine.cfg limine/limine.sys \
      limine/limine-cd.bin limine/limine-eltorito-efi.bin rootfs/
 
# Create the bootable ISO.
xorriso -as mkisofs -b limine-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot limine-eltorito-efi.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        rootfs -o image.iso
 
# Install Limine stage 1 and 2 for legacy BIOS boot.
./limine/limine-install image.iso