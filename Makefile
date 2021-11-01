all:
	make -C dwb all

clean:
	@make -C dwb clean

iso:
	@cd dwb && ./imag.sh
	@echo "Return to host to emulate"

run:
	qemu-system-i386 dwb/image.iso

.PHONY : all
.PHONY : clean
.PHONY : run