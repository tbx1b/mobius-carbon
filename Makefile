all:
	@make -C build all
run:
	@qemu-system-i386 -kernel build/c_kernel -serial stdio
clean:
	@make -C build clean
deconf:
	./deconf
conf:
	./conf
.PHONY : conf deconf all clean run
