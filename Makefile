all:
	@bear -- make -C Make all

clean:
	@make -C Make clean

iso:
	@cd Make && ./imag.sh
	@echo "Return to host to emulate"

run:
	qemu-system-i386 Make/image.iso

.PHONY : all
.PHONY : clean
.PHONY : run