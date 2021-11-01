all:
	@bear -- make -C mk all

clean:
	@make -C mk clean

iso:
	@cd mk && ./imag.sh
	@echo "Return to host to emulate"

run:
	qemu-system-i386 mk/image.iso

.PHONY : all
.PHONY : clean
.PHONY : run