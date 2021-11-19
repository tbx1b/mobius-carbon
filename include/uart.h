#pragma once

#define UART                0x10000000
#define UART_THR            (unsigned char*)(UART+0x00) // THR:transmitter holding register
#define UART_LSR            (unsigned char*)(UART+0x05) // LSR:line status register
#define UART_LSR_EMPTY_MASK 0x40                        // LSR Bit 6: Transmitter empty; both the THR and LSR are empty

int __kern_putc(char ch);
void __kern_puts(char str[]);

#define putc __kern_putc
#define puts __kern_puts