-include $(DEPS)
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.cpp.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

%.s.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@