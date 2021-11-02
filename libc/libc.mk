LIBC_FILES := $(shell find libc -type f -name '*.c')
LIBC_OBJ_FILES := $(LIBC_FILES:%.c=%.o)
LIBC_DEP_FILES := $(LIBC_OBJ_FILES:%.o=%.d)