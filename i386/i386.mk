X64_FILES += $(shell find i386 -type f -name '*.S')
X64_CFILES += $(shell find i386 -type f -name '*.c')
X64_OBJ_FILES += $(X64_FILES:%.S=%.s.o) $(X64_CFILES:%.c=%.o)
X64_DEP_FILES += $(X64_OBJ_FILES:%.o=%.d)