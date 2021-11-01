#########################################################################
#	file: 		Makefil00												#
#	brief: 		Compile the kernel										#
#	author: 	mobiusloop4												#
#	license:	default													#
#########################################################################
include Makefil00
CFLAGS := -I../src/head \
			-I../src/osck/$(TARGET)/sys \
			-I../src/osck/sys \
			-I../src/osck/$(TARGET)/sys \
            -std=c17 \
			-ffreestanding -nostdlib -fno-builtin -fno-stack-protector \
			-mno-red-zone -mno-red-zone -fno-builtin \
			-Wno-implicit-int -O2 -lgcc
ASFLAGS := -O2
LDFLAGS := -T../mk/lnk.lds -nostdlib
CFILES := $(shell find ../src/osck/$(TARGET) ../src/lib ../src/stand/$(TARGET) -type f -name '*.c')
ASFILES := $(shell find ../src/osck/$(TARGET) ../src/stand/$(TARGET) -type f -name '*.s')
OBJ := $(CFILES:.c=.o) $(ASFILES:.s=.s.o)
HEADER_DEPS := $(CFILES:.c=.d)
#########################################################################
all : $(PROJECT)
.PHONY : all
	mkdir -p $(BLDIR)
	multiboot.sh

$(PROJECT) : $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $(BLDIR)/$@
	$(STRIP) --strip-all $(BLDIR)/$@
#########################################################################
# Compilation rules for *.c and *.s files.
-include $(HEADER_DEPS)
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.s.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	(rm image.iso $(OBJ)) || true
.PHONY : clean
# EOF