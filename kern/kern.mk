KERN_FILES := $(shell find kern -type f -name '*.c')
KERN_OBJ_FILES := $(KERN_FILES:%.c=%.o)
KERN_DEP_FILES := $(KERN_OBJ_FILES:%.o=%.d)