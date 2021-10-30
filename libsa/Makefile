TARGET = ../rootfs/System/Stash/BootPicker.pcsw
__LD = lld-link
SRCS = $(wildcard *.c)

CFLAGS = -pedantic -Wall -Wextra -Werror -Ofast --define-macro BATEAU -Wno-incompatible-function-pointer-types -Wno-unused-variable -Wno-implicit-int

include uefi/Makefile
