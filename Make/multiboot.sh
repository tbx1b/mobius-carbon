if grub-file --is-x86-multiboot rootfs/syscbk; then
  echo multiboot confirmed
  exit 0
else
  echo the file is not multiboot
  exit 1
fi