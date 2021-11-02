-include $(DEPS)
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.s.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@