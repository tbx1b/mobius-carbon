all:
	@bear make -C mk all

clean:
	@make -C mk clean

iso:
	@cd mk && ./imag.sh
	@echo "Return to host to emulate"

.PHONY : all
.PHONY : clean