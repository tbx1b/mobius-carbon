#!/usr/bin/env sh

mkdir -p rootfs/boot

cp -v limine.cfg limine/limine.sys \
      limine/limine-cd.bin limine/limine-eltorito-efi.bin rootfs
 
# Create the bootable ISO.
xorriso -as mkisofs -b limine-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot limine-eltorito-efi.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        rootfs -o image.iso
 
# Checks the OS, and install the proper Limine stage 1 and 2 for legacy BIOS boot.
if [[ $OSTYPE == 'darwin'* ]]; then
      ./limine/limine-install image.iso
else
      ./limine/limine-install-linux-x86_64 image.iso
fi
