IO_FILES := $(shell find io -type f -name '*.c')
IO_OBJ_FILES := $(IO_FILES:%.c=%.o)
IO_DEP_FILES := $(IO_OBJ_FILES:%.o=%.d)