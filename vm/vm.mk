VM_FILES += $(shell find vm -type f -name '*.c')
VM_CFILES += $(shell find vm -type f -name '*.cpp')
VM_OBJ_FILES += $(VM_FILES:%.c=%.c.o) $(VM_CFILES:%.cpp=%.cpp.o)
VM_DEP_FILES += $(VM_OBJ_FILES:%.o=%.d)