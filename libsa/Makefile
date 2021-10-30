TARGET = ../rootfs/System/Stash/BootPicker.pcsw
__LD = lld-link
SRCS = $(wildcard *.c)

CFLAGS = -pedantic -Wall -Wextra -Werror -Ofast --define-macro BATEAU -Wno-implicit-int

include uefi/Makefile
