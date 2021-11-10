#include <sys/types.h>
#include <device/io.h>

#define PORT 0x3f8

/**
 * @brief Log a character on the serial port
 * 
 * @param c The character
 * @return uint 0 on success
 */
uint putc(const char c) {
  outb(PORT, c);
  return 0;
}
