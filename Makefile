CC := riscv64-elf-gcc
CFLAGS := -nostdlib -fno-builtin -mcmodel=medany -march=rv32ima -mabi=ilp32
CFLAGS += -I./include -I./include/risc32

QEMU := qemu-system-riscv32
QFLAGS := -nographic -smp 4 -machine virt -bios none

OBJDUMP = riscv64-elf-objdump

S=src/s
C=src/c
KNAME=krnl.sw

SRC := \
	$S/start.S \
	$S/switch.S \
	$C/kern_main.c \
	$C/kern_uart.c \
	$C/kern_time.c \
	$C/kern_announce.c \
	$C/kern_user_init.c \
	$C/sched_pool.c \
	$C/sched_proc.c \
	$C/lib_math.c \
	$S/time.S

all: $(KNAME)

$(KNAME): $(SRC)
	$(CC) $(CFLAGS) -T krnl.ld -o $(KNAME) $^

clean:
	@(rm krnl.sw) || true

qemu: $(TARGET)
	@qemu-system-riscv32 -M ? | grep virt >/dev/null || exit
	$(QEMU) $(QFLAGS) -kernel $(KNAME)

.PHONY : all qemu clean