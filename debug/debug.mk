DEBUG_FILES := $(shell find debug -type f -name '*.c')
DEBUG_OBJ_FILES := $(DEBUG_FILES:%.c=%.o)
DEBUG_DEP_FILES := $(DEBUG_OBJ_FILES:%.o=%.d)