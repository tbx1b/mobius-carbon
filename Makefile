all:
	make -C mk all

clean:
	@make -C mk clean

iso:
	@cd mk && ./imag.sh
	@echo "Return to host to emulate"

run:
	qemu-system-x86_64 -m 3G -serial stdio mk/image.iso

.PHONY : all
.PHONY : clean
.PHONY : run