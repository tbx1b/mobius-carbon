#########################################################################
#	file: 		Makefil00												#
#	brief: 		Compile the kernel										#
#	author: 	mobiusloop4												#
#	license:	default													#
#########################################################################
include Makefil00
CFLAGS := -I../src/head \
			-I../src/mtss/ \
			-I../src/mtss/i86pc/sys \
            -std=c17 \
			-ffreestanding -nostdlib -fno-builtin -fno-stack-protector \
			-mno-red-zone -mno-red-zone -fno-builtin \
			-Wno-implicit-int -Ofast -D $(MODE)
ASFLAGS := -O2
LDFLAGS := -T../mk/lnk.lds -nostdlib
CFILES := $(shell find \
						../src/mtss/i86pc \
						../src/lib \
						-type f -name '*.c')
ASFILES := $(shell find \
						../src/mtss/i86pc \
						../src/stand/i86pc \
						-type f -name '*.S')
NASMFILES := $(shell find \
						../src/mtss/i86pc \
						../src/stand/i86pc \
						-type f -name '*.asm')
OBJ := $(CFILES:.c=.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o)
HEADER_DEPS := $(CFILES:.c=.d)
#########################################################################
all : $(PROJECT)
.PHONY : all
	mkdir -p $(BLDIR)/boot

$(PROJECT) : $(OBJ)
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
	$(AS) $(ASFLAGS) $< -o $@

clean:
	(rm image.iso $(OBJ)) || true
.PHONY : clean
# EOF