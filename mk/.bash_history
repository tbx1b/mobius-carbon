cd
apt install grub xorriso
clear
grub-file --is-x86-multiboot myos.bin
grub-file --is-x86-multiboot os.bin
echo $?
exit
exit
