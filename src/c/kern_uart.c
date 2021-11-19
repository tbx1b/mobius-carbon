#include <uart.h>

int __kern_putc(char ch) {
	while ((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
	return *UART_THR = ch;
}

void __kern_puts(char str[]) {
	while (*str) __kern_putc(*str++);
}