A=aconf
C=chips/chips_
R=csr/csr_
K=kern/kern_
S=s
Y=sys

O = \
	$Cserial.o \
	$Cmmu.o \
	\
	$Rmascotte.o \
	$Rcnsl.o \
	$Rtty.o \
	\
	$Kentry.o \
	$Kmain.o \
	\
	$S/cn.o \
	$S/io.o \
	$S/platf.o \
	$S/str1.o \
	$S/str2.o \
	$S/str3.o \
	$S/str4.o \
	$S/str5.o \
	$S/str6.o \

D = $(O:.o=.d)
T = i686-elf-

CC := $Tgcc
AS := $Tgcc
LD := $Tld
OBJCOPY := $Tobjcopy
OBJDUMP := $Tobjdump

CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -D__KERNEL__ -I.$Y -I. -Wno-implicit-int
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
ASFLAGS = -m32 -gdwarf-2 -Wa,-divide -D__ASSEMBLER__ -D__KERNEL__ -I.$Y -I.
LDFLAGS += -m $(shell $(LD) -V | grep elf_i386 2>/dev/null | head -n 1)
CFLAGS += -D__KERNEL__

ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]no-pie'),)
CFLAGS += -fno-pie -no-pie
endif
ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]nopie'),)
CFLAGS += -fno-pie -nopie
endif

# Disable PIE when possible
ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]no-pie'),)
CFLAGS += -fno-pie -no-pie
endif
ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]nopie'),)
CFLAGS += -fno-pie -nopie
endif

bin/kernel: $O $A/kernel.ld
	mkdir -p bin
	$(LD) $(LDFLAGS) -T$A/kernel.ld $O -o $@
	$(OBJDUMP) -S bin/kernel > bin/kernel.s
	$(OBJDUMP) -t bin/kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > bin/kernel.dsym

clean:
	@(rm $O $D &> /dev/null) || true
	@(rm bin/kernel &> /dev/null) || true

qemu:
	qemu-system-i386 -m 4G -smp 4 -kernel bin/kernel -serial mon:stdio

.PHONY : qemu clean

-include $D
%.o: %.s
	$(AS) $(ASFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@