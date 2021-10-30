LD = ld.lld
LDFLAGS = -static -Bsymbolic -nostdlib
LSCRIPT = config/carbon.ld

KERN_TERGET = rootfs/System/Kernel