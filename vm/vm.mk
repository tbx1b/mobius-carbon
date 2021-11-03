VM_FILES += $(shell find vm -type f -name '*.c')
VM_OBJ_FILES += $(VM_FILES:%.c=%.o)
VM_DEP_FILES += $(VM_OBJ_FILES:%.o=%.d)