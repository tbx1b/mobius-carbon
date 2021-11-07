#########################################################################
#	file: 		Makefil00												#
#	brief: 		Compile the kernel										#
#	author: 	mobiusloop4												#
#	license:	default													#
#########################################################################
include Makefil00
CFLAGS := -I../src \
			-I../src/libc/ \
			-I../src/libcarbon \
			-I../src/mtss \
            -std=c17 \
			-ffreestanding -nostdlib -fno-builtin -fno-stack-protector \
			-mno-red-zone -mno-red-zone -fno-builtin \
			-Wno-implicit-int -O2 -D $(MODE)
ASFLAGS := \
			-I../src \
			-I../src/libc/ \
			-I../src/libcarbon \
			-I../src/mtss -c
LDFLAGS := -T../mk/lnk.lds -nostdlib
CFILES := $(shell find \
						../src \
						-type f -name '*.c')
ASFILES := $(shell find \
						../src \
						-type f -name '*.S')
NASMFILES := $(shell find \
						../src \
						-type f -name '*.asm')
OBJ := $(CFILES:.c=.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o)
HEADER_DEPS := $(CFILES:.c=.d)
#########################################################################
all : $(PROJECT)
.PHONY : all
	mkdir -p $(BLDIR)/boot

$(PROJECT) : $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $(BLDIR)/boot/$@ -L -lgcc

$(PROJECT)-release : $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $(BLDIR)/boot/$@ -L -lgcc
	$(STRIP) --strip-all $(BLDIR)/boot/$@
#########################################################################
# Compilation rules for *.c and *.s files.
-include $(HEADER_DEPS)
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.asm.o: %.asm
	$(NASM) -felf32 $< -o $@

%.S.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@

clean:
	(rm image.iso $(OBJ)) || true
.PHONY : clean
# EOF