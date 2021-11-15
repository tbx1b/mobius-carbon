// =========-------------------- chips_serial.c  ---------------------=========//
//                       Copyright 2021 MobiusLoopFour
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
// 
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// =========----------------------------------------------------------=========// 

#include <sys/defs.h>

int 
spbaudrate(unsigned short com, unsigned short div) 
{
  iooutb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);

  iooutb(SERIAL_DATA_PORT(com), (div >> 8) & 0x00FF);
  iooutb(SERIAL_DATA_PORT(com), div & 0x00FF);

  return 0;
}

int 
spln(unsigned short c) 
{
  /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
   * Content: | d | b | prty  | s | dl  |
   * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
   */
  iooutb(SERIAL_LINE_COMMAND_PORT(c), 0x03);
  return 0;
}

int
init_serialp(void)
{
  iooutb(PORT + 1, 0x00); // Disable all interrupts
  iooutb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
  iooutb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  iooutb(PORT + 1, 0x00); //                  (hi byte)
  iooutb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
  iooutb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  iooutb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
  iooutb(PORT + 4, 0x1E); // Set in loopback mode, test the serial chip
  iooutb(PORT + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

  spln(PORT);
  spbaudrate(PORT, 2);    // We'll use 2 as the divisor

  if (ioinb(PORT + 0) != 0xAE) {
    return (1);
  }
  iooutb(PORT + 4, 0x0F);

  return (0);
}