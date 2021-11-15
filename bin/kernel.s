
bin/kernel:     file format elf32-i386


Disassembly of section .text:

00100000 <spbaudrate>:
#include <sys/defs.h>

int 
spbaudrate(unsigned short com, unsigned short div) 
{
  100000:	55                   	push   %ebp
  100001:	89 e5                	mov    %esp,%ebp
  100003:	56                   	push   %esi
  100004:	53                   	push   %ebx
  100005:	8b 5d 08             	mov    0x8(%ebp),%ebx
  100008:	8b 75 0c             	mov    0xc(%ebp),%esi
  iooutb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  10000b:	8d 43 03             	lea    0x3(%ebx),%eax

  iooutb(SERIAL_DATA_PORT(com), (div >> 8) & 0x00FF);
  10000e:	0f b7 db             	movzwl %bx,%ebx
  iooutb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  100011:	83 ec 08             	sub    $0x8,%esp
  100014:	0f b7 c0             	movzwl %ax,%eax
  100017:	68 80 00 00 00       	push   $0x80
  10001c:	50                   	push   %eax
  10001d:	e8 1f 06 00 00       	call   100641 <iooutb>
  iooutb(SERIAL_DATA_PORT(com), (div >> 8) & 0x00FF);
  100022:	58                   	pop    %eax
  100023:	89 f0                	mov    %esi,%eax
  100025:	5a                   	pop    %edx
  100026:	0f b6 c4             	movzbl %ah,%eax
  100029:	50                   	push   %eax
  10002a:	53                   	push   %ebx
  10002b:	e8 11 06 00 00       	call   100641 <iooutb>
  iooutb(SERIAL_DATA_PORT(com), div & 0x00FF);
  100030:	59                   	pop    %ecx
  100031:	58                   	pop    %eax
  100032:	89 f0                	mov    %esi,%eax
  100034:	0f b6 f0             	movzbl %al,%esi
  100037:	56                   	push   %esi
  100038:	53                   	push   %ebx
  100039:	e8 03 06 00 00       	call   100641 <iooutb>

  return 0;
}
  10003e:	8d 65 f8             	lea    -0x8(%ebp),%esp
  100041:	31 c0                	xor    %eax,%eax
  100043:	5b                   	pop    %ebx
  100044:	5e                   	pop    %esi
  100045:	5d                   	pop    %ebp
  100046:	c3                   	ret    
  100047:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10004e:	66 90                	xchg   %ax,%ax

00100050 <spln>:

int 
spln(unsigned short c) 
{
  100050:	55                   	push   %ebp
  100051:	89 e5                	mov    %esp,%ebp
  100053:	83 ec 10             	sub    $0x10,%esp
  /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
   * Content: | d | b | prty  | s | dl  |
   * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
   */
  iooutb(SERIAL_LINE_COMMAND_PORT(c), 0x03);
  100056:	0f b7 45 08          	movzwl 0x8(%ebp),%eax
  10005a:	6a 03                	push   $0x3
  10005c:	83 c0 03             	add    $0x3,%eax
  10005f:	0f b7 c0             	movzwl %ax,%eax
  100062:	50                   	push   %eax
  100063:	e8 d9 05 00 00       	call   100641 <iooutb>
  return 0;
}
  100068:	31 c0                	xor    %eax,%eax
  10006a:	c9                   	leave  
  10006b:	c3                   	ret    
  10006c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00100070 <init_serialp>:

int
init_serialp(void)
{
  100070:	55                   	push   %ebp
  100071:	89 e5                	mov    %esp,%ebp
  100073:	83 ec 10             	sub    $0x10,%esp
  iooutb(PORT + 1, 0x00); // Disable all interrupts
  100076:	6a 00                	push   $0x0
  100078:	68 f9 03 00 00       	push   $0x3f9
  10007d:	e8 bf 05 00 00       	call   100641 <iooutb>
  iooutb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
  100082:	58                   	pop    %eax
  100083:	5a                   	pop    %edx
  100084:	68 80 00 00 00       	push   $0x80
  100089:	68 fb 03 00 00       	push   $0x3fb
  10008e:	e8 ae 05 00 00       	call   100641 <iooutb>
  iooutb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  100093:	59                   	pop    %ecx
  100094:	58                   	pop    %eax
  100095:	6a 03                	push   $0x3
  100097:	68 f8 03 00 00       	push   $0x3f8
  10009c:	e8 a0 05 00 00       	call   100641 <iooutb>
  iooutb(PORT + 1, 0x00); //                  (hi byte)
  1000a1:	58                   	pop    %eax
  1000a2:	5a                   	pop    %edx
  1000a3:	6a 00                	push   $0x0
  1000a5:	68 f9 03 00 00       	push   $0x3f9
  1000aa:	e8 92 05 00 00       	call   100641 <iooutb>
  iooutb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
  1000af:	59                   	pop    %ecx
  1000b0:	58                   	pop    %eax
  1000b1:	6a 03                	push   $0x3
  1000b3:	68 fb 03 00 00       	push   $0x3fb
  1000b8:	e8 84 05 00 00       	call   100641 <iooutb>
  iooutb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  1000bd:	58                   	pop    %eax
  1000be:	5a                   	pop    %edx
  1000bf:	68 c7 00 00 00       	push   $0xc7
  1000c4:	68 fa 03 00 00       	push   $0x3fa
  1000c9:	e8 73 05 00 00       	call   100641 <iooutb>
  iooutb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
  1000ce:	59                   	pop    %ecx
  1000cf:	58                   	pop    %eax
  1000d0:	6a 0b                	push   $0xb
  1000d2:	68 fc 03 00 00       	push   $0x3fc
  1000d7:	e8 65 05 00 00       	call   100641 <iooutb>
  iooutb(PORT + 4, 0x1E); // Set in loopback mode, test the serial chip
  1000dc:	58                   	pop    %eax
  1000dd:	5a                   	pop    %edx
  1000de:	6a 1e                	push   $0x1e
  1000e0:	68 fc 03 00 00       	push   $0x3fc
  1000e5:	e8 57 05 00 00       	call   100641 <iooutb>
  iooutb(PORT + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)
  1000ea:	59                   	pop    %ecx
  1000eb:	58                   	pop    %eax
  1000ec:	68 ae 00 00 00       	push   $0xae
  1000f1:	68 f8 03 00 00       	push   $0x3f8
  1000f6:	e8 46 05 00 00       	call   100641 <iooutb>
  iooutb(SERIAL_LINE_COMMAND_PORT(c), 0x03);
  1000fb:	58                   	pop    %eax
  1000fc:	5a                   	pop    %edx
  1000fd:	6a 03                	push   $0x3
  1000ff:	68 fb 03 00 00       	push   $0x3fb
  100104:	e8 38 05 00 00       	call   100641 <iooutb>
  iooutb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  100109:	59                   	pop    %ecx
  10010a:	58                   	pop    %eax
  10010b:	68 80 00 00 00       	push   $0x80
  100110:	68 fb 03 00 00       	push   $0x3fb
  100115:	e8 27 05 00 00       	call   100641 <iooutb>
  iooutb(SERIAL_DATA_PORT(com), (div >> 8) & 0x00FF);
  10011a:	58                   	pop    %eax
  10011b:	5a                   	pop    %edx
  10011c:	6a 00                	push   $0x0
  10011e:	68 f8 03 00 00       	push   $0x3f8
  100123:	e8 19 05 00 00       	call   100641 <iooutb>
  iooutb(SERIAL_DATA_PORT(com), div & 0x00FF);
  100128:	59                   	pop    %ecx
  100129:	58                   	pop    %eax
  10012a:	6a 02                	push   $0x2
  10012c:	68 f8 03 00 00       	push   $0x3f8
  100131:	e8 0b 05 00 00       	call   100641 <iooutb>

  spln(PORT);
  spbaudrate(PORT, 2);    // We'll use 2 as the divisor

  if (ioinb(PORT + 0) != 0xAE) {
  100136:	c7 04 24 f8 03 00 00 	movl   $0x3f8,(%esp)
  10013d:	e8 0a 05 00 00       	call   10064c <ioinb>
  100142:	83 c4 10             	add    $0x10,%esp
  100145:	89 c2                	mov    %eax,%edx
  100147:	b8 01 00 00 00       	mov    $0x1,%eax
  10014c:	80 fa ae             	cmp    $0xae,%dl
  10014f:	74 0f                	je     100160 <init_serialp+0xf0>
    return (1);
  }
  iooutb(PORT + 4, 0x0F);

  return (0);
  100151:	c9                   	leave  
  100152:	c3                   	ret    
  100153:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10015a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
  iooutb(PORT + 4, 0x0F);
  100160:	83 ec 08             	sub    $0x8,%esp
  100163:	6a 0f                	push   $0xf
  100165:	68 fc 03 00 00       	push   $0x3fc
  10016a:	e8 d2 04 00 00       	call   100641 <iooutb>
  return (0);
  10016f:	83 c4 10             	add    $0x10,%esp
  100172:	31 c0                	xor    %eax,%eax
  100174:	c9                   	leave  
  100175:	c3                   	ret    
  100176:	66 90                	xchg   %ax,%ax
  100178:	66 90                	xchg   %ax,%ax
  10017a:	66 90                	xchg   %ax,%ax
  10017c:	66 90                	xchg   %ax,%ax
  10017e:	66 90                	xchg   %ax,%ax

00100180 <seginit>:

struct sdesc gdt[6];

int
seginit(void)
{  
  100180:	55                   	push   %ebp
  100181:	89 e5                	mov    %esp,%ebp
  100183:	83 ec 10             	sub    $0x10,%esp
  gdt[SEG_KCODE] = SEG(ASBX|ASBR, 0, 0xffffffff, 0);
  100186:	c7 05 08 20 10 00 ff 	movl   $0xffff,0x102008
  10018d:	ff 00 00 
  gdt[SEG_KDATA] = SEG(ASBW, 0, 0xffffffff, 0);
  gdt[SEG_UCODE] = SEG(ASBX|ASBR, 0, 0xffffffff, DPL_USER);
  gdt[SEG_UDATA] = SEG(ASBW, 0, 0xffffffff, DPL_USER);
  lgdt(gdt, sizeof(gdt));
  100190:	6a 30                	push   $0x30
  100192:	68 00 20 10 00       	push   $0x102000
  gdt[SEG_KCODE] = SEG(ASBX|ASBR, 0, 0xffffffff, 0);
  100197:	c7 05 0c 20 10 00 00 	movl   $0xcf9a00,0x10200c
  10019e:	9a cf 00 
  gdt[SEG_KDATA] = SEG(ASBW, 0, 0xffffffff, 0);
  1001a1:	c7 05 10 20 10 00 ff 	movl   $0xffff,0x102010
  1001a8:	ff 00 00 
  1001ab:	c7 05 14 20 10 00 00 	movl   $0xcf9200,0x102014
  1001b2:	92 cf 00 
  gdt[SEG_UCODE] = SEG(ASBX|ASBR, 0, 0xffffffff, DPL_USER);
  1001b5:	c7 05 18 20 10 00 ff 	movl   $0xffff,0x102018
  1001bc:	ff 00 00 
  1001bf:	c7 05 1c 20 10 00 00 	movl   $0xcffa00,0x10201c
  1001c6:	fa cf 00 
  gdt[SEG_UDATA] = SEG(ASBW, 0, 0xffffffff, DPL_USER);
  1001c9:	c7 05 20 20 10 00 ff 	movl   $0xffff,0x102020
  1001d0:	ff 00 00 
  1001d3:	c7 05 24 20 10 00 00 	movl   $0xcff200,0x102024
  1001da:	f2 cf 00 
  lgdt(gdt, sizeof(gdt));
  1001dd:	e8 2a 05 00 00       	call   10070c <lgdt>

  return 0;
  1001e2:	31 c0                	xor    %eax,%eax
  1001e4:	c9                   	leave  
  1001e5:	c3                   	ret    
  1001e6:	66 90                	xchg   %ax,%ax
  1001e8:	66 90                	xchg   %ax,%ax
  1001ea:	66 90                	xchg   %ax,%ax
  1001ec:	66 90                	xchg   %ax,%ax
  1001ee:	66 90                	xchg   %ax,%ax

001001f0 <announce>:
#include <sys/defs.h>

void
announce()
{
  1001f0:	55                   	push   %ebp
  1001f1:	89 e5                	mov    %esp,%ebp
  1001f3:	83 ec 14             	sub    $0x14,%esp
  ttyputs("= CARBON I -- PRERELEASE BUILD =\n");
  1001f6:	68 9c 17 10 00       	push   $0x10179c
  1001fb:	e8 50 02 00 00       	call   100450 <ttyputs>
  return;
  100200:	83 c4 10             	add    $0x10,%esp
  100203:	c9                   	leave  
  100204:	c3                   	ret    
  100205:	66 90                	xchg   %ax,%ax
  100207:	66 90                	xchg   %ax,%ax
  100209:	66 90                	xchg   %ax,%ax
  10020b:	66 90                	xchg   %ax,%ax
  10020d:	66 90                	xchg   %ax,%ax
  10020f:	90                   	nop

00100210 <cnsetcolor>:
    }
  }
  return 0;
}

cnsetcolor(const unsigned char clr) {
  100210:	55                   	push   %ebp
  100211:	89 e5                	mov    %esp,%ebp
  cncolor = clr;
  100213:	8b 45 08             	mov    0x8(%ebp),%eax
  return 0;
}
  100216:	5d                   	pop    %ebp
  cncolor = clr;
  100217:	a2 34 20 10 00       	mov    %al,0x102034
}
  10021c:	31 c0                	xor    %eax,%eax
  10021e:	c3                   	ret    
  10021f:	90                   	nop

00100220 <cnputs>:

cnputs(const char str[])
{
  100220:	55                   	push   %ebp
  100221:	89 e5                	mov    %esp,%ebp
  100223:	57                   	push   %edi
  100224:	56                   	push   %esi
  100225:	53                   	push   %ebx
  100226:	83 ec 1c             	sub    $0x1c,%esp
  cnbuffer[i] = cnentry(c, clr);
  100229:	a1 30 20 10 00       	mov    0x102030,%eax
{
  10022e:	8b 5d 08             	mov    0x8(%ebp),%ebx
  return fg | bg << 4;
}

unsigned short 
cnentry(const unsigned char uc, const unsigned char color) {
  return (unsigned short)uc | (unsigned short)color << 8;
  100231:	c6 45 e7 00          	movb   $0x0,-0x19(%ebp)
  100235:	8b 3d 38 20 10 00    	mov    0x102038,%edi
  cnbuffer[i] = cnentry(c, clr);
  10023b:	89 45 e0             	mov    %eax,-0x20(%ebp)
  cnput(c, cncolor, cncolumn, cnrow);
  10023e:	0f b6 05 34 20 10 00 	movzbl 0x102034,%eax
  return (unsigned short)uc | (unsigned short)color << 8;
  100245:	c1 e0 08             	shl    $0x8,%eax
  100248:	66 89 45 e4          	mov    %ax,-0x1c(%ebp)
  10024c:	a1 3c 20 10 00       	mov    0x10203c,%eax
  100251:	89 45 dc             	mov    %eax,-0x24(%ebp)
  100254:	89 c6                	mov    %eax,%esi
  100256:	eb 17                	jmp    10026f <cnputs+0x4f>
  100258:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10025f:	90                   	nop
      continue;
  100260:	88 55 e7             	mov    %dl,-0x19(%ebp)
      cnrow++;
  100263:	83 c6 01             	add    $0x1,%esi
      cncolumn = 0;
  100266:	31 ff                	xor    %edi,%edi
  } while(*str++);
  100268:	83 c3 01             	add    $0x1,%ebx
  10026b:	84 c0                	test   %al,%al
  10026d:	74 3a                	je     1002a9 <cnputs+0x89>
    if (*str=='\n' || *str=='\r') {
  10026f:	0f b6 03             	movzbl (%ebx),%eax
  100272:	3c 0a                	cmp    $0xa,%al
  100274:	0f 94 c2             	sete   %dl
  100277:	3c 0d                	cmp    $0xd,%al
  100279:	0f 94 c1             	sete   %cl
  10027c:	08 ca                	or     %cl,%dl
  10027e:	75 e0                	jne    100260 <cnputs+0x40>
  cnbuffer[i] = cnentry(c, clr);
  100280:	8d 14 b6             	lea    (%esi,%esi,4),%edx
  return (unsigned short)uc | (unsigned short)color << 8;
  100283:	8b 4d e0             	mov    -0x20(%ebp),%ecx
  100286:	66 0b 45 e4          	or     -0x1c(%ebp),%ax
  cnbuffer[i] = cnentry(c, clr);
  10028a:	c1 e2 04             	shl    $0x4,%edx
  10028d:	01 fa                	add    %edi,%edx
  if (++cncolumn == VGA_WIDTH) {
  10028f:	83 c7 01             	add    $0x1,%edi
  return (unsigned short)uc | (unsigned short)color << 8;
  100292:	66 89 04 51          	mov    %ax,(%ecx,%edx,2)
  if (++cncolumn == VGA_WIDTH) {
  100296:	83 ff 50             	cmp    $0x50,%edi
  100299:	0f 84 81 00 00 00    	je     100320 <cnputs+0x100>
  } while(*str++);
  10029f:	0f b6 03             	movzbl (%ebx),%eax
  1002a2:	83 c3 01             	add    $0x1,%ebx
  1002a5:	84 c0                	test   %al,%al
  1002a7:	75 c6                	jne    10026f <cnputs+0x4f>
  1002a9:	80 7d e7 00          	cmpb   $0x0,-0x19(%ebp)
  1002ad:	89 3d 38 20 10 00    	mov    %edi,0x102038
  1002b3:	89 f1                	mov    %esi,%ecx
  1002b5:	0f 84 a8 00 00 00    	je     100363 <cnputs+0x143>
  1002bb:	89 35 3c 20 10 00    	mov    %esi,0x10203c
	iooutb(0x3D4, 0x0F);
  1002c1:	83 ec 08             	sub    $0x8,%esp
	unsigned short pos = y * VGA_WIDTH + x;
  1002c4:	8d 0c 89             	lea    (%ecx,%ecx,4),%ecx
	iooutb(0x3D4, 0x0F);
  1002c7:	6a 0f                	push   $0xf
	unsigned short pos = y * VGA_WIDTH + x;
  1002c9:	c1 e1 04             	shl    $0x4,%ecx
	iooutb(0x3D4, 0x0F);
  1002cc:	68 d4 03 00 00       	push   $0x3d4
	unsigned short pos = y * VGA_WIDTH + x;
  1002d1:	8d 1c 39             	lea    (%ecx,%edi,1),%ebx
	iooutb(0x3D4, 0x0F);
  1002d4:	e8 68 03 00 00       	call   100641 <iooutb>
	iooutb(0x3D5, (unsigned char) (pos & 0xFF));
  1002d9:	58                   	pop    %eax
  1002da:	0f b6 c3             	movzbl %bl,%eax
  1002dd:	5a                   	pop    %edx
  1002de:	50                   	push   %eax
	iooutb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
  1002df:	66 c1 eb 08          	shr    $0x8,%bx
	iooutb(0x3D5, (unsigned char) (pos & 0xFF));
  1002e3:	68 d5 03 00 00       	push   $0x3d5
  1002e8:	e8 54 03 00 00       	call   100641 <iooutb>
	iooutb(0x3D4, 0x0E);
  1002ed:	59                   	pop    %ecx
  1002ee:	5e                   	pop    %esi
  1002ef:	6a 0e                	push   $0xe
  1002f1:	68 d4 03 00 00       	push   $0x3d4
  1002f6:	e8 46 03 00 00       	call   100641 <iooutb>
	iooutb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
  1002fb:	5f                   	pop    %edi
  1002fc:	58                   	pop    %eax
  1002fd:	0f b7 c3             	movzwl %bx,%eax
  100300:	50                   	push   %eax
  100301:	68 d5 03 00 00       	push   $0x3d5
  100306:	e8 36 03 00 00       	call   100641 <iooutb>
}
  10030b:	8d 65 f4             	lea    -0xc(%ebp),%esp
  10030e:	31 c0                	xor    %eax,%eax
  100310:	5b                   	pop    %ebx
  100311:	5e                   	pop    %esi
  100312:	5f                   	pop    %edi
  100313:	5d                   	pop    %ebp
  100314:	c3                   	ret    
  100315:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10031c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    if (++cnrow == VGA_HEIGHT) {
  100320:	83 c6 01             	add    $0x1,%esi
  100323:	83 fe 19             	cmp    $0x19,%esi
  100326:	74 0e                	je     100336 <cnputs+0x116>
  } while(*str++);
  100328:	c6 45 e7 01          	movb   $0x1,-0x19(%ebp)
  10032c:	0f b6 03             	movzbl (%ebx),%eax
    cncolumn = 0;
  10032f:	31 ff                	xor    %edi,%edi
  100331:	e9 32 ff ff ff       	jmp    100268 <cnputs+0x48>
  100336:	b8 00 8f 0b 00       	mov    $0xb8f00,%eax
  10033b:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  10033f:	90                   	nop
		*ptr = 0;
  100340:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
  for(x = 0; x < VGA_WIDTH * 2; x++) {
  100346:	83 c0 01             	add    $0x1,%eax
  100349:	3d a0 8f 0b 00       	cmp    $0xb8fa0,%eax
  10034e:	75 f0                	jne    100340 <cnputs+0x120>
  } while(*str++);
  100350:	c6 45 e7 01          	movb   $0x1,-0x19(%ebp)
  100354:	0f b6 03             	movzbl (%ebx),%eax
    cncolumn = 0;
  100357:	31 ff                	xor    %edi,%edi
      cnrow = VGA_HEIGHT - 1;
  100359:	be 18 00 00 00       	mov    $0x18,%esi
  10035e:	e9 05 ff ff ff       	jmp    100268 <cnputs+0x48>
  } while(*str++);
  100363:	8b 4d dc             	mov    -0x24(%ebp),%ecx
  100366:	e9 56 ff ff ff       	jmp    1002c1 <cnputs+0xa1>
  10036b:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  10036f:	90                   	nop

00100370 <cnecolor>:
cnecolor(const enum vga_color fg, const enum vga_color bg) {
  100370:	55                   	push   %ebp
  100371:	89 e5                	mov    %esp,%ebp
  return fg | bg << 4;
  100373:	0f b6 45 0c          	movzbl 0xc(%ebp),%eax
  100377:	c1 e0 04             	shl    $0x4,%eax
  10037a:	0a 45 08             	or     0x8(%ebp),%al
}
  10037d:	5d                   	pop    %ebp
  10037e:	c3                   	ret    
  10037f:	90                   	nop

00100380 <cnentry>:
cnentry(const unsigned char uc, const unsigned char color) {
  100380:	55                   	push   %ebp
  100381:	89 e5                	mov    %esp,%ebp
  return (unsigned short)uc | (unsigned short)color << 8;
  100383:	0f b6 55 0c          	movzbl 0xc(%ebp),%edx
  100387:	0f b6 45 08          	movzbl 0x8(%ebp),%eax
}
  10038b:	5d                   	pop    %ebp
  return (unsigned short)uc | (unsigned short)color << 8;
  10038c:	c1 e2 08             	shl    $0x8,%edx
  10038f:	09 d0                	or     %edx,%eax
}
  100391:	c3                   	ret    
  100392:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  100399:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

001003a0 <cninit>:

cninit(unsigned char clr) {
  1003a0:	55                   	push   %ebp
  return (unsigned short)uc | (unsigned short)color << 8;
  1003a1:	ba a0 80 0b 00       	mov    $0xb80a0,%edx
cninit(unsigned char clr) {
  1003a6:	89 e5                	mov    %esp,%ebp
  1003a8:	83 ec 08             	sub    $0x8,%esp
  unsigned y, x;
  unsigned long long i;

  /* vga fb base addr */
  cnrow = 0; 
  1003ab:	c7 05 3c 20 10 00 00 	movl   $0x0,0x10203c
  1003b2:	00 00 00 
  cncolumn = 1;
  1003b5:	c7 05 38 20 10 00 01 	movl   $0x1,0x102038
  1003bc:	00 00 00 
cninit(unsigned char clr) {
  1003bf:	8b 45 08             	mov    0x8(%ebp),%eax
  cncolor = clr;
  cnbuffer = (unsigned short*)0xB8000;
  1003c2:	c7 05 30 20 10 00 00 	movl   $0xb8000,0x102030
  1003c9:	80 0b 00 
  cncolor = clr;
  1003cc:	a2 34 20 10 00       	mov    %al,0x102034
  return (unsigned short)uc | (unsigned short)color << 8;
  1003d1:	c1 e0 08             	shl    $0x8,%eax
  1003d4:	83 c8 20             	or     $0x20,%eax
  1003d7:	89 c1                	mov    %eax,%ecx
  1003d9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

  for (y = 0; y < VGA_HEIGHT ; y++) {
    for (x = 0; x < VGA_WIDTH; x++) {
  1003e0:	8d 82 60 ff ff ff    	lea    -0xa0(%edx),%eax
  1003e6:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1003ed:	8d 76 00             	lea    0x0(%esi),%esi
      i = y * VGA_WIDTH + x;
      cnbuffer[i] = cnentry(' ', cncolor);
  1003f0:	66 89 08             	mov    %cx,(%eax)
    for (x = 0; x < VGA_WIDTH; x++) {
  1003f3:	83 c0 02             	add    $0x2,%eax
  1003f6:	39 d0                	cmp    %edx,%eax
  1003f8:	75 f6                	jne    1003f0 <cninit+0x50>
  for (y = 0; y < VGA_HEIGHT ; y++) {
  1003fa:	8d 90 a0 00 00 00    	lea    0xa0(%eax),%edx
  100400:	3d a0 8f 0b 00       	cmp    $0xb8fa0,%eax
  100405:	75 d9                	jne    1003e0 <cninit+0x40>
    }
  }
  cncursoron(0, 15);
  100407:	83 ec 08             	sub    $0x8,%esp
  10040a:	6a 0f                	push   $0xf
  10040c:	6a 00                	push   $0x0
  10040e:	e8 b9 01 00 00       	call   1005cc <cncursoron>
	iooutb(0x3D4, 0x0F);
  100413:	58                   	pop    %eax
  100414:	5a                   	pop    %edx
  100415:	6a 0f                	push   $0xf
  100417:	68 d4 03 00 00       	push   $0x3d4
  10041c:	e8 20 02 00 00       	call   100641 <iooutb>
	iooutb(0x3D5, (unsigned char) (pos & 0xFF));
  100421:	59                   	pop    %ecx
  100422:	58                   	pop    %eax
  100423:	6a 00                	push   $0x0
  100425:	68 d5 03 00 00       	push   $0x3d5
  10042a:	e8 12 02 00 00       	call   100641 <iooutb>
	iooutb(0x3D4, 0x0E);
  10042f:	58                   	pop    %eax
  100430:	5a                   	pop    %edx
  100431:	6a 0e                	push   $0xe
  100433:	68 d4 03 00 00       	push   $0x3d4
  100438:	e8 04 02 00 00       	call   100641 <iooutb>
	iooutb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
  10043d:	59                   	pop    %ecx
  10043e:	58                   	pop    %eax
  10043f:	6a 00                	push   $0x0
  100441:	68 d5 03 00 00       	push   $0x3d5
  100446:	e8 f6 01 00 00       	call   100641 <iooutb>
  cnmovcur(0, 0);

  return 0;
  10044b:	31 c0                	xor    %eax,%eax
  10044d:	c9                   	leave  
  10044e:	c3                   	ret    
  10044f:	90                   	nop

00100450 <ttyputs>:
  } while (*str++);
  return 0;
}

ttyputs(const char str[])
{
  100450:	55                   	push   %ebp
  100451:	89 e5                	mov    %esp,%ebp
  100453:	53                   	push   %ebx
  100454:	83 ec 04             	sub    $0x4,%esp
  if (!_context.initialized)
  100457:	a1 40 20 10 00       	mov    0x102040,%eax
{
  10045c:	8b 5d 08             	mov    0x8(%ebp),%ebx
  if (!_context.initialized)
  10045f:	85 c0                	test   %eax,%eax
  100461:	74 60                	je     1004c3 <ttyputs+0x73>
    return -1;
  if (_context.broadcast)
  100463:	a1 44 20 10 00       	mov    0x102044,%eax
  100468:	85 c0                	test   %eax,%eax
  10046a:	75 14                	jne    100480 <ttyputs+0x30>
    cnputs(str);
  if (_context.side)
  10046c:	a1 48 20 10 00       	mov    0x102048,%eax
  100471:	85 c0                	test   %eax,%eax
  100473:	75 2b                	jne    1004a0 <ttyputs+0x50>
    sideputs(str);
  return 0;
  100475:	31 c0                	xor    %eax,%eax
}
  100477:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  10047a:	c9                   	leave  
  10047b:	c3                   	ret    
  10047c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    cnputs(str);
  100480:	83 ec 0c             	sub    $0xc,%esp
  100483:	53                   	push   %ebx
  100484:	e8 97 fd ff ff       	call   100220 <cnputs>
  if (_context.side)
  100489:	8b 0d 48 20 10 00    	mov    0x102048,%ecx
  10048f:	83 c4 10             	add    $0x10,%esp
  100492:	85 c9                	test   %ecx,%ecx
  100494:	74 df                	je     100475 <ttyputs+0x25>
  if (!_context.initialized)
  100496:	8b 15 40 20 10 00    	mov    0x102040,%edx
  10049c:	85 d2                	test   %edx,%edx
  10049e:	74 d5                	je     100475 <ttyputs+0x25>
    iooutb(PORT, *str);
  1004a0:	66 0f be 03          	movsbw (%ebx),%ax
  1004a4:	83 ec 08             	sub    $0x8,%esp
  } while (*str++);
  1004a7:	83 c3 01             	add    $0x1,%ebx
    iooutb(PORT, *str);
  1004aa:	0f b7 c0             	movzwl %ax,%eax
  1004ad:	50                   	push   %eax
  1004ae:	68 f8 03 00 00       	push   $0x3f8
  1004b3:	e8 89 01 00 00       	call   100641 <iooutb>
  } while (*str++);
  1004b8:	83 c4 10             	add    $0x10,%esp
  1004bb:	80 7b ff 00          	cmpb   $0x0,-0x1(%ebx)
  1004bf:	75 df                	jne    1004a0 <ttyputs+0x50>
  1004c1:	eb b2                	jmp    100475 <ttyputs+0x25>
    return -1;
  1004c3:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  1004c8:	eb ad                	jmp    100477 <ttyputs+0x27>
  1004ca:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

001004d0 <ttyup>:

ttyup(broadcast, side)
{
  if (!_context.initialized)
  1004d0:	a1 40 20 10 00       	mov    0x102040,%eax
  1004d5:	85 c0                	test   %eax,%eax
  1004d7:	74 17                	je     1004f0 <ttyup+0x20>
{
  1004d9:	55                   	push   %ebp
  1004da:	89 e5                	mov    %esp,%ebp
    return -1;
  _context.broadcast = broadcast;
  1004dc:	8b 45 08             	mov    0x8(%ebp),%eax
  1004df:	a3 44 20 10 00       	mov    %eax,0x102044
  _context.side = side;
  1004e4:	8b 45 0c             	mov    0xc(%ebp),%eax
  return 0;
}
  1004e7:	5d                   	pop    %ebp
  _context.side = side;
  1004e8:	a3 48 20 10 00       	mov    %eax,0x102048
  return 0;
  1004ed:	31 c0                	xor    %eax,%eax
}
  1004ef:	c3                   	ret    
    return -1;
  1004f0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
}
  1004f5:	c3                   	ret    
  1004f6:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1004fd:	8d 76 00             	lea    0x0(%esi),%esi

00100500 <ttyinit>:

ttyinit()
{
  100500:	55                   	push   %ebp
  100501:	89 e5                	mov    %esp,%ebp
  100503:	83 ec 10             	sub    $0x10,%esp
  _context.broadcast = 1;
  100506:	c7 05 44 20 10 00 01 	movl   $0x1,0x102044
  10050d:	00 00 00 
  _context.side = 1;

  cninit(cnecolor(LIGHT_GREEN, BLACK));
  100510:	6a 00                	push   $0x0
  100512:	6a 0a                	push   $0xa
  _context.side = 1;
  100514:	c7 05 48 20 10 00 01 	movl   $0x1,0x102048
  10051b:	00 00 00 
  cninit(cnecolor(LIGHT_GREEN, BLACK));
  10051e:	e8 4d fe ff ff       	call   100370 <cnecolor>
  100523:	0f b6 c0             	movzbl %al,%eax
  100526:	89 04 24             	mov    %eax,(%esp)
  100529:	e8 72 fe ff ff       	call   1003a0 <cninit>

  _context.initialized = 1;
  return 0;
  10052e:	31 c0                	xor    %eax,%eax
  _context.initialized = 1;
  100530:	c7 05 40 20 10 00 01 	movl   $0x1,0x102040
  100537:	00 00 00 
  10053a:	c9                   	leave  
  10053b:	c3                   	ret    

0010053c <multiboot_header>:
  10053c:	02 b0 ad 1b 00 00    	add    0x1bad(%eax),%dh
  100542:	00 00                	add    %al,(%eax)
  100544:	fe 4f 52             	decb   0x52(%edi)
  100547:	e4                   	.byte 0xe4

00100548 <_start>:
_start = entry

.globl entry
entry:
  # Turn on page size extension for 4Mbyte pages
  movl    %cr4, %eax
  100548:	0f 20 e0             	mov    %cr4,%eax
  orl     $(CR4_PSE), %eax
  10054b:	83 c8 10             	or     $0x10,%eax
  movl    %eax, %cr4
  10054e:	0f 22 e0             	mov    %eax,%cr4

  # Set up stacl
  movl $kernel_stack, %esp
  100551:	bc 4c 60 10 00       	mov    $0x10604c,%esp

  calll kmain
  100556:	e8 05 00 00 00       	call   100560 <kmain>

1:
  cli
  10055b:	fa                   	cli    
  hlt
  10055c:	f4                   	hlt    
  jmp 1b
  10055d:	eb fc                	jmp    10055b <_start+0x13>
  10055f:	90                   	nop

00100560 <kmain>:
#include <sys/defs.h>

int 
kmain() 
{
  100560:	55                   	push   %ebp
  100561:	89 e5                	mov    %esp,%ebp
  100563:	53                   	push   %ebx
  100564:	83 ec 04             	sub    $0x4,%esp
  /* stage 1 */
  cli();
  100567:	e8 31 02 00 00       	call   10079d <cli>
  ttyinit(1,1);
  10056c:	83 ec 08             	sub    $0x8,%esp
  10056f:	6a 01                	push   $0x1
  100571:	6a 01                	push   $0x1
  100573:	e8 88 ff ff ff       	call   100500 <ttyinit>
  announce();
  100578:	e8 73 fc ff ff       	call   1001f0 <announce>

  if (seginit() == -1) {
  10057d:	e8 fe fb ff ff       	call   100180 <seginit>
  100582:	83 c4 10             	add    $0x10,%esp
  100585:	83 f8 ff             	cmp    $0xffffffff,%eax
  100588:	74 19                	je     1005a3 <kmain+0x43>
    ttyputs("\nCouldn't initialize GDT");
    return -1;
  }
  ttyputs("\nInitialized GTD");
  10058a:	83 ec 0c             	sub    $0xc,%esp

  return 0;
  10058d:	31 db                	xor    %ebx,%ebx
  ttyputs("\nInitialized GTD");
  10058f:	68 d7 17 10 00       	push   $0x1017d7
  100594:	e8 b7 fe ff ff       	call   100450 <ttyputs>
  return 0;
  100599:	83 c4 10             	add    $0x10,%esp
  10059c:	89 d8                	mov    %ebx,%eax
  10059e:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  1005a1:	c9                   	leave  
  1005a2:	c3                   	ret    
    ttyputs("\nCouldn't initialize GDT");
  1005a3:	83 ec 0c             	sub    $0xc,%esp
  1005a6:	89 c3                	mov    %eax,%ebx
  1005a8:	68 be 17 10 00       	push   $0x1017be
  1005ad:	e8 9e fe ff ff       	call   100450 <ttyputs>
    return -1;
  1005b2:	83 c4 10             	add    $0x10,%esp
  1005b5:	eb e5                	jmp    10059c <kmain+0x3c>

001005b7 <cncursoroff>:
/ C prototype: void cncursoroff(void);
.globl cncursoroff
.type cncursoroff,@function

cncursoroff:
  pushf
  1005b7:	9c                   	pushf  
  pushl %eax
  1005b8:	50                   	push   %eax
  pushl %edx
  1005b9:	52                   	push   %edx
  movw $0x3D4, %dx
  1005ba:	66 ba d4 03          	mov    $0x3d4,%dx
  / low cursor shape register
  movb $0xA, %al
  1005be:	b0 0a                	mov    $0xa,%al
  outb %al, %dx
  1005c0:	ee                   	out    %al,(%dx)
  addw $1, %dx
  1005c1:	66 83 c2 01          	add    $0x1,%dx
  / bits 6-7 unused, bit 5 disables the cursor, bits 0-4 control the cursor shape
  movb $0x20, %al
  1005c5:	b0 20                	mov    $0x20,%al
  outb %al, %dx
  1005c7:	ee                   	out    %al,(%dx)
  popl %edx
  1005c8:	5a                   	pop    %edx
  popl %eax
  1005c9:	58                   	pop    %eax
  popf
  1005ca:	9d                   	popf   
  retl
  1005cb:	c3                   	ret    

001005cc <cncursoron>:
.type	cncursoron, @function

/ Enable the hardware cursor
/ C prototype: void cncursoron(unsigned char cursor_start, unsigned char cursor_end);
cncursoron:
	pushl	%ebp
  1005cc:	55                   	push   %ebp
	movl	%esp, %ebp
  1005cd:	89 e5                	mov    %esp,%ebp
	pushl	%esi
  1005cf:	56                   	push   %esi
	pushl	%ebx
  1005d0:	53                   	push   %ebx
	movl	8(%ebp), %esi
  1005d1:	8b 75 08             	mov    0x8(%ebp),%esi
	movl	12(%ebp), %ebx
  1005d4:	8b 5d 0c             	mov    0xc(%ebp),%ebx
	subl	$8, %esp
  1005d7:	83 ec 08             	sub    $0x8,%esp
	pushl	$10
  1005da:	6a 0a                	push   $0xa
	pushl	$980
  1005dc:	68 d4 03 00 00       	push   $0x3d4
	call	iooutb
  1005e1:	e8 5b 00 00 00       	call   100641 <iooutb>
	movl	$981, (%esp)
  1005e6:	c7 04 24 d5 03 00 00 	movl   $0x3d5,(%esp)
	call	ioinb
  1005ed:	e8 5a 00 00 00       	call   10064c <ioinb>
	popl	%edx
  1005f2:	5a                   	pop    %edx
	popl	%ecx
  1005f3:	59                   	pop    %ecx
	andl	$-64, %eax
  1005f4:	83 e0 c0             	and    $0xffffffc0,%eax
	orl	%esi, %eax
  1005f7:	09 f0                	or     %esi,%eax
	movzbl	%al, %eax
  1005f9:	0f b6 c0             	movzbl %al,%eax
	pushl	%eax
  1005fc:	50                   	push   %eax
	pushl	$981
  1005fd:	68 d5 03 00 00       	push   $0x3d5
	call	iooutb
  100602:	e8 3a 00 00 00       	call   100641 <iooutb>
	popl	%esi
  100607:	5e                   	pop    %esi
	popl	%eax
  100608:	58                   	pop    %eax
	pushl	$11
  100609:	6a 0b                	push   $0xb
	pushl	$980
  10060b:	68 d4 03 00 00       	push   $0x3d4
	call	iooutb
  100610:	e8 2c 00 00 00       	call   100641 <iooutb>
	movl	$981, (%esp)
  100615:	c7 04 24 d5 03 00 00 	movl   $0x3d5,(%esp)
	call	ioinb
  10061c:	e8 2b 00 00 00       	call   10064c <ioinb>
	movl	$981, 8(%ebp)
  100621:	c7 45 08 d5 03 00 00 	movl   $0x3d5,0x8(%ebp)
	addl	$16, %esp
  100628:	83 c4 10             	add    $0x10,%esp
	andl	$-32, %eax
  10062b:	83 e0 e0             	and    $0xffffffe0,%eax
	orl	%ebx, %eax
  10062e:	09 d8                	or     %ebx,%eax
	movzbl	%al, %eax
  100630:	0f b6 c0             	movzbl %al,%eax
	movl	%eax, 12(%ebp)
  100633:	89 45 0c             	mov    %eax,0xc(%ebp)
	leal	-8(%ebp), %esp
  100636:	8d 65 f8             	lea    -0x8(%ebp),%esp
	popl	%ebx
  100639:	5b                   	pop    %ebx
	popl	%esi
  10063a:	5e                   	pop    %esi
	popl	%ebp
  10063b:	5d                   	pop    %ebp
	jmp	iooutb
  10063c:	e9 00 00 00 00       	jmp    100641 <iooutb>

00100641 <iooutb>:
/ C prototype: void iooutb(unsigned short port, unsigned short data);
.globl iooutb
.type iooutb,@function

iooutb:
  movb  8(%esp), %al
  100641:	8a 44 24 08          	mov    0x8(%esp),%al
  movw  4(%esp), %dx
  100645:	66 8b 54 24 04       	mov    0x4(%esp),%dx
  outb  %al, %dx
  10064a:	ee                   	out    %al,(%dx)
  retl
  10064b:	c3                   	ret    

0010064c <ioinb>:
/ C prototype: unsigned char ioinb(unsigned short port);
.globl ioinb
.type ioinb,@function

ioinb:
  movw  4(%esp), %dx
  10064c:	66 8b 54 24 04       	mov    0x4(%esp),%dx
  inb   %dx, %al
  100651:	ec                   	in     (%dx),%al
  retl
  100652:	c3                   	ret    

00100653 <insl>:

.text
.globl	insl
.type	insl, @function
insl:
	pushl	%ebp
  100653:	55                   	push   %ebp
	movl	%esp, %ebp
  100654:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  100656:	57                   	push   %edi
	pushl	%ebx
  100657:	53                   	push   %ebx
	movl	8(%ebp), %edx
  100658:	8b 55 08             	mov    0x8(%ebp),%edx
	movl	12(%ebp), %ecx
  10065b:	8b 4d 0c             	mov    0xc(%ebp),%ecx
	movl	16(%ebp), %eax
  10065e:	8b 45 10             	mov    0x10(%ebp),%eax
	movl	%ecx, %ebx
  100661:	89 cb                	mov    %ecx,%ebx
	movl	%ebx, %edi
  100663:	89 df                	mov    %ebx,%edi
	movl	%eax, %ecx
  100665:	89 c1                	mov    %eax,%ecx

	cld; rep insl
  100667:	fc                   	cld    
  100668:	f3 6d                	rep insl (%dx),%es:(%edi)

	movl	%ecx, %eax
  10066a:	89 c8                	mov    %ecx,%eax
	movl	%edi, %ebx
  10066c:	89 fb                	mov    %edi,%ebx
	movl	%ebx, 12(%ebp)
  10066e:	89 5d 0c             	mov    %ebx,0xc(%ebp)
	movl	%eax, 16(%ebp)
  100671:	89 45 10             	mov    %eax,0x10(%ebp)
	nop
  100674:	90                   	nop
	popl	%ebx
  100675:	5b                   	pop    %ebx
	popl	%edi
  100676:	5f                   	pop    %edi
	popl	%ebp
  100677:	5d                   	pop    %ebp
	ret
  100678:	c3                   	ret    

00100679 <outw>:
	.size	insl, .-insl
	.globl	outw
	.type	outw, @function
outw:
	pushl	%ebp
  100679:	55                   	push   %ebp
	movl	%esp, %ebp
  10067a:	89 e5                	mov    %esp,%ebp
	subl	$8, %esp
  10067c:	83 ec 08             	sub    $0x8,%esp
	movl	8(%ebp), %edx
  10067f:	8b 55 08             	mov    0x8(%ebp),%edx
	movl	12(%ebp), %eax
  100682:	8b 45 0c             	mov    0xc(%ebp),%eax
	movw	%dx, -4(%ebp)
  100685:	66 89 55 fc          	mov    %dx,-0x4(%ebp)
	movw	%ax, -8(%ebp)
  100689:	66 89 45 f8          	mov    %ax,-0x8(%ebp)
	movzwl	-8(%ebp), %eax
  10068d:	0f b7 45 f8          	movzwl -0x8(%ebp),%eax
	movzwl	-4(%ebp), %edx
  100691:	0f b7 55 fc          	movzwl -0x4(%ebp),%edx

	out %ax,%dx
  100695:	66 ef                	out    %ax,(%dx)

	nop
  100697:	90                   	nop
	leave
  100698:	c9                   	leave  
	ret
  100699:	c3                   	ret    

0010069a <outsl>:
	.size	outw, .-outw
	.globl	outsl
	.type	outsl, @function
outsl:
	pushl	%ebp
  10069a:	55                   	push   %ebp
	movl	%esp, %ebp
  10069b:	89 e5                	mov    %esp,%ebp
	pushl	%esi
  10069d:	56                   	push   %esi
	pushl	%ebx
  10069e:	53                   	push   %ebx
	movl	8(%ebp), %edx
  10069f:	8b 55 08             	mov    0x8(%ebp),%edx
	movl	12(%ebp), %ecx
  1006a2:	8b 4d 0c             	mov    0xc(%ebp),%ecx
	movl	16(%ebp), %eax
  1006a5:	8b 45 10             	mov    0x10(%ebp),%eax
	movl	%ecx, %ebx
  1006a8:	89 cb                	mov    %ecx,%ebx
	movl	%ebx, %esi
  1006aa:	89 de                	mov    %ebx,%esi
	movl	%eax, %ecx
  1006ac:	89 c1                	mov    %eax,%ecx

	cld; rep outsl
  1006ae:	fc                   	cld    
  1006af:	f3 6f                	rep outsl %ds:(%esi),(%dx)

	movl	%ecx, %eax
  1006b1:	89 c8                	mov    %ecx,%eax
	movl	%esi, %ebx
  1006b3:	89 f3                	mov    %esi,%ebx
	movl	%ebx, 12(%ebp)
  1006b5:	89 5d 0c             	mov    %ebx,0xc(%ebp)
	movl	%eax, 16(%ebp)
  1006b8:	89 45 10             	mov    %eax,0x10(%ebp)
	nop
  1006bb:	90                   	nop
	popl	%ebx
  1006bc:	5b                   	pop    %ebx
	popl	%esi
  1006bd:	5e                   	pop    %esi
	popl	%ebp
  1006be:	5d                   	pop    %ebp
	ret
  1006bf:	c3                   	ret    

001006c0 <stosb>:
	.size	outsl, .-outsl
	.globl	stosb
	.type	stosb, @function
stosb:
	pushl	%ebp
  1006c0:	55                   	push   %ebp
	movl	%esp, %ebp
  1006c1:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  1006c3:	57                   	push   %edi
	pushl	%ebx
  1006c4:	53                   	push   %ebx
	movl	8(%ebp), %ecx
  1006c5:	8b 4d 08             	mov    0x8(%ebp),%ecx
	movl	16(%ebp), %edx
  1006c8:	8b 55 10             	mov    0x10(%ebp),%edx
	movl	12(%ebp), %eax
  1006cb:	8b 45 0c             	mov    0xc(%ebp),%eax
	movl	%ecx, %ebx
  1006ce:	89 cb                	mov    %ecx,%ebx
	movl	%ebx, %edi
  1006d0:	89 df                	mov    %ebx,%edi
	movl	%edx, %ecx
  1006d2:	89 d1                	mov    %edx,%ecx

	cld; rep stosb
  1006d4:	fc                   	cld    
  1006d5:	f3 aa                	rep stos %al,%es:(%edi)

	movl	%ecx, %edx
  1006d7:	89 ca                	mov    %ecx,%edx
	movl	%edi, %ebx
  1006d9:	89 fb                	mov    %edi,%ebx
	movl	%ebx, 8(%ebp)
  1006db:	89 5d 08             	mov    %ebx,0x8(%ebp)
	movl	%edx, 16(%ebp)
  1006de:	89 55 10             	mov    %edx,0x10(%ebp)
	nop
  1006e1:	90                   	nop
	popl	%ebx
  1006e2:	5b                   	pop    %ebx
	popl	%edi
  1006e3:	5f                   	pop    %edi
	popl	%ebp
  1006e4:	5d                   	pop    %ebp
	ret
  1006e5:	c3                   	ret    

001006e6 <stosl>:
	.size	stosb, .-stosb
	.globl	stosl
	.type	stosl, @function
stosl:
	pushl	%ebp
  1006e6:	55                   	push   %ebp
	movl	%esp, %ebp
  1006e7:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  1006e9:	57                   	push   %edi
	pushl	%ebx
  1006ea:	53                   	push   %ebx
	movl	8(%ebp), %ecx
  1006eb:	8b 4d 08             	mov    0x8(%ebp),%ecx
	movl	16(%ebp), %edx
  1006ee:	8b 55 10             	mov    0x10(%ebp),%edx
	movl	12(%ebp), %eax
  1006f1:	8b 45 0c             	mov    0xc(%ebp),%eax
	movl	%ecx, %ebx
  1006f4:	89 cb                	mov    %ecx,%ebx
	movl	%ebx, %edi
  1006f6:	89 df                	mov    %ebx,%edi
	movl	%edx, %ecx
  1006f8:	89 d1                	mov    %edx,%ecx

	cld; rep stosl
  1006fa:	fc                   	cld    
  1006fb:	f3 ab                	rep stos %eax,%es:(%edi)

	movl	%ecx, %edx
  1006fd:	89 ca                	mov    %ecx,%edx
	movl	%edi, %ebx
  1006ff:	89 fb                	mov    %edi,%ebx
	movl	%ebx, 8(%ebp)
  100701:	89 5d 08             	mov    %ebx,0x8(%ebp)
	movl	%edx, 16(%ebp)
  100704:	89 55 10             	mov    %edx,0x10(%ebp)
	nop
  100707:	90                   	nop
	popl	%ebx
  100708:	5b                   	pop    %ebx
	popl	%edi
  100709:	5f                   	pop    %edi
	popl	%ebp
  10070a:	5d                   	pop    %ebp
	ret
  10070b:	c3                   	ret    

0010070c <lgdt>:
	.size	stosl, .-stosl
	.globl	lgdt
	.type	lgdt, @function
lgdt:
	pushl	%ebp
  10070c:	55                   	push   %ebp
	movl	%esp, %ebp
  10070d:	89 e5                	mov    %esp,%ebp
	subl	$16, %esp
  10070f:	83 ec 10             	sub    $0x10,%esp
	movl	12(%ebp), %eax
  100712:	8b 45 0c             	mov    0xc(%ebp),%eax
	subl	$1, %eax
  100715:	83 e8 01             	sub    $0x1,%eax
	movw	%ax, -6(%ebp)
  100718:	66 89 45 fa          	mov    %ax,-0x6(%ebp)
	movl	8(%ebp), %eax
  10071c:	8b 45 08             	mov    0x8(%ebp),%eax
	movw	%ax, -4(%ebp)
  10071f:	66 89 45 fc          	mov    %ax,-0x4(%ebp)
	movl	8(%ebp), %eax
  100723:	8b 45 08             	mov    0x8(%ebp),%eax
	shrl	$16, %eax
  100726:	c1 e8 10             	shr    $0x10,%eax
	movw	%ax, -2(%ebp)
  100729:	66 89 45 fe          	mov    %ax,-0x2(%ebp)
	leal	-6(%ebp), %eax
  10072d:	8d 45 fa             	lea    -0x6(%ebp),%eax

	lgdt (%eax)
  100730:	0f 01 10             	lgdtl  (%eax)

	nop
  100733:	90                   	nop
	leave
  100734:	c9                   	leave  
	ret
  100735:	c3                   	ret    

00100736 <lidt>:
	.size	lgdt, .-lgdt
	.globl	lidt
	.type	lidt, @function
lidt:
	pushl	%ebp
  100736:	55                   	push   %ebp
	movl	%esp, %ebp
  100737:	89 e5                	mov    %esp,%ebp
	subl	$16, %esp
  100739:	83 ec 10             	sub    $0x10,%esp
	movl	12(%ebp), %eax
  10073c:	8b 45 0c             	mov    0xc(%ebp),%eax
	subl	$1, %eax
  10073f:	83 e8 01             	sub    $0x1,%eax
	movw	%ax, -6(%ebp)
  100742:	66 89 45 fa          	mov    %ax,-0x6(%ebp)
	movl	8(%ebp), %eax
  100746:	8b 45 08             	mov    0x8(%ebp),%eax
	movw	%ax, -4(%ebp)
  100749:	66 89 45 fc          	mov    %ax,-0x4(%ebp)
	movl	8(%ebp), %eax
  10074d:	8b 45 08             	mov    0x8(%ebp),%eax
	shrl	$16, %eax
  100750:	c1 e8 10             	shr    $0x10,%eax
	movw	%ax, -2(%ebp)
  100753:	66 89 45 fe          	mov    %ax,-0x2(%ebp)
	leal	-6(%ebp), %eax
  100757:	8d 45 fa             	lea    -0x6(%ebp),%eax

	lidt (%eax)
  10075a:	0f 01 18             	lidtl  (%eax)

	nop
  10075d:	90                   	nop
	leave
  10075e:	c9                   	leave  
	ret
  10075f:	c3                   	ret    

00100760 <ltr>:
	.size	lidt, .-lidt
	.globl	ltr
	.type	ltr, @function
ltr:
	pushl	%ebp
  100760:	55                   	push   %ebp
	movl	%esp, %ebp
  100761:	89 e5                	mov    %esp,%ebp
	subl	$4, %esp
  100763:	83 ec 04             	sub    $0x4,%esp
	movl	8(%ebp), %eax
  100766:	8b 45 08             	mov    0x8(%ebp),%eax
	movw	%ax, -4(%ebp)
  100769:	66 89 45 fc          	mov    %ax,-0x4(%ebp)
	movzwl	-4(%ebp), %eax
  10076d:	0f b7 45 fc          	movzwl -0x4(%ebp),%eax

	ltr %ax
  100771:	0f 00 d8             	ltr    %ax

	nop
  100774:	90                   	nop
	leave
  100775:	c9                   	leave  
	ret
  100776:	c3                   	ret    

00100777 <readeflags>:
	.size	ltr, .-ltr
	.globl	readeflags
	.type	readeflags, @function
readeflags:
	pushl	%ebp
  100777:	55                   	push   %ebp
	movl	%esp, %ebp
  100778:	89 e5                	mov    %esp,%ebp
	subl	$16, %esp
  10077a:	83 ec 10             	sub    $0x10,%esp

	pushfl; popl %eax
  10077d:	9c                   	pushf  
  10077e:	58                   	pop    %eax

	movl	%eax, -4(%ebp)
  10077f:	89 45 fc             	mov    %eax,-0x4(%ebp)
	movl	-4(%ebp), %eax
  100782:	8b 45 fc             	mov    -0x4(%ebp),%eax
	leave
  100785:	c9                   	leave  
	ret
  100786:	c3                   	ret    

00100787 <loadgs>:
	.size	readeflags, .-readeflags
	.globl	loadgs
	.type	loadgs, @function
loadgs:
	pushl	%ebp
  100787:	55                   	push   %ebp
	movl	%esp, %ebp
  100788:	89 e5                	mov    %esp,%ebp
	subl	$4, %esp
  10078a:	83 ec 04             	sub    $0x4,%esp
	movl	8(%ebp), %eax
  10078d:	8b 45 08             	mov    0x8(%ebp),%eax
	movw	%ax, -4(%ebp)
  100790:	66 89 45 fc          	mov    %ax,-0x4(%ebp)
	movzwl	-4(%ebp), %eax
  100794:	0f b7 45 fc          	movzwl -0x4(%ebp),%eax

	movw %ax, %gs
  100798:	8e e8                	mov    %eax,%gs

	nop
  10079a:	90                   	nop
	leave
  10079b:	c9                   	leave  
	ret
  10079c:	c3                   	ret    

0010079d <cli>:
	.size	loadgs, .-loadgs
	.globl	cli
	.type	cli, @function
cli:
	pushl	%ebp
  10079d:	55                   	push   %ebp
	movl	%esp, %ebp
  10079e:	89 e5                	mov    %esp,%ebp

	cli
  1007a0:	fa                   	cli    

	nop
  1007a1:	90                   	nop
	popl	%ebp
  1007a2:	5d                   	pop    %ebp
	ret
  1007a3:	c3                   	ret    

001007a4 <sti>:
	.size	cli, .-cli
	.globl	sti
	.type	sti, @function
sti:
	pushl	%ebp
  1007a4:	55                   	push   %ebp
	movl	%esp, %ebp
  1007a5:	89 e5                	mov    %esp,%ebp

	sti
  1007a7:	fb                   	sti    

	nop
  1007a8:	90                   	nop
	popl	%ebp
  1007a9:	5d                   	pop    %ebp
	ret
  1007aa:	c3                   	ret    

001007ab <xchg>:
	.size	sti, .-sti
	.globl	xchg
	.type	xchg, @function
xchg:
	pushl	%ebp
  1007ab:	55                   	push   %ebp
	movl	%esp, %ebp
  1007ac:	89 e5                	mov    %esp,%ebp
	subl	$16, %esp
  1007ae:	83 ec 10             	sub    $0x10,%esp
	movl	8(%ebp), %edx
  1007b1:	8b 55 08             	mov    0x8(%ebp),%edx
	movl	12(%ebp), %eax
  1007b4:	8b 45 0c             	mov    0xc(%ebp),%eax
	movl	8(%ebp), %ecx
  1007b7:	8b 4d 08             	mov    0x8(%ebp),%ecx

	lock; xchgl (%edx), %eax
  1007ba:	f0 87 02             	lock xchg %eax,(%edx)

	movl	%eax, -4(%ebp)
  1007bd:	89 45 fc             	mov    %eax,-0x4(%ebp)
	movl	-4(%ebp), %eax
  1007c0:	8b 45 fc             	mov    -0x4(%ebp),%eax
	leave
  1007c3:	c9                   	leave  
	ret
  1007c4:	c3                   	ret    

001007c5 <rcr2>:
	.size	xchg, .-xchg
	.globl	rcr2
	.type	rcr2, @function
rcr2:
	pushl	%ebp
  1007c5:	55                   	push   %ebp
	movl	%esp, %ebp
  1007c6:	89 e5                	mov    %esp,%ebp
	subl	$16, %esp
  1007c8:	83 ec 10             	sub    $0x10,%esp

	movl %cr2,%eax
  1007cb:	0f 20 d0             	mov    %cr2,%eax

	movl	%eax, -4(%ebp)
  1007ce:	89 45 fc             	mov    %eax,-0x4(%ebp)
	movl	-4(%ebp), %eax
  1007d1:	8b 45 fc             	mov    -0x4(%ebp),%eax
	leave
  1007d4:	c9                   	leave  
	ret
  1007d5:	c3                   	ret    

001007d6 <lcr3>:
	.size	rcr2, .-rcr2
	.globl	lcr3
	.type	lcr3, @function
lcr3:
	pushl	%ebp
  1007d6:	55                   	push   %ebp
	movl	%esp, %ebp
  1007d7:	89 e5                	mov    %esp,%ebp
	movl	8(%ebp), %eax
  1007d9:	8b 45 08             	mov    0x8(%ebp),%eax

	movl %eax,%cr3
  1007dc:	0f 22 d8             	mov    %eax,%cr3

	nop
  1007df:	90                   	nop
	popl	%ebp
  1007e0:	5d                   	pop    %ebp
	ret
  1007e1:	c3                   	ret    
  1007e2:	66 90                	xchg   %ax,%ax
  1007e4:	66 90                	xchg   %ax,%ax
  1007e6:	66 90                	xchg   %ax,%ax
  1007e8:	66 90                	xchg   %ax,%ax
  1007ea:	66 90                	xchg   %ax,%ax
  1007ec:	66 90                	xchg   %ax,%ax
  1007ee:	66 90                	xchg   %ax,%ax

001007f0 <strlen>:
.text
.align 16
.globl	strlen
.type	strlen, @function
strlen:
	pushl	%ebp
  1007f0:	55                   	push   %ebp
	xorl	%eax, %eax
  1007f1:	31 c0                	xor    %eax,%eax
	movl	%esp, %ebp
  1007f3:	89 e5                	mov    %esp,%ebp
	pushl	%ebx
  1007f5:	53                   	push   %ebx
	movl	8(%ebp), %ebx
  1007f6:	8b 5d 08             	mov    0x8(%ebp),%ebx
	cmpb	$0, (%ebx)
  1007f9:	80 3b 00             	cmpb   $0x0,(%ebx)
	je	.L1
  1007fc:	74 0e                	je     10080c <strlen+0x1c>
	xorl	%edx, %edx
  1007fe:	31 d2                	xor    %edx,%edx
	.align 16
.L3:
	addl	$1, %eax
  100800:	83 c0 01             	add    $0x1,%eax
	adcl	$0, %edx
  100803:	83 d2 00             	adc    $0x0,%edx
	cmpb	$0, (%ebx,%eax)
  100806:	80 3c 03 00          	cmpb   $0x0,(%ebx,%eax,1)
	jne	.L3
  10080a:	75 f4                	jne    100800 <strlen+0x10>
.L1:
	movl	-4(%ebp), %ebx
  10080c:	8b 5d fc             	mov    -0x4(%ebp),%ebx
	leave
  10080f:	c9                   	leave  
	ret
  100810:	c3                   	ret    
  100811:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  100818:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10081f:	90                   	nop

00100820 <memcmp>:
/ C: int memcmp(const void *s1, const void *s2, unsigned n);
.align 16
.globl	memcmp
.type	memcmp, @function
memcmp:
	pushl	%ebp
  100820:	55                   	push   %ebp
	xorl	%eax, %eax
  100821:	31 c0                	xor    %eax,%eax
	movl	%esp, %ebp
  100823:	89 e5                	mov    %esp,%ebp
	pushl	%esi
  100825:	56                   	push   %esi
	movl	16(%ebp), %esi
  100826:	8b 75 10             	mov    0x10(%ebp),%esi
	movl	8(%ebp), %edx
  100829:	8b 55 08             	mov    0x8(%ebp),%edx
	pushl	%ebx
  10082c:	53                   	push   %ebx
	movl	12(%ebp), %ecx
  10082d:	8b 4d 0c             	mov    0xc(%ebp),%ecx
	testl	%esi, %esi
  100830:	85 f6                	test   %esi,%esi
	je	.L8
  100832:	74 22                	je     100856 <memcmp+0x36>
	addl	%edx, %esi
  100834:	01 d6                	add    %edx,%esi
	jmp	.L11
  100836:	eb 0c                	jmp    100844 <memcmp+0x24>
  100838:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10083f:	90                   	nop
	.align 16
.L10:
	cmpl	%esi, %edx
  100840:	39 f2                	cmp    %esi,%edx
	je	.L16
  100842:	74 1c                	je     100860 <memcmp+0x40>
.L11:
	movzbl	(%edx), %eax
  100844:	0f b6 02             	movzbl (%edx),%eax
	movzbl	(%ecx), %ebx
  100847:	0f b6 19             	movzbl (%ecx),%ebx
	addl	$1, %edx
  10084a:	83 c2 01             	add    $0x1,%edx
	addl	$1, %ecx
  10084d:	83 c1 01             	add    $0x1,%ecx
	cmpb	%bl, %al
  100850:	38 d8                	cmp    %bl,%al
	je	.L10
  100852:	74 ec                	je     100840 <memcmp+0x20>
	subl	%ebx, %eax
  100854:	29 d8                	sub    %ebx,%eax
.L8:
	popl	%ebx
  100856:	5b                   	pop    %ebx
	popl	%esi
  100857:	5e                   	pop    %esi
	popl	%ebp
  100858:	5d                   	pop    %ebp
	ret
  100859:	c3                   	ret    
  10085a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	.align 16
.L16:
	popl	%ebx
  100860:	5b                   	pop    %ebx
	xorl	%eax, %eax
  100861:	31 c0                	xor    %eax,%eax
	popl	%esi
  100863:	5e                   	pop    %esi
	popl	%ebp
  100864:	5d                   	pop    %ebp
	ret
  100865:	c3                   	ret    

00100866 <memcpy>:
/ C: void * memcpy(void *dst0, const void *src0, unsigned int len)
.globl	memcpy
.type	memcpy, @function

memcpy:
	pushl	%ebp
  100866:	55                   	push   %ebp
	movl	%esp, %ebp
  100867:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  100869:	57                   	push   %edi
	pushl	%esi
  10086a:	56                   	push   %esi
	pushl	%ebx
  10086b:	53                   	push   %ebx
	subl	$4, %esp
  10086c:	83 ec 04             	sub    $0x4,%esp
	movl	12(%ebp), %eax
  10086f:	8b 45 0c             	mov    0xc(%ebp),%eax
	movl	16(%ebp), %edi
  100872:	8b 7d 10             	mov    0x10(%ebp),%edi
	testl	%edi, %edi
  100875:	85 ff                	test   %edi,%edi
	je	.L2
  100877:	0f 84 9d 00 00 00    	je     10091a <memcpy+0xb4>
	cmpl	%eax, 8(%ebp)
  10087d:	39 45 08             	cmp    %eax,0x8(%ebp)
	je	.L2
  100880:	0f 84 94 00 00 00    	je     10091a <memcpy+0xb4>
	movl	%eax, %ecx
  100886:	89 c1                	mov    %eax,%ecx
	cmpl	%eax, 8(%ebp)
  100888:	39 45 08             	cmp    %eax,0x8(%ebp)
	jnb	.L3
  10088b:	0f 83 a5 00 00 00    	jae    100936 <memcpy+0xd0>
	movl	%eax, %ebx
  100891:	89 c3                	mov    %eax,%ebx
	orl	8(%ebp), %ebx
  100893:	0b 5d 08             	or     0x8(%ebp),%ebx
	movl	8(%ebp), %edx
  100896:	8b 55 08             	mov    0x8(%ebp),%edx
	testb	$3, %bl
  100899:	f6 c3 03             	test   $0x3,%bl
	je	.L4
  10089c:	74 36                	je     1008d4 <memcpy+0x6e>
	movl	%eax, %edx
  10089e:	89 c2                	mov    %eax,%edx
	xorl	8(%ebp), %edx
  1008a0:	33 55 08             	xor    0x8(%ebp),%edx
	testb	$3, %dl
  1008a3:	f6 c2 03             	test   $0x3,%dl
	jne	.L17
  1008a6:	75 05                	jne    1008ad <memcpy+0x47>
	cmpl	$3, %edi
  1008a8:	83 ff 03             	cmp    $0x3,%edi
	ja	.L26
  1008ab:	77 78                	ja     100925 <memcpy+0xbf>
.L17:
	movl	%edi, %esi
  1008ad:	89 fe                	mov    %edi,%esi
.L5:
	subl	%esi, %edi
  1008af:	29 f7                	sub    %esi,%edi
	movl	%esi, %edx
  1008b1:	89 f2                	mov    %esi,%edx
	addl	8(%ebp), %edx
  1008b3:	03 55 08             	add    0x8(%ebp),%edx
	movl	%eax, %ebx
  1008b6:	89 c3                	mov    %eax,%ebx
	movl	8(%ebp), %ecx
  1008b8:	8b 4d 08             	mov    0x8(%ebp),%ecx
	movl	%eax, 12(%ebp)
  1008bb:	89 45 0c             	mov    %eax,0xc(%ebp)
.L6:
	addl	$1, %ebx
  1008be:	83 c3 01             	add    $0x1,%ebx
	addl	$1, %ecx
  1008c1:	83 c1 01             	add    $0x1,%ecx
	movzbl	-1(%ebx), %eax
  1008c4:	0f b6 43 ff          	movzbl -0x1(%ebx),%eax
	movb	%al, -1(%ecx)
  1008c8:	88 41 ff             	mov    %al,-0x1(%ecx)
	cmpl	%edx, %ecx
  1008cb:	39 d1                	cmp    %edx,%ecx
	jne	.L6
  1008cd:	75 ef                	jne    1008be <memcpy+0x58>
	movl	12(%ebp), %eax
  1008cf:	8b 45 0c             	mov    0xc(%ebp),%eax
	addl	%esi, %eax
  1008d2:	01 f0                	add    %esi,%eax
.L4:
	cmpl	$3, %edi
  1008d4:	83 ff 03             	cmp    $0x3,%edi
	jbe	.L7
  1008d7:	76 27                	jbe    100900 <memcpy+0x9a>
	movl	%edi, %esi
  1008d9:	89 fe                	mov    %edi,%esi
	shrl	$2, %esi
  1008db:	c1 ee 02             	shr    $0x2,%esi
	movl	%eax, %ebx
  1008de:	89 c3                	mov    %eax,%ebx
	movl	%edx, %ecx
  1008e0:	89 d1                	mov    %edx,%ecx
	movl	%eax, 12(%ebp)
  1008e2:	89 45 0c             	mov    %eax,0xc(%ebp)
.L8:
	movl	(%ebx), %eax
  1008e5:	8b 03                	mov    (%ebx),%eax
	movl	%eax, (%ecx)
  1008e7:	89 01                	mov    %eax,(%ecx)
	addl	$4, %ebx
  1008e9:	83 c3 04             	add    $0x4,%ebx
	addl	$4, %ecx
  1008ec:	83 c1 04             	add    $0x4,%ecx
	subl	$1, %esi
  1008ef:	83 ee 01             	sub    $0x1,%esi
	jne	.L8
  1008f2:	75 f1                	jne    1008e5 <memcpy+0x7f>
	movl	12(%ebp), %eax
  1008f4:	8b 45 0c             	mov    0xc(%ebp),%eax
	movl	%edi, %ecx
  1008f7:	89 f9                	mov    %edi,%ecx
	andl	$-4, %ecx
  1008f9:	83 e1 fc             	and    $0xfffffffc,%ecx
	addl	%ecx, %eax
  1008fc:	01 c8                	add    %ecx,%eax
	addl	%ecx, %edx
  1008fe:	01 ca                	add    %ecx,%edx
.L7:
	andl	$3, %edi
  100900:	83 e7 03             	and    $0x3,%edi
	movl	%edi, %ebx
  100903:	89 fb                	mov    %edi,%ebx
	je	.L2
  100905:	74 13                	je     10091a <memcpy+0xb4>
	addl	%edx, %ebx
  100907:	01 d3                	add    %edx,%ebx
.L9:
	addl	$1, %eax
  100909:	83 c0 01             	add    $0x1,%eax
	addl	$1, %edx
  10090c:	83 c2 01             	add    $0x1,%edx
	movzbl	-1(%eax), %ecx
  10090f:	0f b6 48 ff          	movzbl -0x1(%eax),%ecx
	movb	%cl, -1(%edx)
  100913:	88 4a ff             	mov    %cl,-0x1(%edx)
	cmpl	%ebx, %edx
  100916:	39 da                	cmp    %ebx,%edx
	jne	.L9
  100918:	75 ef                	jne    100909 <memcpy+0xa3>
.L2:
	movl	8(%ebp), %eax
  10091a:	8b 45 08             	mov    0x8(%ebp),%eax
	addl	$4, %esp
  10091d:	83 c4 04             	add    $0x4,%esp
	popl	%ebx
  100920:	5b                   	pop    %ebx
	popl	%esi
  100921:	5e                   	pop    %esi
	popl	%edi
  100922:	5f                   	pop    %edi
	popl	%ebp
  100923:	5d                   	pop    %ebp
	ret
  100924:	c3                   	ret    
.L26:
	andl	$3, %ecx
  100925:	83 e1 03             	and    $0x3,%ecx
	movl	$4, %edx
  100928:	ba 04 00 00 00       	mov    $0x4,%edx
	movl	%edx, %esi
  10092d:	89 d6                	mov    %edx,%esi
	subl	%ecx, %esi
  10092f:	29 ce                	sub    %ecx,%esi
	jmp	.L5
  100931:	e9 79 ff ff ff       	jmp    1008af <memcpy+0x49>
.L3:
	addl	%edi, %eax
  100936:	01 f8                	add    %edi,%eax
	movl	%edi, %ecx
  100938:	89 f9                	mov    %edi,%ecx
	addl	8(%ebp), %ecx
  10093a:	03 4d 08             	add    0x8(%ebp),%ecx
	movl	%eax, %ebx
  10093d:	89 c3                	mov    %eax,%ebx
	movl	%ecx, %edx
  10093f:	89 ca                	mov    %ecx,%edx
	orl	%eax, %edx
  100941:	09 c2                	or     %eax,%edx
	testb	$3, %dl
  100943:	f6 c2 03             	test   $0x3,%dl
	je	.L10
  100946:	74 35                	je     10097d <memcpy+0x117>
	movl	%ecx, %edx
  100948:	89 ca                	mov    %ecx,%edx
	xorl	%eax, %edx
  10094a:	31 c2                	xor    %eax,%edx
	testb	$3, %dl
  10094c:	f6 c2 03             	test   $0x3,%dl
	jne	.L18
  10094f:	75 08                	jne    100959 <memcpy+0xf3>
	andl	$3, %ebx
  100951:	83 e3 03             	and    $0x3,%ebx
	cmpl	$4, %edi
  100954:	83 ff 04             	cmp    $0x4,%edi
	ja	.L11
  100957:	77 02                	ja     10095b <memcpy+0xf5>
.L18:
	movl	%edi, %ebx
  100959:	89 fb                	mov    %edi,%ebx
.L11:
	subl	%ebx, %edi
  10095b:	29 df                	sub    %ebx,%edi
	movl	%ebx, %edx
  10095d:	89 da                	mov    %ebx,%edx
	movl	%ebx, %esi
  10095f:	89 de                	mov    %ebx,%esi
	negl	%esi
  100961:	f7 de                	neg    %esi
	subl	%ebx, %eax
  100963:	29 d8                	sub    %ebx,%eax
	movl	%ecx, -16(%ebp)
  100965:	89 4d f0             	mov    %ecx,-0x10(%ebp)
.L12:
	movl	-16(%ebp), %ebx
  100968:	8b 5d f0             	mov    -0x10(%ebp),%ebx
	addl	%esi, %ebx
  10096b:	01 f3                	add    %esi,%ebx
	movzbl	-1(%eax,%edx), %ecx
  10096d:	0f b6 4c 10 ff       	movzbl -0x1(%eax,%edx,1),%ecx
	movb	%cl, -1(%ebx,%edx)
  100972:	88 4c 13 ff          	mov    %cl,-0x1(%ebx,%edx,1)
	subl	$1, %edx
  100976:	83 ea 01             	sub    $0x1,%edx
	jne	.L12
  100979:	75 ed                	jne    100968 <memcpy+0x102>
	movl	%ebx, %ecx
  10097b:	89 d9                	mov    %ebx,%ecx
.L10:
	cmpl	$3, %edi
  10097d:	83 ff 03             	cmp    $0x3,%edi
	jbe	.L13
  100980:	76 1b                	jbe    10099d <memcpy+0x137>
	movl	%edi, %edx
  100982:	89 fa                	mov    %edi,%edx
	shrl	$2, %edx
  100984:	c1 ea 02             	shr    $0x2,%edx
	movl	%edi, %ebx
  100987:	89 fb                	mov    %edi,%ebx
	andl	$-4, %ebx
  100989:	83 e3 fc             	and    $0xfffffffc,%ebx
	subl	%ebx, %eax
  10098c:	29 d8                	sub    %ebx,%eax
	subl	%ebx, %ecx
  10098e:	29 d9                	sub    %ebx,%ecx
.L14:
	movl	-4(%eax,%edx,4), %ebx
  100990:	8b 5c 90 fc          	mov    -0x4(%eax,%edx,4),%ebx
	movl	%ebx, -4(%ecx,%edx,4)
  100994:	89 5c 91 fc          	mov    %ebx,-0x4(%ecx,%edx,4)
	subl	$1, %edx
  100998:	83 ea 01             	sub    $0x1,%edx
	jne	.L14
  10099b:	75 f3                	jne    100990 <memcpy+0x12a>
.L13:
	andl	$3, %edi
  10099d:	83 e7 03             	and    $0x3,%edi
	je	.L2
  1009a0:	0f 84 74 ff ff ff    	je     10091a <memcpy+0xb4>
	movl	%edi, %edx
  1009a6:	89 fa                	mov    %edi,%edx
	movl	%edi, %ebx
  1009a8:	89 fb                	mov    %edi,%ebx
	negl	%ebx
  1009aa:	f7 db                	neg    %ebx
	subl	%edi, %eax
  1009ac:	29 f8                	sub    %edi,%eax
	movl	%ecx, %edi
  1009ae:	89 cf                	mov    %ecx,%edi
.L15:
	leal	(%edi,%ebx), %esi
  1009b0:	8d 34 1f             	lea    (%edi,%ebx,1),%esi
	movzbl	-1(%eax,%edx), %ecx
  1009b3:	0f b6 4c 10 ff       	movzbl -0x1(%eax,%edx,1),%ecx
	movb	%cl, -1(%esi,%edx)
  1009b8:	88 4c 16 ff          	mov    %cl,-0x1(%esi,%edx,1)
	subl	$1, %edx
  1009bc:	83 ea 01             	sub    $0x1,%edx
	jne	.L15
  1009bf:	75 ef                	jne    1009b0 <memcpy+0x14a>
	jmp	.L2
  1009c1:	e9 54 ff ff ff       	jmp    10091a <memcpy+0xb4>

001009c6 <memmove>:

/ C: void * memmove(void *s1, const void *s2, unsigned int n)
.globl	memmove
.type	memmove, @function
memmove:
	pushl	%ebp
  1009c6:	55                   	push   %ebp
	movl	%esp, %ebp
  1009c7:	89 e5                	mov    %esp,%ebp
	subl	$12, %esp
  1009c9:	83 ec 0c             	sub    $0xc,%esp
	pushl	16(%ebp)
  1009cc:	ff 75 10             	push   0x10(%ebp)
	pushl	12(%ebp)
  1009cf:	ff 75 0c             	push   0xc(%ebp)
	pushl	8(%ebp)
  1009d2:	ff 75 08             	push   0x8(%ebp)
	call	memcpy
  1009d5:	e8 8c fe ff ff       	call   100866 <memcpy>
	leave
  1009da:	c9                   	leave  
	ret
  1009db:	c3                   	ret    

001009dc <bcopy>:

/ C: void bcopy(const void *s1, void *s2, unsigned int n)
.globl	bcopy
.type	bcopy, @function
bcopy:
	pushl	%ebp
  1009dc:	55                   	push   %ebp
	movl	%esp, %ebp
  1009dd:	89 e5                	mov    %esp,%ebp
	subl	$12, %esp
  1009df:	83 ec 0c             	sub    $0xc,%esp
	pushl	16(%ebp)
  1009e2:	ff 75 10             	push   0x10(%ebp)
	pushl	8(%ebp)
  1009e5:	ff 75 08             	push   0x8(%ebp)
	pushl	12(%ebp)
  1009e8:	ff 75 0c             	push   0xc(%ebp)
	call	memcpy
  1009eb:	e8 76 fe ff ff       	call   100866 <memcpy>
	addl	$16, %esp
  1009f0:	83 c4 10             	add    $0x10,%esp
	leave
  1009f3:	c9                   	leave  
	ret
  1009f4:	c3                   	ret    

001009f5 <strcpy>:

/ C: char * strcpy(char * restrict dst, const char * restrict src)
.globl	strcpy
.type	strcpy, @function
strcpy:
	pushl	%ebp
  1009f5:	55                   	push   %ebp
	movl	%esp, %ebp
  1009f6:	89 e5                	mov    %esp,%ebp
	pushl	%esi
  1009f8:	56                   	push   %esi
	pushl	%ebx
  1009f9:	53                   	push   %ebx
	movl	8(%ebp), %ebx
  1009fa:	8b 5d 08             	mov    0x8(%ebp),%ebx
	movl	12(%ebp), %esi
  1009fd:	8b 75 0c             	mov    0xc(%ebp),%esi
	subl	$12, %esp
  100a00:	83 ec 0c             	sub    $0xc,%esp
	pushl	%esi
  100a03:	56                   	push   %esi
	call	strlen
  100a04:	e8 e7 fd ff ff       	call   1007f0 <strlen>
	addl	$12, %esp
  100a09:	83 c4 0c             	add    $0xc,%esp
	addl	$1, %eax
  100a0c:	83 c0 01             	add    $0x1,%eax
	pushl	%eax
  100a0f:	50                   	push   %eax
	pushl	%esi
  100a10:	56                   	push   %esi
	pushl	%ebx
  100a11:	53                   	push   %ebx
	call	memcpy
  100a12:	e8 4f fe ff ff       	call   100866 <memcpy>
	movl	%ebx, %eax
  100a17:	89 d8                	mov    %ebx,%eax
	leal	-8(%ebp), %esp
  100a19:	8d 65 f8             	lea    -0x8(%ebp),%esp
	popl	%ebx
  100a1c:	5b                   	pop    %ebx
	popl	%esi
  100a1d:	5e                   	pop    %esi
	popl	%ebp
  100a1e:	5d                   	pop    %ebp
	ret
  100a1f:	c3                   	ret    

00100a20 <strcat>:
.text
.globl	strcat
.type	strcat, @function

strcat:
	pushl	%ebp
  100a20:	55                   	push   %ebp
	movl	%esp, %ebp
  100a21:	89 e5                	mov    %esp,%ebp
	pushl	%ebx
  100a23:	53                   	push   %ebx
	subl	$16, %esp
  100a24:	83 ec 10             	sub    $0x10,%esp
	movl	8(%ebp), %ebx
  100a27:	8b 5d 08             	mov    0x8(%ebp),%ebx
	pushl	%ebx
  100a2a:	53                   	push   %ebx
	call	strlen
  100a2b:	e8 c0 fd ff ff       	call   1007f0 <strlen>
	addl	$8, %esp
  100a30:	83 c4 08             	add    $0x8,%esp
	pushl	12(%ebp)
  100a33:	ff 75 0c             	push   0xc(%ebp)
	addl	%ebx, %eax
  100a36:	01 d8                	add    %ebx,%eax
	pushl	%eax
  100a38:	50                   	push   %eax
	call	strcpy
  100a39:	e8 b7 ff ff ff       	call   1009f5 <strcpy>
	movl	%ebx, %eax
  100a3e:	89 d8                	mov    %ebx,%eax
	movl	-4(%ebp), %ebx
  100a40:	8b 5d fc             	mov    -0x4(%ebp),%ebx
	leave
  100a43:	c9                   	leave  
	ret
  100a44:	c3                   	ret    

00100a45 <strnlen>:
/ C: unsigned int strnlen(const char *str, unsigned int maxlen);
.globl	strnlen
.type	strnlen, @function

strnlen:
	pushl	%ebp
  100a45:	55                   	push   %ebp
	movl	%esp, %ebp
  100a46:	89 e5                	mov    %esp,%ebp
	pushl	%esi
  100a48:	56                   	push   %esi
	pushl	%ebx
  100a49:	53                   	push   %ebx
	movl	8(%ebp), %esi
  100a4a:	8b 75 08             	mov    0x8(%ebp),%esi
	movl	12(%ebp), %ecx
  100a4d:	8b 4d 0c             	mov    0xc(%ebp),%ecx
	movl	%ecx, %eax
  100a50:	89 c8                	mov    %ecx,%eax
	testl	%ecx, %ecx
  100a52:	85 c9                	test   %ecx,%ecx
	je	.L3
  100a54:	74 79                	je     100acf <strnlen+0x8a>
	addl	%esi, %ecx
  100a56:	01 f1                	add    %esi,%ecx
	testl	$3, %esi
  100a58:	f7 c6 03 00 00 00    	test   $0x3,%esi
	je	.L14
  100a5e:	74 1f                	je     100a7f <strnlen+0x3a>
	movl	%esi, %eax
  100a60:	89 f0                	mov    %esi,%eax
.L7:
	cmpb	$0, (%eax)
  100a62:	80 38 00             	cmpb   $0x0,(%eax)
	je	.L19
  100a65:	74 0f                	je     100a76 <strnlen+0x31>
	addl	$1, %eax
  100a67:	83 c0 01             	add    $0x1,%eax
	testb	$3, %al
  100a6a:	a8 03                	test   $0x3,%al
	jne	.L7
  100a6c:	75 f4                	jne    100a62 <strnlen+0x1d>
.L5:
	cmpl	%eax, %ecx
  100a6e:	39 c1                	cmp    %eax,%ecx
	ja	.L12
  100a70:	77 1f                	ja     100a91 <strnlen+0x4c>
	movl	%eax, %ebx
  100a72:	89 c3                	mov    %eax,%ebx
	jmp	.L8
  100a74:	eb 50                	jmp    100ac6 <strnlen+0x81>
.L19:
	cmpl	%eax, %ecx
  100a76:	39 c1                	cmp    %eax,%ecx
	cmovbe	%ecx, %eax
  100a78:	0f 46 c1             	cmovbe %ecx,%eax
	subl	%esi, %eax
  100a7b:	29 f0                	sub    %esi,%eax
	jmp	.L3
  100a7d:	eb 50                	jmp    100acf <strnlen+0x8a>
.L14:
	movl	%esi, %eax
  100a7f:	89 f0                	mov    %esi,%eax
	jmp	.L5
  100a81:	eb eb                	jmp    100a6e <strnlen+0x29>
.L21:
	leal	-3(%eax), %ebx
  100a83:	8d 58 fd             	lea    -0x3(%eax),%ebx
	jmp	.L8
  100a86:	eb 3e                	jmp    100ac6 <strnlen+0x81>
.L22:
	leal	-2(%eax), %ebx
  100a88:	8d 58 fe             	lea    -0x2(%eax),%ebx
	jmp	.L8
  100a8b:	eb 39                	jmp    100ac6 <strnlen+0x81>
.L9:
	cmpl	%eax, %ecx
  100a8d:	39 c1                	cmp    %eax,%ecx
	jbe	.L20
  100a8f:	76 33                	jbe    100ac4 <strnlen+0x7f>
.L12:
	movl	%eax, %ebx
  100a91:	89 c3                	mov    %eax,%ebx
	addl	$4, %eax
  100a93:	83 c0 04             	add    $0x4,%eax
	movl	-4(%eax), %edx
  100a96:	8b 50 fc             	mov    -0x4(%eax),%edx
	subl	$16843009, %edx
  100a99:	81 ea 01 01 01 01    	sub    $0x1010101,%edx
	testl	$-2139062144, %edx
  100a9f:	f7 c2 80 80 80 80    	test   $0x80808080,%edx
	je	.L9
  100aa5:	74 e6                	je     100a8d <strnlen+0x48>
	cmpb	$0, -4(%eax)
  100aa7:	80 78 fc 00          	cmpb   $0x0,-0x4(%eax)
	je	.L8
  100aab:	74 19                	je     100ac6 <strnlen+0x81>
	cmpb	$0, -3(%eax)
  100aad:	80 78 fd 00          	cmpb   $0x0,-0x3(%eax)
	je	.L21
  100ab1:	74 d0                	je     100a83 <strnlen+0x3e>
	cmpb	$0, -2(%eax)
  100ab3:	80 78 fe 00          	cmpb   $0x0,-0x2(%eax)
	je	.L22
  100ab7:	74 cf                	je     100a88 <strnlen+0x43>
	cmpb	$0, -1(%eax)
  100ab9:	80 78 ff 00          	cmpb   $0x0,-0x1(%eax)
	jne	.L9
  100abd:	75 ce                	jne    100a8d <strnlen+0x48>
	leal	-1(%eax), %ebx
  100abf:	8d 58 ff             	lea    -0x1(%eax),%ebx
	jmp	.L8
  100ac2:	eb 02                	jmp    100ac6 <strnlen+0x81>
.L20:
	movl	%ecx, %ebx
  100ac4:	89 cb                	mov    %ecx,%ebx
.L8:
	cmpl	%ecx, %ebx
  100ac6:	39 cb                	cmp    %ecx,%ebx
	movl	%ecx, %eax
  100ac8:	89 c8                	mov    %ecx,%eax
	cmovbe	%ebx, %eax
  100aca:	0f 46 c3             	cmovbe %ebx,%eax
	subl	%esi, %eax
  100acd:	29 f0                	sub    %esi,%eax
.L3:
	popl	%ebx
  100acf:	5b                   	pop    %ebx
	popl	%esi
  100ad0:	5e                   	pop    %esi
	popl	%ebp
  100ad1:	5d                   	pop    %ebp
	ret
  100ad2:	c3                   	ret    

00100ad3 <strncat>:
/ C: char *strncat(char *s1, const char *s2, unsigned int n);
.globl	strncat
.type	strncat, @function

strncat:
	pushl	%ebp
  100ad3:	55                   	push   %ebp
	movl	%esp, %ebp
  100ad4:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  100ad6:	57                   	push   %edi
	pushl	%esi
  100ad7:	56                   	push   %esi
	pushl	%ebx
  100ad8:	53                   	push   %ebx
	subl	$24, %esp
  100ad9:	83 ec 18             	sub    $0x18,%esp
	movl	8(%ebp), %esi
  100adc:	8b 75 08             	mov    0x8(%ebp),%esi
	movl	12(%ebp), %edi
  100adf:	8b 7d 0c             	mov    0xc(%ebp),%edi
	pushl	%esi
  100ae2:	56                   	push   %esi
	call	strlen
  100ae3:	e8 08 fd ff ff       	call   1007f0 <strlen>
	addl	$8, %esp
  100ae8:	83 c4 08             	add    $0x8,%esp
	leal	(%esi,%eax), %ebx
  100aeb:	8d 1c 06             	lea    (%esi,%eax,1),%ebx
	pushl	16(%ebp)
  100aee:	ff 75 10             	push   0x10(%ebp)
	pushl	%edi
  100af1:	57                   	push   %edi
	call	strnlen
  100af2:	e8 4e ff ff ff       	call   100a45 <strnlen>
	addl	$12, %esp
  100af7:	83 c4 0c             	add    $0xc,%esp
	movb	$0, (%ebx,%eax)
  100afa:	c6 04 03 00          	movb   $0x0,(%ebx,%eax,1)
	pushl	%eax
  100afe:	50                   	push   %eax
	pushl	%edi
  100aff:	57                   	push   %edi
	pushl	%ebx
  100b00:	53                   	push   %ebx
	call	memcpy
  100b01:	e8 60 fd ff ff       	call   100866 <memcpy>
	movl	%esi, %eax
  100b06:	89 f0                	mov    %esi,%eax
	leal	-12(%ebp), %esp
  100b08:	8d 65 f4             	lea    -0xc(%ebp),%esp
	popl	%ebx
  100b0b:	5b                   	pop    %ebx
	popl	%esi
  100b0c:	5e                   	pop    %esi
	popl	%edi
  100b0d:	5f                   	pop    %edi
	popl	%ebp
  100b0e:	5d                   	pop    %ebp
	ret
  100b0f:	c3                   	ret    

00100b10 <strcmp>:
	.align 16
	.globl	strcmp
	.type	strcmp, @function

strcmp:
	pushl	%ebp
  100b10:	55                   	push   %ebp
	xorl	%eax, %eax
  100b11:	31 c0                	xor    %eax,%eax
	movl	%esp, %ebp
  100b13:	89 e5                	mov    %esp,%ebp
	pushl	%esi
  100b15:	56                   	push   %esi
	movl	8(%ebp), %esi
  100b16:	8b 75 08             	mov    0x8(%ebp),%esi
	pushl	%ebx
  100b19:	53                   	push   %ebx
	movl	12(%ebp), %ebx
  100b1a:	8b 5d 0c             	mov    0xc(%ebp),%ebx
	jmp	.L4
  100b1d:	eb 08                	jmp    100b27 <strcmp+0x17>
  100b1f:	90                   	nop
	.align 16
.L2:
	addl	$1, %eax
  100b20:	83 c0 01             	add    $0x1,%eax
	cmpb	%cl, %dl
  100b23:	38 ca                	cmp    %cl,%dl
	jne	.L8
  100b25:	75 19                	jne    100b40 <strcmp+0x30>
.L4:
	movzbl	(%esi,%eax), %edx
  100b27:	0f b6 14 06          	movzbl (%esi,%eax,1),%edx
	movzbl	(%ebx,%eax), %ecx
  100b2b:	0f b6 0c 03          	movzbl (%ebx,%eax,1),%ecx
	testb	%dl, %dl
  100b2f:	84 d2                	test   %dl,%dl
	jne	.L2
  100b31:	75 ed                	jne    100b20 <strcmp+0x10>
	movzbl	%cl, %eax
  100b33:	0f b6 c1             	movzbl %cl,%eax
	popl	%ebx
  100b36:	5b                   	pop    %ebx
	popl	%esi
  100b37:	5e                   	pop    %esi
	negl	%eax
  100b38:	f7 d8                	neg    %eax
	popl	%ebp
  100b3a:	5d                   	pop    %ebp
	ret
  100b3b:	c3                   	ret    
  100b3c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L8:
	movzbl	%dl, %eax
  100b40:	0f b6 c2             	movzbl %dl,%eax
	popl	%ebx
  100b43:	5b                   	pop    %ebx
	popl	%esi
  100b44:	5e                   	pop    %esi
	subl	%ecx, %eax
  100b45:	29 c8                	sub    %ecx,%eax
	popl	%ebp
  100b47:	5d                   	pop    %ebp
	ret
  100b48:	c3                   	ret    
  100b49:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00100b50 <strncmp>:
.align 16
.globl	strncmp
.type	strncmp, @function

strncmp:
	pushl	%ebp
  100b50:	55                   	push   %ebp
	movl	%esp, %ebp
  100b51:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  100b53:	57                   	push   %edi
	movl	16(%ebp), %edi
  100b54:	8b 7d 10             	mov    0x10(%ebp),%edi
	movl	8(%ebp), %edx
  100b57:	8b 55 08             	mov    0x8(%ebp),%edx
	pushl	%esi
  100b5a:	56                   	push   %esi
	movl	12(%ebp), %ecx
  100b5b:	8b 4d 0c             	mov    0xc(%ebp),%ecx
	pushl	%ebx
  100b5e:	53                   	push   %ebx
	cmpl	$3, %edi
  100b5f:	83 ff 03             	cmp    $0x3,%edi
	jbe	.L25
  100b62:	76 5c                	jbe    100bc0 <strncmp+0x70>
	movl	%edi, %esi
  100b64:	89 fe                	mov    %edi,%esi
	andl	$-4, %esi
  100b66:	83 e6 fc             	and    $0xfffffffc,%esi
	addl	%edx, %esi
  100b69:	01 d6                	add    %edx,%esi
  100b6b:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  100b6f:	90                   	nop
	.align 16
.L20:
	movzbl	(%edx), %eax
  100b70:	0f b6 02             	movzbl (%edx),%eax
	movzbl	(%ecx), %ebx
  100b73:	0f b6 19             	movzbl (%ecx),%ebx
	testb	%al, %al
  100b76:	84 c0                	test   %al,%al
	je	.L21
  100b78:	74 7e                	je     100bf8 <strncmp+0xa8>
	cmpb	%bl, %al
  100b7a:	38 d8                	cmp    %bl,%al
	jne	.L21
  100b7c:	75 7a                	jne    100bf8 <strncmp+0xa8>
	movzbl	1(%edx), %eax
  100b7e:	0f b6 42 01          	movzbl 0x1(%edx),%eax
	movzbl	1(%ecx), %ebx
  100b82:	0f b6 59 01          	movzbl 0x1(%ecx),%ebx
	testb	%al, %al
  100b86:	84 c0                	test   %al,%al
	je	.L21
  100b88:	74 6e                	je     100bf8 <strncmp+0xa8>
	cmpb	%bl, %al
  100b8a:	38 d8                	cmp    %bl,%al
	jne	.L21
  100b8c:	75 6a                	jne    100bf8 <strncmp+0xa8>
	movzbl	2(%edx), %eax
  100b8e:	0f b6 42 02          	movzbl 0x2(%edx),%eax
	movzbl	2(%ecx), %ebx
  100b92:	0f b6 59 02          	movzbl 0x2(%ecx),%ebx
	testb	%al, %al
  100b96:	84 c0                	test   %al,%al
	je	.L21
  100b98:	74 5e                	je     100bf8 <strncmp+0xa8>
	cmpb	%bl, %al
  100b9a:	38 d8                	cmp    %bl,%al
	jne	.L21
  100b9c:	75 5a                	jne    100bf8 <strncmp+0xa8>
	movzbl	3(%edx), %eax
  100b9e:	0f b6 42 03          	movzbl 0x3(%edx),%eax
	addl	$4, %edx
  100ba2:	83 c2 04             	add    $0x4,%edx
	addl	$4, %ecx
  100ba5:	83 c1 04             	add    $0x4,%ecx
	movzbl	-1(%ecx), %ebx
  100ba8:	0f b6 59 ff          	movzbl -0x1(%ecx),%ebx
	testb	%al, %al
  100bac:	84 c0                	test   %al,%al
	je	.L21
  100bae:	74 48                	je     100bf8 <strncmp+0xa8>
	cmpb	%bl, %al
  100bb0:	38 d8                	cmp    %bl,%al
	jne	.L21
  100bb2:	75 44                	jne    100bf8 <strncmp+0xa8>
	cmpl	%edx, %esi
  100bb4:	39 d6                	cmp    %edx,%esi
	jne	.L20
  100bb6:	75 b8                	jne    100b70 <strncmp+0x20>
	andl	$3, %edi
  100bb8:	83 e7 03             	and    $0x3,%edi
	jmp	.L10
  100bbb:	eb 07                	jmp    100bc4 <strncmp+0x74>
  100bbd:	8d 76 00             	lea    0x0(%esi),%esi
	.align 16
.L25:
	xorl	%ebx, %ebx
  100bc0:	31 db                	xor    %ebx,%ebx
	xorl	%eax, %eax
  100bc2:	31 c0                	xor    %eax,%eax
.L10:
	testl	%edi, %edi
  100bc4:	85 ff                	test   %edi,%edi
	je	.L21
  100bc6:	74 30                	je     100bf8 <strncmp+0xa8>
	movzbl	(%edx), %eax
  100bc8:	0f b6 02             	movzbl (%edx),%eax
	movzbl	(%ecx), %ebx
  100bcb:	0f b6 19             	movzbl (%ecx),%ebx
	cmpb	%al, %bl
  100bce:	38 c3                	cmp    %al,%bl
	jne	.L21
  100bd0:	75 26                	jne    100bf8 <strncmp+0xa8>
	testb	%al, %al
  100bd2:	84 c0                	test   %al,%al
	je	.L21
  100bd4:	74 22                	je     100bf8 <strncmp+0xa8>
	subl	$1, %edi
  100bd6:	83 ef 01             	sub    $0x1,%edi
	je	.L21
  100bd9:	74 1d                	je     100bf8 <strncmp+0xa8>
	movzbl	1(%edx), %eax
  100bdb:	0f b6 42 01          	movzbl 0x1(%edx),%eax
	movzbl	1(%ecx), %ebx
  100bdf:	0f b6 59 01          	movzbl 0x1(%ecx),%ebx
	cmpb	%al, %bl
  100be3:	38 c3                	cmp    %al,%bl
	jne	.L21
  100be5:	75 11                	jne    100bf8 <strncmp+0xa8>
	testb	%al, %al
  100be7:	84 c0                	test   %al,%al
	je	.L21
  100be9:	74 0d                	je     100bf8 <strncmp+0xa8>
	cmpl	$1, %edi
  100beb:	83 ff 01             	cmp    $0x1,%edi
	je	.L21
  100bee:	74 08                	je     100bf8 <strncmp+0xa8>
	movzbl	2(%edx), %eax
  100bf0:	0f b6 42 02          	movzbl 0x2(%edx),%eax
	movzbl	2(%ecx), %ebx
  100bf4:	0f b6 59 02          	movzbl 0x2(%ecx),%ebx
.L21:
	subl	%ebx, %eax
  100bf8:	29 d8                	sub    %ebx,%eax
	popl	%ebx
  100bfa:	5b                   	pop    %ebx
	popl	%esi
  100bfb:	5e                   	pop    %esi
	popl	%edi
  100bfc:	5f                   	pop    %edi
	popl	%ebp
  100bfd:	5d                   	pop    %ebp
	ret
  100bfe:	c3                   	ret    
  100bff:	90                   	nop

00100c00 <critical_factorization>:

/ critical_factorization: internal fn
.align 16
.type	critical_factorization, @function
critical_factorization:
	pushl	%ebp
  100c00:	55                   	push   %ebp
	movl	%esp, %ebp
  100c01:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  100c03:	57                   	push   %edi
	pushl	%esi
  100c04:	56                   	push   %esi
	pushl	%ebx
  100c05:	53                   	push   %ebx
	subl	$20, %esp
  100c06:	83 ec 14             	sub    $0x14,%esp
	movl	%edx, -20(%ebp)
  100c09:	89 55 ec             	mov    %edx,-0x14(%ebp)
	movl	%ecx, -28(%ebp)
  100c0c:	89 4d e4             	mov    %ecx,-0x1c(%ebp)
	cmpl	$1, %edx
  100c0f:	83 fa 01             	cmp    $0x1,%edx
	jbe	.L15
  100c12:	0f 86 58 01 00 00    	jbe    100d70 <critical_factorization+0x170>
	movl	$1, %edi
  100c18:	bf 01 00 00 00       	mov    $0x1,%edi
	xorl	%ebx, %ebx
  100c1d:	31 db                	xor    %ebx,%ebx
	movl	$-1, %esi
  100c1f:	be ff ff ff ff       	mov    $0xffffffff,%esi
	movl	$1, %ecx
  100c24:	b9 01 00 00 00       	mov    $0x1,%ecx
	movl	%edi, -24(%ebp)
  100c29:	89 7d e8             	mov    %edi,-0x18(%ebp)
	movl	$1, %edx
  100c2c:	ba 01 00 00 00       	mov    $0x1,%edx
	movl	%esi, %edi
  100c31:	89 f7                	mov    %esi,%edi
	movl	%ebx, -16(%ebp)
  100c33:	89 5d f0             	mov    %ebx,-0x10(%ebp)
	jmp	.L7
  100c36:	eb 21                	jmp    100c59 <critical_factorization+0x59>
  100c38:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  100c3f:	90                   	nop
	.align 16
.L22:
	movl	%edx, %esi
  100c40:	89 d6                	mov    %edx,%esi
	movl	%edx, -16(%ebp)
  100c42:	89 55 f0             	mov    %edx,-0x10(%ebp)
	movl	$1, %ecx
  100c45:	b9 01 00 00 00       	mov    $0x1,%ecx
	movl	%edx, %ebx
  100c4a:	89 d3                	mov    %edx,%ebx
	subl	%edi, %esi
  100c4c:	29 fe                	sub    %edi,%esi
	movl	%esi, -24(%ebp)
  100c4e:	89 75 e8             	mov    %esi,-0x18(%ebp)
.L4:
	leal	(%ebx,%ecx), %edx
  100c51:	8d 14 0b             	lea    (%ebx,%ecx,1),%edx
	cmpl	%edx, -20(%ebp)
  100c54:	39 55 ec             	cmp    %edx,-0x14(%ebp)
	jbe	.L21
  100c57:	76 33                	jbe    100c8c <critical_factorization+0x8c>
.L7:
	leal	(%eax,%edi), %esi
  100c59:	8d 34 38             	lea    (%eax,%edi,1),%esi
	movzbl	(%esi,%ecx), %ebx
  100c5c:	0f b6 1c 0e          	movzbl (%esi,%ecx,1),%ebx
	cmpb	%bl, (%eax,%edx)
  100c60:	38 1c 10             	cmp    %bl,(%eax,%edx,1)
	jb	.L22
  100c63:	72 db                	jb     100c40 <critical_factorization+0x40>
	je	.L23
  100c65:	0f 84 c5 00 00 00    	je     100d30 <critical_factorization+0x130>
	movl	-16(%ebp), %ecx
  100c6b:	8b 4d f0             	mov    -0x10(%ebp),%ecx
	movl	$1, -24(%ebp)
  100c6e:	c7 45 e8 01 00 00 00 	movl   $0x1,-0x18(%ebp)
	leal	1(%ecx), %esi
  100c75:	8d 71 01             	lea    0x1(%ecx),%esi
	movl	%ecx, %edi
  100c78:	89 cf                	mov    %ecx,%edi
	movl	$1, %ecx
  100c7a:	b9 01 00 00 00       	mov    $0x1,%ecx
	movl	%esi, %ebx
  100c7f:	89 f3                	mov    %esi,%ebx
	movl	%esi, -16(%ebp)
  100c81:	89 75 f0             	mov    %esi,-0x10(%ebp)
	leal	(%ebx,%ecx), %edx
  100c84:	8d 14 0b             	lea    (%ebx,%ecx,1),%edx
	cmpl	%edx, -20(%ebp)
  100c87:	39 55 ec             	cmp    %edx,-0x14(%ebp)
	ja	.L7
  100c8a:	77 cd                	ja     100c59 <critical_factorization+0x59>
.L21:
	movl	-28(%ebp), %esi
  100c8c:	8b 75 e4             	mov    -0x1c(%ebp),%esi
	movl	%edi, -32(%ebp)
  100c8f:	89 7d e0             	mov    %edi,-0x20(%ebp)
	xorl	%ebx, %ebx
  100c92:	31 db                	xor    %ebx,%ebx
	movl	$1, %ecx
  100c94:	b9 01 00 00 00       	mov    $0x1,%ecx
	movl	-24(%ebp), %edi
  100c99:	8b 7d e8             	mov    -0x18(%ebp),%edi
	movl	%ebx, -16(%ebp)
  100c9c:	89 5d f0             	mov    %ebx,-0x10(%ebp)
	movl	$1, %edx
  100c9f:	ba 01 00 00 00       	mov    $0x1,%edx
	movl	$1, -24(%ebp)
  100ca4:	c7 45 e8 01 00 00 00 	movl   $0x1,-0x18(%ebp)
	movl	%edi, (%esi)
  100cab:	89 3e                	mov    %edi,(%esi)
	movl	$-1, %esi
  100cad:	be ff ff ff ff       	mov    $0xffffffff,%esi
	jmp	.L13
  100cb2:	eb 25                	jmp    100cd9 <critical_factorization+0xd9>
  100cb4:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  100cbb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  100cbf:	90                   	nop
	.align 16
.L25:
	movl	%edx, %ebx
  100cc0:	89 d3                	mov    %edx,%ebx
	movl	%edx, -16(%ebp)
  100cc2:	89 55 f0             	mov    %edx,-0x10(%ebp)
	movl	$1, %ecx
  100cc5:	b9 01 00 00 00       	mov    $0x1,%ecx
	subl	%esi, %ebx
  100cca:	29 f3                	sub    %esi,%ebx
	movl	%ebx, -24(%ebp)
  100ccc:	89 5d e8             	mov    %ebx,-0x18(%ebp)
	movl	%edx, %ebx
  100ccf:	89 d3                	mov    %edx,%ebx
.L10:
	leal	(%ebx,%ecx), %edx
  100cd1:	8d 14 0b             	lea    (%ebx,%ecx,1),%edx
	cmpl	%edx, -20(%ebp)
  100cd4:	39 55 ec             	cmp    %edx,-0x14(%ebp)
	jbe	.L24
  100cd7:	76 2f                	jbe    100d08 <critical_factorization+0x108>
.L13:
	leal	(%eax,%ecx), %edi
  100cd9:	8d 3c 08             	lea    (%eax,%ecx,1),%edi
	movzbl	(%edi,%esi), %ebx
  100cdc:	0f b6 1c 37          	movzbl (%edi,%esi,1),%ebx
	cmpb	%bl, (%eax,%edx)
  100ce0:	38 1c 10             	cmp    %bl,(%eax,%edx,1)
	ja	.L25
  100ce3:	77 db                	ja     100cc0 <critical_factorization+0xc0>
	je	.L26
  100ce5:	74 59                	je     100d40 <critical_factorization+0x140>
	movl	-16(%ebp), %edi
  100ce7:	8b 7d f0             	mov    -0x10(%ebp),%edi
	movl	$1, %ecx
  100cea:	b9 01 00 00 00       	mov    $0x1,%ecx
	movl	$1, -24(%ebp)
  100cef:	c7 45 e8 01 00 00 00 	movl   $0x1,-0x18(%ebp)
	movl	%edi, %esi
  100cf6:	89 fe                	mov    %edi,%esi
	addl	$1, %edi
  100cf8:	83 c7 01             	add    $0x1,%edi
	movl	%edi, %ebx
  100cfb:	89 fb                	mov    %edi,%ebx
	movl	%edi, -16(%ebp)
  100cfd:	89 7d f0             	mov    %edi,-0x10(%ebp)
	leal	(%ebx,%ecx), %edx
  100d00:	8d 14 0b             	lea    (%ebx,%ecx,1),%edx
	cmpl	%edx, -20(%ebp)
  100d03:	39 55 ec             	cmp    %edx,-0x14(%ebp)
	ja	.L13
  100d06:	77 d1                	ja     100cd9 <critical_factorization+0xd9>
.L24:
	movl	-32(%ebp), %eax
  100d08:	8b 45 e0             	mov    -0x20(%ebp),%eax
	addl	$1, %esi
  100d0b:	83 c6 01             	add    $0x1,%esi
	addl	$1, %eax
  100d0e:	83 c0 01             	add    $0x1,%eax
	cmpl	%eax, %esi
  100d11:	39 c6                	cmp    %eax,%esi
	jb	.L1
  100d13:	72 0a                	jb     100d1f <critical_factorization+0x11f>
.L2:
	movl	-28(%ebp), %eax
  100d15:	8b 45 e4             	mov    -0x1c(%ebp),%eax
	movl	-24(%ebp), %edi
  100d18:	8b 7d e8             	mov    -0x18(%ebp),%edi
	movl	%edi, (%eax)
  100d1b:	89 38                	mov    %edi,(%eax)
	movl	%esi, %eax
  100d1d:	89 f0                	mov    %esi,%eax
.L1:
	addl	$20, %esp
  100d1f:	83 c4 14             	add    $0x14,%esp
	popl	%ebx
  100d22:	5b                   	pop    %ebx
	popl	%esi
  100d23:	5e                   	pop    %esi
	popl	%edi
  100d24:	5f                   	pop    %edi
	popl	%ebp
  100d25:	5d                   	pop    %ebp
	ret
  100d26:	c3                   	ret    
  100d27:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  100d2e:	66 90                	xchg   %ax,%ax
	.align 16
.L23:
	cmpl	-24(%ebp), %ecx
  100d30:	3b 4d e8             	cmp    -0x18(%ebp),%ecx
	je	.L6
  100d33:	74 1b                	je     100d50 <critical_factorization+0x150>
	movl	-16(%ebp), %ebx
  100d35:	8b 5d f0             	mov    -0x10(%ebp),%ebx
	addl	$1, %ecx
  100d38:	83 c1 01             	add    $0x1,%ecx
	jmp	.L4
  100d3b:	e9 11 ff ff ff       	jmp    100c51 <critical_factorization+0x51>
	.align 16
.L26:
	cmpl	-24(%ebp), %ecx
  100d40:	3b 4d e8             	cmp    -0x18(%ebp),%ecx
	je	.L12
  100d43:	74 1b                	je     100d60 <critical_factorization+0x160>
	movl	-16(%ebp), %ebx
  100d45:	8b 5d f0             	mov    -0x10(%ebp),%ebx
	addl	$1, %ecx
  100d48:	83 c1 01             	add    $0x1,%ecx
	jmp	.L10
  100d4b:	eb 84                	jmp    100cd1 <critical_factorization+0xd1>
  100d4d:	8d 76 00             	lea    0x0(%esi),%esi
	.align 16
.L6:
	addl	%ecx, -16(%ebp)
  100d50:	01 4d f0             	add    %ecx,-0x10(%ebp)
	movl	$1, %ecx
  100d53:	b9 01 00 00 00       	mov    $0x1,%ecx
	movl	-16(%ebp), %ebx
  100d58:	8b 5d f0             	mov    -0x10(%ebp),%ebx
	jmp	.L4
  100d5b:	e9 f1 fe ff ff       	jmp    100c51 <critical_factorization+0x51>
	.align 16
.L12:
	addl	%ecx, -16(%ebp)
  100d60:	01 4d f0             	add    %ecx,-0x10(%ebp)
	movl	$1, %ecx
  100d63:	b9 01 00 00 00       	mov    $0x1,%ecx
	movl	-16(%ebp), %ebx
  100d68:	8b 5d f0             	mov    -0x10(%ebp),%ebx
	jmp	.L10
  100d6b:	e9 61 ff ff ff       	jmp    100cd1 <critical_factorization+0xd1>
	.align 16
.L15:
	movl	$1, -24(%ebp)
  100d70:	c7 45 e8 01 00 00 00 	movl   $0x1,-0x18(%ebp)
	xorl	%esi, %esi
  100d77:	31 f6                	xor    %esi,%esi
	jmp	.L2
  100d79:	eb 9a                	jmp    100d15 <critical_factorization+0x115>
  100d7b:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  100d7f:	90                   	nop

00100d80 <two_way_long_needle>:

/ another internal function
.align 16
.type	two_way_long_needle, @function
two_way_long_needle:
	pushl	%ebp
  100d80:	55                   	push   %ebp
	movl	%esp, %ebp
  100d81:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  100d83:	57                   	push   %edi
	movl	%ecx, %edi
  100d84:	89 cf                	mov    %ecx,%edi
	pushl	%esi
  100d86:	56                   	push   %esi
	leal	-1052(%ebp), %ecx
  100d87:	8d 8d e4 fb ff ff    	lea    -0x41c(%ebp),%ecx
	pushl	%ebx
  100d8d:	53                   	push   %ebx
	subl	$1084, %esp
  100d8e:	81 ec 3c 04 00 00    	sub    $0x43c,%esp
	movl	8(%ebp), %ebx
  100d94:	8b 5d 08             	mov    0x8(%ebp),%ebx
	movl	%eax, -1072(%ebp)
  100d97:	89 85 d0 fb ff ff    	mov    %eax,-0x430(%ebp)
	movl	%edi, %eax
  100d9d:	89 f8                	mov    %edi,%eax
	movl	%edx, -1068(%ebp)
  100d9f:	89 95 d4 fb ff ff    	mov    %edx,-0x42c(%ebp)
	movl	%ebx, %edx
  100da5:	89 da                	mov    %ebx,%edx
	call	critical_factorization
  100da7:	e8 54 fe ff ff       	call   100c00 <critical_factorization>
	leal	-24(%ebp), %edx
  100dac:	8d 55 e8             	lea    -0x18(%ebp),%edx
	movl	%eax, -1084(%ebp)
  100daf:	89 85 c4 fb ff ff    	mov    %eax,-0x43c(%ebp)
	leal	-1048(%ebp), %eax
  100db5:	8d 85 e8 fb ff ff    	lea    -0x418(%ebp),%eax
  100dbb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  100dbf:	90                   	nop
	.align 16
.L28:
	movl	%ebx, (%eax)
  100dc0:	89 18                	mov    %ebx,(%eax)
	addl	$4, %eax
  100dc2:	83 c0 04             	add    $0x4,%eax
	cmpl	%eax, %edx
  100dc5:	39 c2                	cmp    %eax,%edx
	jne	.L28
  100dc7:	75 f7                	jne    100dc0 <two_way_long_needle+0x40>
	testl	%ebx, %ebx
  100dc9:	85 db                	test   %ebx,%ebx
	je	.L33
  100dcb:	74 2e                	je     100dfb <two_way_long_needle+0x7b>
	leal	(%edi,%ebx), %edx
  100dcd:	8d 14 1f             	lea    (%edi,%ebx,1),%edx
	movl	%edi, -1076(%ebp)
  100dd0:	89 bd cc fb ff ff    	mov    %edi,-0x434(%ebp)
	movl	%edi, %eax
  100dd6:	89 f8                	mov    %edi,%eax
	leal	-1(%edi,%ebx), %esi
  100dd8:	8d 74 1f ff          	lea    -0x1(%edi,%ebx,1),%esi
	movl	%edx, %edi
  100ddc:	89 d7                	mov    %edx,%edi
  100dde:	66 90                	xchg   %ax,%ax
	.align 16
.L32:
	movzbl	(%eax), %edx
  100de0:	0f b6 10             	movzbl (%eax),%edx
	movl	%esi, %ecx
  100de3:	89 f1                	mov    %esi,%ecx
	subl	%eax, %ecx
  100de5:	29 c1                	sub    %eax,%ecx
	addl	$1, %eax
  100de7:	83 c0 01             	add    $0x1,%eax
	movl	%ecx, -1048(%ebp,%edx,4)
  100dea:	89 8c 95 e8 fb ff ff 	mov    %ecx,-0x418(%ebp,%edx,4)
	cmpl	%eax, %edi
  100df1:	39 c7                	cmp    %eax,%edi
	jne	.L32
  100df3:	75 eb                	jne    100de0 <two_way_long_needle+0x60>
	movl	-1076(%ebp), %edi
  100df5:	8b bd cc fb ff ff    	mov    -0x434(%ebp),%edi
.L33:
	movl	-1052(%ebp), %eax
  100dfb:	8b 85 e4 fb ff ff    	mov    -0x41c(%ebp),%eax
	subl	$4, %esp
  100e01:	83 ec 04             	sub    $0x4,%esp
	pushl	-1084(%ebp)
  100e04:	ff b5 c4 fb ff ff    	push   -0x43c(%ebp)
	movl	%eax, -1092(%ebp)
  100e0a:	89 85 bc fb ff ff    	mov    %eax,-0x444(%ebp)
	addl	%edi, %eax
  100e10:	01 f8                	add    %edi,%eax
	pushl	%eax
  100e12:	50                   	push   %eax
	pushl	%edi
  100e13:	57                   	push   %edi
	call	memcmp
  100e14:	e8 07 fa ff ff       	call   100820 <memcmp>
	addl	$16, %esp
  100e19:	83 c4 10             	add    $0x10,%esp
	testl	%eax, %eax
  100e1c:	85 c0                	test   %eax,%eax
	jne	.L90
  100e1e:	0f 85 cb 01 00 00    	jne    100fef <two_way_long_needle+0x26f>
	movl	$0, -1080(%ebp)
  100e24:	c7 85 c8 fb ff ff 00 	movl   $0x0,-0x438(%ebp)
  100e2b:	00 00 00 
	movl	$1, %eax
  100e2e:	b8 01 00 00 00       	mov    $0x1,%eax
	subl	-1084(%ebp), %eax
  100e33:	2b 85 c4 fb ff ff    	sub    -0x43c(%ebp),%eax
	movl	$0, -1076(%ebp)
  100e39:	c7 85 cc fb ff ff 00 	movl   $0x0,-0x434(%ebp)
  100e40:	00 00 00 
	movl	%eax, -1096(%ebp)
  100e43:	89 85 b8 fb ff ff    	mov    %eax,-0x448(%ebp)
  100e49:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L30:
	movl	-1076(%ebp), %eax
  100e50:	8b 85 cc fb ff ff    	mov    -0x434(%ebp),%eax
	movl	-1068(%ebp), %ecx
  100e56:	8b 8d d4 fb ff ff    	mov    -0x42c(%ebp),%ecx
	leal	(%eax,%ebx), %esi
  100e5c:	8d 34 18             	lea    (%eax,%ebx,1),%esi
	cmpl	%ecx, %esi
  100e5f:	39 ce                	cmp    %ecx,%esi
	jbe	.L45
  100e61:	76 2d                	jbe    100e90 <two_way_long_needle+0x110>
	movl	-1072(%ebp), %eax
  100e63:	8b 85 d0 fb ff ff    	mov    -0x430(%ebp),%eax
	subl	$8, %esp
  100e69:	83 ec 08             	sub    $0x8,%esp
	pushl	$512
  100e6c:	68 00 02 00 00       	push   $0x200
	addl	%ecx, %eax
  100e71:	01 c8                	add    %ecx,%eax
	pushl	%eax
  100e73:	50                   	push   %eax
	call	strnlen
  100e74:	e8 cc fb ff ff       	call   100a45 <strnlen>
	addl	%eax, -1068(%ebp)
  100e79:	01 85 d4 fb ff ff    	add    %eax,-0x42c(%ebp)
	addl	$16, %esp
  100e7f:	83 c4 10             	add    $0x10,%esp
	movl	-1068(%ebp), %ecx
  100e82:	8b 8d d4 fb ff ff    	mov    -0x42c(%ebp),%ecx
	cmpl	%ecx, %esi
  100e88:	39 ce                	cmp    %ecx,%esi
	ja	.L89
  100e8a:	0f 87 4a 01 00 00    	ja     100fda <two_way_long_needle+0x25a>
.L45:
	movl	-1072(%ebp), %eax
  100e90:	8b 85 d0 fb ff ff    	mov    -0x430(%ebp),%eax
	movzbl	-1(%eax,%esi), %eax
  100e96:	0f b6 44 30 ff       	movzbl -0x1(%eax,%esi,1),%eax
	movl	-1048(%ebp,%eax,4), %eax
  100e9b:	8b 84 85 e8 fb ff ff 	mov    -0x418(%ebp,%eax,4),%eax
	testl	%eax, %eax
  100ea2:	85 c0                	test   %eax,%eax
	je	.L34
  100ea4:	74 3a                	je     100ee0 <two_way_long_needle+0x160>
	movl	-1080(%ebp), %edx
  100ea6:	8b 95 c8 fb ff ff    	mov    -0x438(%ebp),%edx
	testl	%edx, %edx
  100eac:	85 d2                	test   %edx,%edx
	je	.L35
  100eae:	74 14                	je     100ec4 <two_way_long_needle+0x144>
	movl	-1092(%ebp), %esi
  100eb0:	8b b5 bc fb ff ff    	mov    -0x444(%ebp),%esi
	movl	%ebx, %edx
  100eb6:	89 da                	mov    %ebx,%edx
	cmpl	%eax, %esi
  100eb8:	39 c6                	cmp    %eax,%esi
	seta	%cl
  100eba:	0f 97 c1             	seta   %cl
	subl	%esi, %edx
  100ebd:	29 f2                	sub    %esi,%edx
	testb	%cl, %cl
  100ebf:	84 c9                	test   %cl,%cl
	cmovne	%edx, %eax
  100ec1:	0f 45 c2             	cmovne %edx,%eax
.L35:
	addl	%eax, -1076(%ebp)
  100ec4:	01 85 cc fb ff ff    	add    %eax,-0x434(%ebp)
	movl	$0, -1080(%ebp)
  100eca:	c7 85 c8 fb ff ff 00 	movl   $0x0,-0x438(%ebp)
  100ed1:	00 00 00 
	jmp	.L30
  100ed4:	e9 77 ff ff ff       	jmp    100e50 <two_way_long_needle+0xd0>
  100ed9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L34:
	movl	-1080(%ebp), %esi
  100ee0:	8b b5 c8 fb ff ff    	mov    -0x438(%ebp),%esi
	movl	-1084(%ebp), %eax
  100ee6:	8b 85 c4 fb ff ff    	mov    -0x43c(%ebp),%eax
	leal	-1(%ebx), %edx
  100eec:	8d 53 ff             	lea    -0x1(%ebx),%edx
	movl	-1076(%ebp), %ecx
  100eef:	8b 8d cc fb ff ff    	mov    -0x434(%ebp),%ecx
	cmpl	%eax, %esi
  100ef5:	39 c6                	cmp    %eax,%esi
	cmovnb	%esi, %eax
  100ef7:	0f 43 c6             	cmovae %esi,%eax
	movl	-1072(%ebp), %esi
  100efa:	8b b5 d0 fb ff ff    	mov    -0x430(%ebp),%esi
	addl	%esi, %ecx
  100f00:	01 f1                	add    %esi,%ecx
	movl	%ebx, %esi
  100f02:	89 de                	mov    %ebx,%esi
	cmpl	%edx, %eax
  100f04:	39 d0                	cmp    %edx,%eax
	jb	.L37
  100f06:	72 0f                	jb     100f17 <two_way_long_needle+0x197>
	jmp	.L38
  100f08:	eb 48                	jmp    100f52 <two_way_long_needle+0x1d2>
  100f0a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	.align 16
.L39:
	addl	$1, %eax
  100f10:	83 c0 01             	add    $0x1,%eax
	cmpl	%edx, %eax
  100f13:	39 d0                	cmp    %edx,%eax
	jnb	.L83
  100f15:	73 39                	jae    100f50 <two_way_long_needle+0x1d0>
.L37:
	movzbl	(%ecx,%eax), %ebx
  100f17:	0f b6 1c 01          	movzbl (%ecx,%eax,1),%ebx
	cmpb	%bl, (%edi,%eax)
  100f1b:	38 1c 07             	cmp    %bl,(%edi,%eax,1)
	je	.L39
  100f1e:	74 f0                	je     100f10 <two_way_long_needle+0x190>
	movl	-1076(%ebp), %edx
  100f20:	8b 95 cc fb ff ff    	mov    -0x434(%ebp),%edx
	addl	-1096(%ebp), %edx
  100f26:	03 95 b8 fb ff ff    	add    -0x448(%ebp),%edx
	movl	%esi, %ebx
  100f2c:	89 f3                	mov    %esi,%ebx
	movl	$0, -1080(%ebp)
  100f2e:	c7 85 c8 fb ff ff 00 	movl   $0x0,-0x438(%ebp)
  100f35:	00 00 00 
	addl	%edx, %eax
  100f38:	01 d0                	add    %edx,%eax
	movl	%eax, -1076(%ebp)
  100f3a:	89 85 cc fb ff ff    	mov    %eax,-0x434(%ebp)
	jmp	.L30
  100f40:	e9 0b ff ff ff       	jmp    100e50 <two_way_long_needle+0xd0>
  100f45:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  100f4c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L83:
	movl	%esi, %ebx
  100f50:	89 f3                	mov    %esi,%ebx
.L38:
	movl	-1084(%ebp), %edx
  100f52:	8b 95 c4 fb ff ff    	mov    -0x43c(%ebp),%edx
	movl	-1076(%ebp), %esi
  100f58:	8b b5 cc fb ff ff    	mov    -0x434(%ebp),%esi
	leal	-1(%edx), %eax
  100f5e:	8d 42 ff             	lea    -0x1(%edx),%eax
	leal	(%esi,%eax), %ecx
  100f61:	8d 0c 06             	lea    (%esi,%eax,1),%ecx
	leal	-1(%edi), %esi
  100f64:	8d 77 ff             	lea    -0x1(%edi),%esi
	subl	%edx, %ecx
  100f67:	29 d1                	sub    %edx,%ecx
	addl	-1072(%ebp), %ecx
  100f69:	03 8d d0 fb ff ff    	add    -0x430(%ebp),%ecx
	cmpl	%edx, -1080(%ebp)
  100f6f:	39 95 c8 fb ff ff    	cmp    %edx,-0x438(%ebp)
	jnb	.L41
  100f75:	73 37                	jae    100fae <two_way_long_needle+0x22e>
	movl	%ebx, 8(%ebp)
  100f77:	89 5d 08             	mov    %ebx,0x8(%ebp)
	movl	-1080(%ebp), %ebx
  100f7a:	8b 9d c8 fb ff ff    	mov    -0x438(%ebp),%ebx
	movl	%ebx, -1088(%ebp)
  100f80:	89 9d c0 fb ff ff    	mov    %ebx,-0x440(%ebp)
	jmp	.L57
  100f86:	eb 15                	jmp    100f9d <two_way_long_needle+0x21d>
  100f88:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  100f8f:	90                   	nop
	.align 16
.L42:
	leal	-1(%eax), %edx
  100f90:	8d 50 ff             	lea    -0x1(%eax),%edx
	cmpl	%eax, -1088(%ebp)
  100f93:	39 85 c0 fb ff ff    	cmp    %eax,-0x440(%ebp)
	je	.L60
  100f99:	74 49                	je     100fe4 <two_way_long_needle+0x264>
	movl	%edx, %eax
  100f9b:	89 d0                	mov    %edx,%eax
.L57:
	movzbl	1(%eax,%ecx), %ebx
  100f9d:	0f b6 5c 08 01       	movzbl 0x1(%eax,%ecx,1),%ebx
	leal	1(%eax), %edx
  100fa2:	8d 50 01             	lea    0x1(%eax),%edx
	cmpb	%bl, 1(%esi,%eax)
  100fa5:	38 5c 06 01          	cmp    %bl,0x1(%esi,%eax,1)
	je	.L42
  100fa9:	74 e5                	je     100f90 <two_way_long_needle+0x210>
	movl	8(%ebp), %ebx
  100fab:	8b 5d 08             	mov    0x8(%ebp),%ebx
.L41:
	movl	-1080(%ebp), %eax
  100fae:	8b 85 c8 fb ff ff    	mov    -0x438(%ebp),%eax
	addl	$1, %eax
  100fb4:	83 c0 01             	add    $0x1,%eax
	cmpl	%eax, %edx
  100fb7:	39 c2                	cmp    %eax,%edx
	jb	.L91
  100fb9:	0f 82 72 01 00 00    	jb     101131 <two_way_long_needle+0x3b1>
	movl	-1092(%ebp), %esi
  100fbf:	8b b5 bc fb ff ff    	mov    -0x444(%ebp),%esi
	movl	%ebx, %eax
  100fc5:	89 d8                	mov    %ebx,%eax
	addl	%esi, -1076(%ebp)
  100fc7:	01 b5 cc fb ff ff    	add    %esi,-0x434(%ebp)
	subl	%esi, %eax
  100fcd:	29 f0                	sub    %esi,%eax
	movl	%eax, -1080(%ebp)
  100fcf:	89 85 c8 fb ff ff    	mov    %eax,-0x438(%ebp)
	jmp	.L30
  100fd5:	e9 76 fe ff ff       	jmp    100e50 <two_way_long_needle+0xd0>
.L89:
	xorl	%eax, %eax
  100fda:	31 c0                	xor    %eax,%eax
.L27:
	leal	-12(%ebp), %esp
  100fdc:	8d 65 f4             	lea    -0xc(%ebp),%esp
	popl	%ebx
  100fdf:	5b                   	pop    %ebx
	popl	%esi
  100fe0:	5e                   	pop    %esi
	popl	%edi
  100fe1:	5f                   	pop    %edi
	popl	%ebp
  100fe2:	5d                   	pop    %ebp
	ret
  100fe3:	c3                   	ret    
.L60:
	movl	8(%ebp), %ebx
  100fe4:	8b 5d 08             	mov    0x8(%ebp),%ebx
	movl	-1080(%ebp), %edx
  100fe7:	8b 95 c8 fb ff ff    	mov    -0x438(%ebp),%edx
	jmp	.L41
  100fed:	eb bf                	jmp    100fae <two_way_long_needle+0x22e>
.L90:
	movl	-1084(%ebp), %edx
  100fef:	8b 95 c4 fb ff ff    	mov    -0x43c(%ebp),%edx
	movl	%ebx, %eax
  100ff5:	89 d8                	mov    %ebx,%eax
	leal	-1(%ebx), %ecx
  100ff7:	8d 4b ff             	lea    -0x1(%ebx),%ecx
	movl	%ebx, 8(%ebp)
  100ffa:	89 5d 08             	mov    %ebx,0x8(%ebp)
	movl	%ecx, %ebx
  100ffd:	89 cb                	mov    %ecx,%ebx
	subl	%edx, %eax
  100fff:	29 d0                	sub    %edx,%eax
	cmpl	%edx, %eax
  101001:	39 d0                	cmp    %edx,%eax
	cmovb	%edx, %eax
  101003:	0f 42 c2             	cmovb  %edx,%eax
	xorl	%esi, %esi
  101006:	31 f6                	xor    %esi,%esi
	addl	$1, %eax
  101008:	83 c0 01             	add    $0x1,%eax
	movl	%eax, -1092(%ebp)
  10100b:	89 85 bc fb ff ff    	mov    %eax,-0x444(%ebp)
	leal	-1(%edx), %eax
  101011:	8d 42 ff             	lea    -0x1(%edx),%eax
	movl	%eax, -1088(%ebp)
  101014:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%ebp)
	movl	$1, %eax
  10101a:	b8 01 00 00 00       	mov    $0x1,%eax
	subl	%edx, %eax
  10101f:	29 d0                	sub    %edx,%eax
	movl	%eax, -1080(%ebp)
  101021:	89 85 c8 fb ff ff    	mov    %eax,-0x438(%ebp)
  101027:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10102e:	66 90                	xchg   %ax,%ax
	.align 16
.L46:
	movl	8(%ebp), %edx
  101030:	8b 55 08             	mov    0x8(%ebp),%edx
	movl	-1068(%ebp), %ecx
  101033:	8b 8d d4 fb ff ff    	mov    -0x42c(%ebp),%ecx
	addl	%esi, %edx
  101039:	01 f2                	add    %esi,%edx
	cmpl	%ecx, %edx
  10103b:	39 ca                	cmp    %ecx,%edx
	jbe	.L56
  10103d:	76 39                	jbe    101078 <two_way_long_needle+0x2f8>
	movl	-1072(%ebp), %eax
  10103f:	8b 85 d0 fb ff ff    	mov    -0x430(%ebp),%eax
	subl	$8, %esp
  101045:	83 ec 08             	sub    $0x8,%esp
	movl	%edx, -1076(%ebp)
  101048:	89 95 cc fb ff ff    	mov    %edx,-0x434(%ebp)
	pushl	$512
  10104e:	68 00 02 00 00       	push   $0x200
	addl	%ecx, %eax
  101053:	01 c8                	add    %ecx,%eax
	pushl	%eax
  101055:	50                   	push   %eax
	call	strnlen
  101056:	e8 ea f9 ff ff       	call   100a45 <strnlen>
	movl	-1076(%ebp), %edx
  10105b:	8b 95 cc fb ff ff    	mov    -0x434(%ebp),%edx
	addl	%eax, -1068(%ebp)
  101061:	01 85 d4 fb ff ff    	add    %eax,-0x42c(%ebp)
	addl	$16, %esp
  101067:	83 c4 10             	add    $0x10,%esp
	movl	-1068(%ebp), %eax
  10106a:	8b 85 d4 fb ff ff    	mov    -0x42c(%ebp),%eax
	cmpl	%eax, %edx
  101070:	39 c2                	cmp    %eax,%edx
	ja	.L89
  101072:	0f 87 62 ff ff ff    	ja     100fda <two_way_long_needle+0x25a>
.L56:
	movl	-1072(%ebp), %eax
  101078:	8b 85 d0 fb ff ff    	mov    -0x430(%ebp),%eax
	movzbl	-1(%eax,%edx), %eax
  10107e:	0f b6 44 10 ff       	movzbl -0x1(%eax,%edx,1),%eax
	movl	-1048(%ebp,%eax,4), %eax
  101083:	8b 84 85 e8 fb ff ff 	mov    -0x418(%ebp,%eax,4),%eax
	testl	%eax, %eax
  10108a:	85 c0                	test   %eax,%eax
	je	.L47
  10108c:	74 12                	je     1010a0 <two_way_long_needle+0x320>
	addl	%eax, %esi
  10108e:	01 c6                	add    %eax,%esi
	jmp	.L46
  101090:	eb 9e                	jmp    101030 <two_way_long_needle+0x2b0>
  101092:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  101099:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L47:
	movl	-1084(%ebp), %ecx
  1010a0:	8b 8d c4 fb ff ff    	mov    -0x43c(%ebp),%ecx
	movl	-1072(%ebp), %edx
  1010a6:	8b 95 d0 fb ff ff    	mov    -0x430(%ebp),%edx
	movl	%ecx, %eax
  1010ac:	89 c8                	mov    %ecx,%eax
	addl	%esi, %edx
  1010ae:	01 f2                	add    %esi,%edx
	cmpl	%ecx, %ebx
  1010b0:	39 cb                	cmp    %ecx,%ebx
	ja	.L49
  1010b2:	77 13                	ja     1010c7 <two_way_long_needle+0x347>
	jmp	.L50
  1010b4:	eb 2a                	jmp    1010e0 <two_way_long_needle+0x360>
  1010b6:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1010bd:	8d 76 00             	lea    0x0(%esi),%esi
	.align 16
.L51:
	addl	$1, %eax
  1010c0:	83 c0 01             	add    $0x1,%eax
	cmpl	%eax, %ebx
  1010c3:	39 c3                	cmp    %eax,%ebx
	jbe	.L50
  1010c5:	76 19                	jbe    1010e0 <two_way_long_needle+0x360>
.L49:
	movzbl	(%edx,%eax), %ecx
  1010c7:	0f b6 0c 02          	movzbl (%edx,%eax,1),%ecx
	cmpb	%cl, (%edi,%eax)
  1010cb:	38 0c 07             	cmp    %cl,(%edi,%eax,1)
	je	.L51
  1010ce:	74 f0                	je     1010c0 <two_way_long_needle+0x340>
	addl	-1080(%ebp), %esi
  1010d0:	03 b5 c8 fb ff ff    	add    -0x438(%ebp),%esi
	addl	%eax, %esi
  1010d6:	01 c6                	add    %eax,%esi
	jmp	.L46
  1010d8:	e9 53 ff ff ff       	jmp    101030 <two_way_long_needle+0x2b0>
  1010dd:	8d 76 00             	lea    0x0(%esi),%esi
	.align 16
.L50:
	movl	-1088(%ebp), %eax
  1010e0:	8b 85 c0 fb ff ff    	mov    -0x440(%ebp),%eax
	leal	(%esi,%eax), %edx
  1010e6:	8d 14 06             	lea    (%esi,%eax,1),%edx
	cmpl	$-1, %eax
  1010e9:	83 f8 ff             	cmp    $0xffffffff,%eax
	je	.L53
  1010ec:	74 54                	je     101142 <two_way_long_needle+0x3c2>
	subl	-1084(%ebp), %edx
  1010ee:	2b 95 c4 fb ff ff    	sub    -0x43c(%ebp),%edx
	movl	%ebx, -1076(%ebp)
  1010f4:	89 9d cc fb ff ff    	mov    %ebx,-0x434(%ebp)
	leal	-1(%edi), %ecx
  1010fa:	8d 4f ff             	lea    -0x1(%edi),%ecx
	addl	-1072(%ebp), %edx
  1010fd:	03 95 d0 fb ff ff    	add    -0x430(%ebp),%edx
	jmp	.L58
  101103:	eb 10                	jmp    101115 <two_way_long_needle+0x395>
  101105:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10110c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L54:
	subl	$1, %eax
  101110:	83 e8 01             	sub    $0x1,%eax
	jb	.L53
  101113:	72 2d                	jb     101142 <two_way_long_needle+0x3c2>
.L58:
	movzbl	1(%eax,%edx), %ebx
  101115:	0f b6 5c 10 01       	movzbl 0x1(%eax,%edx,1),%ebx
	cmpb	%bl, 1(%ecx,%eax)
  10111a:	38 5c 01 01          	cmp    %bl,0x1(%ecx,%eax,1)
	je	.L54
  10111e:	74 f0                	je     101110 <two_way_long_needle+0x390>
	movl	-1076(%ebp), %ebx
  101120:	8b 9d cc fb ff ff    	mov    -0x434(%ebp),%ebx
	addl	-1092(%ebp), %esi
  101126:	03 b5 bc fb ff ff    	add    -0x444(%ebp),%esi
	jmp	.L46
  10112c:	e9 ff fe ff ff       	jmp    101030 <two_way_long_needle+0x2b0>
.L91:
	movl	-1072(%ebp), %eax
  101131:	8b 85 d0 fb ff ff    	mov    -0x430(%ebp),%eax
	addl	-1076(%ebp), %eax
  101137:	03 85 cc fb ff ff    	add    -0x434(%ebp),%eax
	jmp	.L27
  10113d:	e9 9a fe ff ff       	jmp    100fdc <two_way_long_needle+0x25c>
.L53:
	movl	-1072(%ebp), %eax
  101142:	8b 85 d0 fb ff ff    	mov    -0x430(%ebp),%eax
	addl	%esi, %eax
  101148:	01 f0                	add    %esi,%eax
	jmp	.L27
  10114a:	e9 8d fe ff ff       	jmp    100fdc <two_way_long_needle+0x25c>
  10114f:	90                   	nop

00101150 <memchr>:
/ C: void * memchr (void const *s, int c_in, unsigned int n)
.align 16
.globl	memchr	
.type	memchr, @function
memchr:
	pushl	%ebp
  101150:	55                   	push   %ebp
	movl	%esp, %ebp
  101151:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  101153:	57                   	push   %edi
	movl	16(%ebp), %edx
  101154:	8b 55 10             	mov    0x10(%ebp),%edx
	movl	8(%ebp), %eax
  101157:	8b 45 08             	mov    0x8(%ebp),%eax
	pushl	%esi
  10115a:	56                   	push   %esi
	pushl	%ebx
  10115b:	53                   	push   %ebx
	movzbl	12(%ebp), %ebx
  10115c:	0f b6 5d 0c          	movzbl 0xc(%ebp),%ebx
	testl	%edx, %edx
  101160:	85 d2                	test   %edx,%edx
	jne	.L109
  101162:	75 18                	jne    10117c <memchr+0x2c>
	jmp	.L104
  101164:	eb 7e                	jmp    1011e4 <memchr+0x94>
  101166:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10116d:	8d 76 00             	lea    0x0(%esi),%esi
	.align 16
.L110:
	cmpb	%bl, (%eax)
  101170:	38 18                	cmp    %bl,(%eax)
	je	.L92
  101172:	74 67                	je     1011db <memchr+0x8b>
	addl	$1, %eax
  101174:	83 c0 01             	add    $0x1,%eax
	subl	$1, %edx
  101177:	83 ea 01             	sub    $0x1,%edx
	je	.L104
  10117a:	74 68                	je     1011e4 <memchr+0x94>
.L109:
	testb	$3, %al
  10117c:	a8 03                	test   $0x3,%al
	jne	.L110
  10117e:	75 f0                	jne    101170 <memchr+0x20>
	movzbl	12(%ebp), %ecx
  101180:	0f b6 4d 0c          	movzbl 0xc(%ebp),%ecx
	movl	%ecx, %esi
  101184:	89 ce                	mov    %ecx,%esi
	sall	$8, %esi
  101186:	c1 e6 08             	shl    $0x8,%esi
	orl	%esi, %ecx
  101189:	09 f1                	or     %esi,%ecx
	movl	%ecx, %edi
  10118b:	89 cf                	mov    %ecx,%edi
	sall	$16, %edi
  10118d:	c1 e7 10             	shl    $0x10,%edi
	orl	%ecx, %edi
  101190:	09 cf                	or     %ecx,%edi
	cmpl	$3, %edx
  101192:	83 fa 03             	cmp    $0x3,%edx
	ja	.L97
  101195:	77 14                	ja     1011ab <memchr+0x5b>
	jmp	.L99
  101197:	eb 28                	jmp    1011c1 <memchr+0x71>
  101199:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L112:
	subl	$4, %edx
  1011a0:	83 ea 04             	sub    $0x4,%edx
	addl	$4, %eax
  1011a3:	83 c0 04             	add    $0x4,%eax
	cmpl	$3, %edx
  1011a6:	83 fa 03             	cmp    $0x3,%edx
	jbe	.L111
  1011a9:	76 35                	jbe    1011e0 <memchr+0x90>
.L97:
	movl	(%eax), %ecx
  1011ab:	8b 08                	mov    (%eax),%ecx
	xorl	%edi, %ecx
  1011ad:	31 f9                	xor    %edi,%ecx
	leal	-16843009(%ecx), %esi
  1011af:	8d b1 ff fe fe fe    	lea    -0x1010101(%ecx),%esi
	notl	%ecx
  1011b5:	f7 d1                	not    %ecx
	andl	%ecx, %esi
  1011b7:	21 ce                	and    %ecx,%esi
	andl	$-2139062144, %esi
  1011b9:	81 e6 80 80 80 80    	and    $0x80808080,%esi
	je	.L112
  1011bf:	74 df                	je     1011a0 <memchr+0x50>
.L99:
	addl	%eax, %edx
  1011c1:	01 c2                	add    %eax,%edx
	jmp	.L98
  1011c3:	eb 12                	jmp    1011d7 <memchr+0x87>
  1011c5:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1011cc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L113:
	addl	$1, %eax
  1011d0:	83 c0 01             	add    $0x1,%eax
	cmpl	%edx, %eax
  1011d3:	39 d0                	cmp    %edx,%eax
	je	.L104
  1011d5:	74 0d                	je     1011e4 <memchr+0x94>
.L98:
	cmpb	%bl, (%eax)
  1011d7:	38 18                	cmp    %bl,(%eax)
	jne	.L113
  1011d9:	75 f5                	jne    1011d0 <memchr+0x80>
.L92:
	popl	%ebx
  1011db:	5b                   	pop    %ebx
	popl	%esi
  1011dc:	5e                   	pop    %esi
	popl	%edi
  1011dd:	5f                   	pop    %edi
	popl	%ebp
  1011de:	5d                   	pop    %ebp
	ret
  1011df:	c3                   	ret    
	.align 16
.L111:
	testl	%edx, %edx
  1011e0:	85 d2                	test   %edx,%edx
	jne	.L99
  1011e2:	75 dd                	jne    1011c1 <memchr+0x71>
.L104:
	popl	%ebx
  1011e4:	5b                   	pop    %ebx
	xorl	%eax, %eax
  1011e5:	31 c0                	xor    %eax,%eax
	popl	%esi
  1011e7:	5e                   	pop    %esi
	popl	%edi
  1011e8:	5f                   	pop    %edi
	popl	%ebp
  1011e9:	5d                   	pop    %ebp
	ret
  1011ea:	c3                   	ret    
  1011eb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  1011ef:	90                   	nop

001011f0 <strchr>:
.align 16
.globl	strchr
.type	strchr, @function

strchr:
	pushl	%ebp
  1011f0:	55                   	push   %ebp
	movl	%esp, %ebp
  1011f1:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  1011f3:	57                   	push   %edi
	pushl	%esi
  1011f4:	56                   	push   %esi
	pushl	%ebx
  1011f5:	53                   	push   %ebx
	subl	$4, %esp
  1011f6:	83 ec 04             	sub    $0x4,%esp
	movl	8(%ebp), %eax
  1011f9:	8b 45 08             	mov    0x8(%ebp),%eax
	movzbl	12(%ebp), %ecx
  1011fc:	0f b6 4d 0c          	movzbl 0xc(%ebp),%ecx
	testb	$3, %al
  101200:	a8 03                	test   $0x3,%al
	jne	.L117
  101202:	75 1b                	jne    10121f <strchr+0x2f>
	jmp	.L115
  101204:	eb 3a                	jmp    101240 <strchr+0x50>
  101206:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10120d:	8d 76 00             	lea    0x0(%esi),%esi
	.align 16
.L136:
	testb	%dl, %dl
  101210:	84 d2                	test   %dl,%dl
	je	.L126
  101212:	0f 84 a1 00 00 00    	je     1012b9 <strchr+0xc9>
	addl	$1, %eax
  101218:	83 c0 01             	add    $0x1,%eax
	testb	$3, %al
  10121b:	a8 03                	test   $0x3,%al
	je	.L115
  10121d:	74 21                	je     101240 <strchr+0x50>
.L117:
	movzbl	(%eax), %edx
  10121f:	0f b6 10             	movzbl (%eax),%edx
	cmpb	%cl, %dl
  101222:	38 ca                	cmp    %cl,%dl
	jne	.L136
  101224:	75 ea                	jne    101210 <strchr+0x20>
	movl	%eax, %esi
  101226:	89 c6                	mov    %eax,%esi
.L114:
	addl	$4, %esp
  101228:	83 c4 04             	add    $0x4,%esp
	movl	%esi, %eax
  10122b:	89 f0                	mov    %esi,%eax
	popl	%ebx
  10122d:	5b                   	pop    %ebx
	popl	%esi
  10122e:	5e                   	pop    %esi
	popl	%edi
  10122f:	5f                   	pop    %edi
	popl	%ebp
  101230:	5d                   	pop    %ebp
	ret
  101231:	c3                   	ret    
  101232:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  101239:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L115:
	movzbl	12(%ebp), %edx
  101240:	0f b6 55 0c          	movzbl 0xc(%ebp),%edx
	movl	%edx, %ebx
  101244:	89 d3                	mov    %edx,%ebx
	sall	$8, %ebx
  101246:	c1 e3 08             	shl    $0x8,%ebx
	orl	%ebx, %edx
  101249:	09 da                	or     %ebx,%edx
	movl	%edx, %ebx
  10124b:	89 d3                	mov    %edx,%ebx
	sall	$16, %ebx
  10124d:	c1 e3 10             	shl    $0x10,%ebx
	orl	%edx, %ebx
  101250:	09 d3                	or     %edx,%ebx
	movl	%ebx, -16(%ebp)
  101252:	89 5d f0             	mov    %ebx,-0x10(%ebp)
  101255:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10125c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	.align 16
.L131:
	movl	%eax, %esi
  101260:	89 c6                	mov    %eax,%esi
	movl	-16(%ebp), %edi
  101262:	8b 7d f0             	mov    -0x10(%ebp),%edi
	movl	(%eax), %ebx
  101265:	8b 18                	mov    (%eax),%ebx
	leal	4(%eax), %eax
  101267:	8d 40 04             	lea    0x4(%eax),%eax
	xorl	%ebx, %edi
  10126a:	31 df                	xor    %ebx,%edi
	leal	2130640639(%ebx), %edx
  10126c:	8d 93 ff fe fe 7e    	lea    0x7efefeff(%ebx),%edx
	xorl	%ebx, %edx
  101272:	31 da                	xor    %ebx,%edx
	leal	2130640639(%edi), %ebx
  101274:	8d 9f ff fe fe 7e    	lea    0x7efefeff(%edi),%ebx
	xorl	%edi, %ebx
  10127a:	31 fb                	xor    %edi,%ebx
	andl	%ebx, %edx
  10127c:	21 da                	and    %ebx,%edx
	orl	$2130640639, %edx
  10127e:	81 ca ff fe fe 7e    	or     $0x7efefeff,%edx
	cmpl	$-1, %edx
  101284:	83 fa ff             	cmp    $0xffffffff,%edx
	je	.L131
  101287:	74 d7                	je     101260 <strchr+0x70>
	movzbl	-4(%eax), %edx
  101289:	0f b6 50 fc          	movzbl -0x4(%eax),%edx
	cmpb	%cl, %dl
  10128d:	38 ca                	cmp    %cl,%dl
	je	.L114
  10128f:	74 97                	je     101228 <strchr+0x38>
	testb	%dl, %dl
  101291:	84 d2                	test   %dl,%dl
	je	.L126
  101293:	74 24                	je     1012b9 <strchr+0xc9>
	movzbl	-3(%eax), %edx
  101295:	0f b6 50 fd          	movzbl -0x3(%eax),%edx
	cmpb	%cl, %dl
  101299:	38 ca                	cmp    %cl,%dl
	je	.L137
  10129b:	74 28                	je     1012c5 <strchr+0xd5>
	testb	%dl, %dl
  10129d:	84 d2                	test   %dl,%dl
	je	.L126
  10129f:	74 18                	je     1012b9 <strchr+0xc9>
	movzbl	-2(%eax), %edx
  1012a1:	0f b6 50 fe          	movzbl -0x2(%eax),%edx
	cmpb	%cl, %dl
  1012a5:	38 ca                	cmp    %cl,%dl
	je	.L138
  1012a7:	74 24                	je     1012cd <strchr+0xdd>
	testb	%dl, %dl
  1012a9:	84 d2                	test   %dl,%dl
	je	.L126
  1012ab:	74 0c                	je     1012b9 <strchr+0xc9>
	movzbl	-1(%eax), %edx
  1012ad:	0f b6 50 ff          	movzbl -0x1(%eax),%edx
	cmpb	%cl, %dl
  1012b1:	38 ca                	cmp    %cl,%dl
	je	.L139
  1012b3:	74 20                	je     1012d5 <strchr+0xe5>
	testb	%dl, %dl
  1012b5:	84 d2                	test   %dl,%dl
	jne	.L131
  1012b7:	75 a7                	jne    101260 <strchr+0x70>
.L126:
	addl	$4, %esp
  1012b9:	83 c4 04             	add    $0x4,%esp
	xorl	%esi, %esi
  1012bc:	31 f6                	xor    %esi,%esi
	popl	%ebx
  1012be:	5b                   	pop    %ebx
	movl	%esi, %eax
  1012bf:	89 f0                	mov    %esi,%eax
	popl	%esi
  1012c1:	5e                   	pop    %esi
	popl	%edi
  1012c2:	5f                   	pop    %edi
	popl	%ebp
  1012c3:	5d                   	pop    %ebp
	ret
  1012c4:	c3                   	ret    
.L137:
	addl	$1, %esi
  1012c5:	83 c6 01             	add    $0x1,%esi
	jmp	.L114
  1012c8:	e9 5b ff ff ff       	jmp    101228 <strchr+0x38>
.L138:
	addl	$2, %esi
  1012cd:	83 c6 02             	add    $0x2,%esi
	jmp	.L114
  1012d0:	e9 53 ff ff ff       	jmp    101228 <strchr+0x38>
.L139:
	addl	$3, %esi
  1012d5:	83 c6 03             	add    $0x3,%esi
	jmp	.L114
  1012d8:	e9 4b ff ff ff       	jmp    101228 <strchr+0x38>
  1012dd:	8d 76 00             	lea    0x0(%esi),%esi

001012e0 <strstr>:
/ C: char * strstr (const char *haystack, const char *needle)
.align 16
.globl	strstr
.type	strstr, @function
strstr:
	pushl	%ebp
  1012e0:	55                   	push   %ebp
	movl	%esp, %ebp
  1012e1:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  1012e3:	57                   	push   %edi
	pushl	%esi
  1012e4:	56                   	push   %esi
	pushl	%ebx
  1012e5:	53                   	push   %ebx
	subl	$76, %esp
  1012e6:	83 ec 4c             	sub    $0x4c,%esp
	movl	12(%ebp), %esi
  1012e9:	8b 75 0c             	mov    0xc(%ebp),%esi
	movl	8(%ebp), %edx
  1012ec:	8b 55 08             	mov    0x8(%ebp),%edx
	movsbl	(%esi), %eax
  1012ef:	0f be 06             	movsbl (%esi),%eax
	testb	%al, %al
  1012f2:	84 c0                	test   %al,%al
	je	.L172
  1012f4:	74 7a                	je     101370 <strstr+0x90>
	pushl	%eax
  1012f6:	50                   	push   %eax
	pushl	%edx
  1012f7:	52                   	push   %edx
	call	strchr
  1012f8:	e8 f3 fe ff ff       	call   1011f0 <strchr>
	popl	%ebx
  1012fd:	5b                   	pop    %ebx
	popl	%edi
  1012fe:	5f                   	pop    %edi
	movl	%eax, -44(%ebp)
  1012ff:	89 45 d4             	mov    %eax,-0x2c(%ebp)
	movl	%eax, %edi
  101302:	89 c7                	mov    %eax,%edi
	testl	%eax, %eax
  101304:	85 c0                	test   %eax,%eax
	je	.L140
  101306:	74 6b                	je     101373 <strstr+0x93>
	cmpb	$0, 1(%esi)
  101308:	80 7e 01 00          	cmpb   $0x0,0x1(%esi)
	je	.L140
  10130c:	74 65                	je     101373 <strstr+0x93>
	subl	$12, %esp
  10130e:	83 ec 0c             	sub    $0xc,%esp
	pushl	%esi
  101311:	56                   	push   %esi
	call	strlen
  101312:	e8 d9 f4 ff ff       	call   1007f0 <strlen>
	popl	%edx
  101317:	5a                   	pop    %edx
	popl	%ecx
  101318:	59                   	pop    %ecx
	movl	%eax, %ebx
  101319:	89 c3                	mov    %eax,%ebx
	leal	256(%eax), %eax
  10131b:	8d 80 00 01 00 00    	lea    0x100(%eax),%eax
	pushl	%eax
  101321:	50                   	push   %eax
	pushl	%edi
  101322:	57                   	push   %edi
	call	strnlen
  101323:	e8 1d f7 ff ff       	call   100a45 <strnlen>
	addl	$16, %esp
  101328:	83 c4 10             	add    $0x10,%esp
	movl	%eax, -48(%ebp)
  10132b:	89 45 d0             	mov    %eax,-0x30(%ebp)
	movl	%eax, %edi
  10132e:	89 c7                	mov    %eax,%edi
	cmpl	%eax, %ebx
  101330:	39 c3                	cmp    %eax,%ebx
	ja	.L173
  101332:	0f 87 16 01 00 00    	ja     10144e <strstr+0x16e>
	subl	$4, %esp
  101338:	83 ec 04             	sub    $0x4,%esp
	pushl	%ebx
  10133b:	53                   	push   %ebx
	pushl	%esi
  10133c:	56                   	push   %esi
	pushl	-44(%ebp)
  10133d:	ff 75 d4             	push   -0x2c(%ebp)
	call	memcmp
  101340:	e8 db f4 ff ff       	call   100820 <memcmp>
	addl	$16, %esp
  101345:	83 c4 10             	add    $0x10,%esp
	testl	%eax, %eax
  101348:	85 c0                	test   %eax,%eax
	je	.L140
  10134a:	74 27                	je     101373 <strstr+0x93>
	cmpl	$31, %ebx
  10134c:	83 fb 1f             	cmp    $0x1f,%ebx
	jbe	.L203
  10134f:	76 2d                	jbe    10137e <strstr+0x9e>
	movl	%ebx, 8(%ebp)
  101351:	89 5d 08             	mov    %ebx,0x8(%ebp)
	movl	-44(%ebp), %eax
  101354:	8b 45 d4             	mov    -0x2c(%ebp),%eax
	leal	-12(%ebp), %esp
  101357:	8d 65 f4             	lea    -0xc(%ebp),%esp
	movl	%esi, %ecx
  10135a:	89 f1                	mov    %esi,%ecx
	popl	%ebx
  10135c:	5b                   	pop    %ebx
	movl	%edi, %edx
  10135d:	89 fa                	mov    %edi,%edx
	popl	%esi
  10135f:	5e                   	pop    %esi
	popl	%edi
  101360:	5f                   	pop    %edi
	popl	%ebp
  101361:	5d                   	pop    %ebp
	jmp	two_way_long_needle
  101362:	e9 19 fa ff ff       	jmp    100d80 <two_way_long_needle>
  101367:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10136e:	66 90                	xchg   %ax,%ax
	.align 16
.L172:
	movl	%edx, -44(%ebp)
  101370:	89 55 d4             	mov    %edx,-0x2c(%ebp)
.L140:
	movl	-44(%ebp), %eax
  101373:	8b 45 d4             	mov    -0x2c(%ebp),%eax
	leal	-12(%ebp), %esp
  101376:	8d 65 f4             	lea    -0xc(%ebp),%esp
	popl	%ebx
  101379:	5b                   	pop    %ebx
	popl	%esi
  10137a:	5e                   	pop    %esi
	popl	%edi
  10137b:	5f                   	pop    %edi
	popl	%ebp
  10137c:	5d                   	pop    %ebp
	ret
  10137d:	c3                   	ret    
.L203:
	leal	-28(%ebp), %ecx
  10137e:	8d 4d e4             	lea    -0x1c(%ebp),%ecx
	movl	%ebx, %edx
  101381:	89 da                	mov    %ebx,%edx
	movl	%esi, %eax
  101383:	89 f0                	mov    %esi,%eax
	call	critical_factorization
  101385:	e8 76 f8 ff ff       	call   100c00 <critical_factorization>
	movl	-28(%ebp), %ecx
  10138a:	8b 4d e4             	mov    -0x1c(%ebp),%ecx
	subl	$4, %esp
  10138d:	83 ec 04             	sub    $0x4,%esp
	pushl	%eax
  101390:	50                   	push   %eax
	movl	%eax, %edi
  101391:	89 c7                	mov    %eax,%edi
	movl	%eax, -56(%ebp)
  101393:	89 45 c8             	mov    %eax,-0x38(%ebp)
	leal	(%esi,%ecx), %eax
  101396:	8d 04 0e             	lea    (%esi,%ecx,1),%eax
	pushl	%eax
  101399:	50                   	push   %eax
	pushl	%esi
  10139a:	56                   	push   %esi
	movl	%ecx, -76(%ebp)
  10139b:	89 4d b4             	mov    %ecx,-0x4c(%ebp)
	call	memcmp
  10139e:	e8 7d f4 ff ff       	call   100820 <memcmp>
	addl	$16, %esp
  1013a3:	83 c4 10             	add    $0x10,%esp
	testl	%eax, %eax
  1013a6:	85 c0                	test   %eax,%eax
	jne	.L195
  1013a8:	0f 85 b2 00 00 00    	jne    101460 <strstr+0x180>
	movl	$1, %eax
  1013ae:	b8 01 00 00 00       	mov    $0x1,%eax
	movl	$0, -52(%ebp)
  1013b3:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%ebp)
	xorl	%ecx, %ecx
  1013ba:	31 c9                	xor    %ecx,%ecx
	subl	%edi, %eax
  1013bc:	29 f8                	sub    %edi,%eax
	movl	%eax, -64(%ebp)
  1013be:	89 45 c0             	mov    %eax,-0x40(%ebp)
  1013c1:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1013c8:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1013cf:	90                   	nop
	.align 16
.L143:
	movl	-56(%ebp), %eax
  1013d0:	8b 45 c8             	mov    -0x38(%ebp),%eax
	movl	-44(%ebp), %edi
  1013d3:	8b 7d d4             	mov    -0x2c(%ebp),%edi
	movl	-52(%ebp), %edx
  1013d6:	8b 55 cc             	mov    -0x34(%ebp),%edx
	cmpl	%ecx, %eax
  1013d9:	39 c8                	cmp    %ecx,%eax
	cmovb	%ecx, %eax
  1013db:	0f 42 c1             	cmovb  %ecx,%eax
	addl	%edi, %edx
  1013de:	01 fa                	add    %edi,%edx
	movl	%ecx, %edi
  1013e0:	89 cf                	mov    %ecx,%edi
	cmpl	%eax, %ebx
  1013e2:	39 c3                	cmp    %eax,%ebx
	ja	.L145
  1013e4:	77 15                	ja     1013fb <strstr+0x11b>
	jmp	.L146
  1013e6:	e9 d7 01 00 00       	jmp    1015c2 <strstr+0x2e2>
  1013eb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  1013ef:	90                   	nop
	.align 16
.L147:
	addl	$1, %eax
  1013f0:	83 c0 01             	add    $0x1,%eax
	cmpl	%eax, %ebx
  1013f3:	39 c3                	cmp    %eax,%ebx
	je	.L199
  1013f5:	0f 84 c5 01 00 00    	je     1015c0 <strstr+0x2e0>
.L145:
	movzbl	(%edx,%eax), %ecx
  1013fb:	0f b6 0c 02          	movzbl (%edx,%eax,1),%ecx
	cmpb	%cl, (%esi,%eax)
  1013ff:	38 0c 06             	cmp    %cl,(%esi,%eax,1)
	je	.L147
  101402:	74 ec                	je     1013f0 <strstr+0x110>
	movl	%edi, %ecx
  101404:	89 f9                	mov    %edi,%ecx
	cmpl	%eax, %ebx
  101406:	39 c3                	cmp    %eax,%ebx
	jbe	.L146
  101408:	0f 86 b4 01 00 00    	jbe    1015c2 <strstr+0x2e2>
	movl	-52(%ebp), %edx
  10140e:	8b 55 cc             	mov    -0x34(%ebp),%edx
	addl	-64(%ebp), %edx
  101411:	03 55 c0             	add    -0x40(%ebp),%edx
	xorl	%ecx, %ecx
  101414:	31 c9                	xor    %ecx,%ecx
	addl	%edx, %eax
  101416:	01 d0                	add    %edx,%eax
	movl	%eax, -52(%ebp)
  101418:	89 45 cc             	mov    %eax,-0x34(%ebp)
.L154:
	movl	-52(%ebp), %eax
  10141b:	8b 45 cc             	mov    -0x34(%ebp),%eax
	movl	-48(%ebp), %edx
  10141e:	8b 55 d0             	mov    -0x30(%ebp),%edx
	leal	(%ebx,%eax), %edi
  101421:	8d 3c 03             	lea    (%ebx,%eax,1),%edi
	cmpl	%edx, %edi
  101424:	39 d7                	cmp    %edx,%edi
	jbe	.L143
  101426:	76 a8                	jbe    1013d0 <strstr+0xf0>
	movl	-44(%ebp), %eax
  101428:	8b 45 d4             	mov    -0x2c(%ebp),%eax
	subl	$8, %esp
  10142b:	83 ec 08             	sub    $0x8,%esp
	movl	%ecx, -60(%ebp)
  10142e:	89 4d c4             	mov    %ecx,-0x3c(%ebp)
	pushl	$512
  101431:	68 00 02 00 00       	push   $0x200
	addl	%edx, %eax
  101436:	01 d0                	add    %edx,%eax
	pushl	%eax
  101438:	50                   	push   %eax
	call	strnlen
  101439:	e8 07 f6 ff ff       	call   100a45 <strnlen>
	addl	%eax, -48(%ebp)
  10143e:	01 45 d0             	add    %eax,-0x30(%ebp)
	movl	-48(%ebp), %edx
  101441:	8b 55 d0             	mov    -0x30(%ebp),%edx
	addl	$16, %esp
  101444:	83 c4 10             	add    $0x10,%esp
	movl	-60(%ebp), %ecx
  101447:	8b 4d c4             	mov    -0x3c(%ebp),%ecx
	cmpl	%edx, %edi
  10144a:	39 d7                	cmp    %edx,%edi
	jbe	.L143
  10144c:	76 82                	jbe    1013d0 <strstr+0xf0>
.L173:
	movl	$0, -44(%ebp)
  10144e:	c7 45 d4 00 00 00 00 	movl   $0x0,-0x2c(%ebp)
	movl	-44(%ebp), %eax
  101455:	8b 45 d4             	mov    -0x2c(%ebp),%eax
	leal	-12(%ebp), %esp
  101458:	8d 65 f4             	lea    -0xc(%ebp),%esp
	popl	%ebx
  10145b:	5b                   	pop    %ebx
	popl	%esi
  10145c:	5e                   	pop    %esi
	popl	%edi
  10145d:	5f                   	pop    %edi
	popl	%ebp
  10145e:	5d                   	pop    %ebp
	ret
  10145f:	c3                   	ret    
.L195:
	movzbl	(%esi,%edi), %eax
  101460:	0f b6 04 3e          	movzbl (%esi,%edi,1),%eax
	movl	%esi, -52(%ebp)
  101464:	89 75 cc             	mov    %esi,-0x34(%ebp)
	movb	%al, -64(%ebp)
  101467:	88 45 c0             	mov    %al,-0x40(%ebp)
	movl	%ebx, %eax
  10146a:	89 d8                	mov    %ebx,%eax
	subl	%edi, %eax
  10146c:	29 f8                	sub    %edi,%eax
	cmpl	%edi, %eax
  10146e:	39 f8                	cmp    %edi,%eax
	cmovb	%edi, %eax
  101470:	0f 42 c7             	cmovb  %edi,%eax
	xorl	%ecx, %ecx
  101473:	31 c9                	xor    %ecx,%ecx
	movl	%ecx, %esi
  101475:	89 ce                	mov    %ecx,%esi
	addl	$1, %eax
  101477:	83 c0 01             	add    $0x1,%eax
	movl	%eax, -76(%ebp)
  10147a:	89 45 b4             	mov    %eax,-0x4c(%ebp)
	leal	1(%edi), %eax
  10147d:	8d 47 01             	lea    0x1(%edi),%eax
	movl	%eax, -60(%ebp)
  101480:	89 45 c4             	mov    %eax,-0x3c(%ebp)
	leal	-1(%edi), %eax
  101483:	8d 47 ff             	lea    -0x1(%edi),%eax
	movl	%eax, -72(%ebp)
  101486:	89 45 b8             	mov    %eax,-0x48(%ebp)
	movl	$1, %eax
  101489:	b8 01 00 00 00       	mov    $0x1,%eax
	subl	%edi, %eax
  10148e:	29 f8                	sub    %edi,%eax
	movl	%eax, -68(%ebp)
  101490:	89 45 bc             	mov    %eax,-0x44(%ebp)
  101493:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10149a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	.align 16
.L156:
	movl	-56(%ebp), %eax
  1014a0:	8b 45 c8             	mov    -0x38(%ebp),%eax
	movl	-44(%ebp), %edi
  1014a3:	8b 7d d4             	mov    -0x2c(%ebp),%edi
	movzbl	-64(%ebp), %ecx
  1014a6:	0f b6 4d c0          	movzbl -0x40(%ebp),%ecx
	addl	%esi, %eax
  1014aa:	01 f0                	add    %esi,%eax
	addl	%edi, %eax
  1014ac:	01 f8                	add    %edi,%eax
	leal	1(%eax), %edx
  1014ae:	8d 50 01             	lea    0x1(%eax),%edx
	cmpb	(%eax), %cl
  1014b1:	3a 08                	cmp    (%eax),%cl
	je	.L157
  1014b3:	74 22                	je     1014d7 <strstr+0x1f7>
	subl	$8, %esp
  1014b5:	83 ec 08             	sub    $0x8,%esp
	movzbl	%cl, %eax
  1014b8:	0f b6 c1             	movzbl %cl,%eax
	pushl	%eax
  1014bb:	50                   	push   %eax
	pushl	%edx
  1014bc:	52                   	push   %edx
	call	strchr
  1014bd:	e8 2e fd ff ff       	call   1011f0 <strchr>
	addl	$16, %esp
  1014c2:	83 c4 10             	add    $0x10,%esp
	movl	%eax, %edx
  1014c5:	89 c2                	mov    %eax,%edx
	testl	%eax, %eax
  1014c7:	85 c0                	test   %eax,%eax
	je	.L173
  1014c9:	74 83                	je     10144e <strstr+0x16e>
	movl	-56(%ebp), %eax
  1014cb:	8b 45 c8             	mov    -0x38(%ebp),%eax
	movl	%edx, %esi
  1014ce:	89 d6                	mov    %edx,%esi
	addl	$1, %edx
  1014d0:	83 c2 01             	add    $0x1,%edx
	addl	%edi, %eax
  1014d3:	01 f8                	add    %edi,%eax
	subl	%eax, %esi
  1014d5:	29 c6                	sub    %eax,%esi
.L157:
	movl	-60(%ebp), %eax
  1014d7:	8b 45 c4             	mov    -0x3c(%ebp),%eax
	cmpl	%eax, %ebx
  1014da:	39 c3                	cmp    %eax,%ebx
	jbe	.L158
  1014dc:	0f 86 7e 00 00 00    	jbe    101560 <strstr+0x280>
	movl	-52(%ebp), %edi
  1014e2:	8b 7d cc             	mov    -0x34(%ebp),%edi
	addl	$1, %edi
  1014e5:	83 c7 01             	add    $0x1,%edi
	jmp	.L161
  1014e8:	eb 0d                	jmp    1014f7 <strstr+0x217>
  1014ea:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	.align 16
.L159:
	addl	$1, %eax
  1014f0:	83 c0 01             	add    $0x1,%eax
	cmpl	%eax, %ebx
  1014f3:	39 c3                	cmp    %eax,%ebx
	jbe	.L158
  1014f5:	76 69                	jbe    101560 <strstr+0x280>
.L161:
	addl	$1, %edx
  1014f7:	83 c2 01             	add    $0x1,%edx
	movzbl	-1(%edx), %ecx
  1014fa:	0f b6 4a ff          	movzbl -0x1(%edx),%ecx
	cmpb	%cl, -1(%edi,%eax)
  1014fe:	38 4c 07 ff          	cmp    %cl,-0x1(%edi,%eax,1)
	je	.L159
  101502:	74 ec                	je     1014f0 <strstr+0x210>
	testb	%cl, %cl
  101504:	84 c9                	test   %cl,%cl
	je	.L173
  101506:	0f 84 42 ff ff ff    	je     10144e <strstr+0x16e>
	movl	-44(%ebp), %ecx
  10150c:	8b 4d d4             	mov    -0x2c(%ebp),%ecx
	addl	-48(%ebp), %ecx
  10150f:	03 4d d0             	add    -0x30(%ebp),%ecx
	cmpl	%ecx, %edx
  101512:	39 ca                	cmp    %ecx,%edx
	jbe	.L162
  101514:	76 06                	jbe    10151c <strstr+0x23c>
.L170:
	subl	-44(%ebp), %edx
  101516:	2b 55 d4             	sub    -0x2c(%ebp),%edx
	movl	%edx, -48(%ebp)
  101519:	89 55 d0             	mov    %edx,-0x30(%ebp)
.L162:
	cmpl	%eax, %ebx
  10151c:	39 c3                	cmp    %eax,%ebx
	jbe	.L171
  10151e:	76 4a                	jbe    10156a <strstr+0x28a>
	movl	-68(%ebp), %edi
  101520:	8b 7d bc             	mov    -0x44(%ebp),%edi
	leal	(%edi,%esi), %edx
  101523:	8d 14 37             	lea    (%edi,%esi,1),%edx
	leal	(%edx,%eax), %esi
  101526:	8d 34 02             	lea    (%edx,%eax,1),%esi
.L169:
	movl	-48(%ebp), %ecx
  101529:	8b 4d d0             	mov    -0x30(%ebp),%ecx
	leal	(%ebx,%esi), %edi
  10152c:	8d 3c 33             	lea    (%ebx,%esi,1),%edi
	cmpl	%edi, %ecx
  10152f:	39 f9                	cmp    %edi,%ecx
	jnb	.L156
  101531:	0f 83 69 ff ff ff    	jae    1014a0 <strstr+0x1c0>
	movl	-44(%ebp), %eax
  101537:	8b 45 d4             	mov    -0x2c(%ebp),%eax
	subl	$8, %esp
  10153a:	83 ec 08             	sub    $0x8,%esp
	pushl	$512
  10153d:	68 00 02 00 00       	push   $0x200
	addl	%ecx, %eax
  101542:	01 c8                	add    %ecx,%eax
	pushl	%eax
  101544:	50                   	push   %eax
	call	strnlen
  101545:	e8 fb f4 ff ff       	call   100a45 <strnlen>
	addl	%eax, -48(%ebp)
  10154a:	01 45 d0             	add    %eax,-0x30(%ebp)
	movl	-48(%ebp), %ecx
  10154d:	8b 4d d0             	mov    -0x30(%ebp),%ecx
	addl	$16, %esp
  101550:	83 c4 10             	add    $0x10,%esp
	cmpl	%ecx, %edi
  101553:	39 cf                	cmp    %ecx,%edi
	jbe	.L156
  101555:	0f 86 45 ff ff ff    	jbe    1014a0 <strstr+0x1c0>
	jmp	.L173
  10155b:	e9 ee fe ff ff       	jmp    10144e <strstr+0x16e>
	.align 16
.L158:
	movl	-44(%ebp), %ecx
  101560:	8b 4d d4             	mov    -0x2c(%ebp),%ecx
	addl	-48(%ebp), %ecx
  101563:	03 4d d0             	add    -0x30(%ebp),%ecx
	cmpl	%ecx, %edx
  101566:	39 ca                	cmp    %ecx,%edx
	ja	.L170
  101568:	77 ac                	ja     101516 <strstr+0x236>
.L171:
	movl	-72(%ebp), %eax
  10156a:	8b 45 b8             	mov    -0x48(%ebp),%eax
	leal	(%eax,%esi), %ecx
  10156d:	8d 0c 30             	lea    (%eax,%esi,1),%ecx
	cmpl	$-1, %eax
  101570:	83 f8 ff             	cmp    $0xffffffff,%eax
	je	.L164
  101573:	0f 84 b7 00 00 00    	je     101630 <strstr+0x350>
	movl	-52(%ebp), %edi
  101579:	8b 7d cc             	mov    -0x34(%ebp),%edi
	subl	-56(%ebp), %ecx
  10157c:	2b 4d c8             	sub    -0x38(%ebp),%ecx
	addl	-44(%ebp), %ecx
  10157f:	03 4d d4             	add    -0x2c(%ebp),%ecx
	subl	$1, %edi
  101582:	83 ef 01             	sub    $0x1,%edi
	jmp	.L167
  101585:	eb 12                	jmp    101599 <strstr+0x2b9>
  101587:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10158e:	66 90                	xchg   %ax,%ax
	.align 16
.L165:
	subl	$1, %eax
  101590:	83 e8 01             	sub    $0x1,%eax
	jb	.L164
  101593:	0f 82 97 00 00 00    	jb     101630 <strstr+0x350>
.L167:
	movzbl	1(%ecx,%eax), %edx
  101599:	0f b6 54 01 01       	movzbl 0x1(%ecx,%eax,1),%edx
	cmpb	%dl, 1(%edi,%eax)
  10159e:	38 54 07 01          	cmp    %dl,0x1(%edi,%eax,1)
	je	.L165
  1015a2:	74 ec                	je     101590 <strstr+0x2b0>
	testb	%dl, %dl
  1015a4:	84 d2                	test   %dl,%dl
	je	.L173
  1015a6:	0f 84 a2 fe ff ff    	je     10144e <strstr+0x16e>
	addl	-76(%ebp), %esi
  1015ac:	03 75 b4             	add    -0x4c(%ebp),%esi
	jmp	.L169
  1015af:	e9 75 ff ff ff       	jmp    101529 <strstr+0x249>
  1015b4:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1015bb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  1015bf:	90                   	nop
	.align 16
.L199:
	movl	%edi, %ecx
  1015c0:	89 f9                	mov    %edi,%ecx
.L146:
	movl	-56(%ebp), %eax
  1015c2:	8b 45 c8             	mov    -0x38(%ebp),%eax
	movl	-52(%ebp), %edi
  1015c5:	8b 7d cc             	mov    -0x34(%ebp),%edi
	subl	$1, %eax
  1015c8:	83 e8 01             	sub    $0x1,%eax
	leal	(%eax,%edi), %edx
  1015cb:	8d 14 38             	lea    (%eax,%edi,1),%edx
	subl	-56(%ebp), %edx
  1015ce:	2b 55 c8             	sub    -0x38(%ebp),%edx
	leal	-1(%esi), %edi
  1015d1:	8d 7e ff             	lea    -0x1(%esi),%edi
	addl	-44(%ebp), %edx
  1015d4:	03 55 d4             	add    -0x2c(%ebp),%edx
	movl	%edx, -60(%ebp)
  1015d7:	89 55 c4             	mov    %edx,-0x3c(%ebp)
	movl	-56(%ebp), %edx
  1015da:	8b 55 c8             	mov    -0x38(%ebp),%edx
	cmpl	%ecx, -56(%ebp)
  1015dd:	39 4d c8             	cmp    %ecx,-0x38(%ebp)
	jbe	.L150
  1015e0:	76 2b                	jbe    10160d <strstr+0x32d>
	movl	%esi, -68(%ebp)
  1015e2:	89 75 bc             	mov    %esi,-0x44(%ebp)
	movl	-60(%ebp), %esi
  1015e5:	8b 75 c4             	mov    -0x3c(%ebp),%esi
	movl	%ebx, -72(%ebp)
  1015e8:	89 5d b8             	mov    %ebx,-0x48(%ebp)
	jmp	.L149
  1015eb:	eb 0c                	jmp    1015f9 <strstr+0x319>
  1015ed:	8d 76 00             	lea    0x0(%esi),%esi
	.align 16
.L151:
	leal	-1(%eax), %edx
  1015f0:	8d 50 ff             	lea    -0x1(%eax),%edx
	cmpl	%eax, %ecx
  1015f3:	39 c1                	cmp    %eax,%ecx
	je	.L175
  1015f5:	74 49                	je     101640 <strstr+0x360>
	movl	%edx, %eax
  1015f7:	89 d0                	mov    %edx,%eax
.L149:
	movzbl	1(%eax,%esi), %ebx
  1015f9:	0f b6 5c 30 01       	movzbl 0x1(%eax,%esi,1),%ebx
	leal	1(%eax), %edx
  1015fe:	8d 50 01             	lea    0x1(%eax),%edx
	cmpb	%bl, 1(%edi,%eax)
  101601:	38 5c 07 01          	cmp    %bl,0x1(%edi,%eax,1)
	je	.L151
  101605:	74 e9                	je     1015f0 <strstr+0x310>
	movl	-68(%ebp), %esi
  101607:	8b 75 bc             	mov    -0x44(%ebp),%esi
	movl	-72(%ebp), %ebx
  10160a:	8b 5d b8             	mov    -0x48(%ebp),%ebx
.L150:
	leal	1(%ecx), %eax
  10160d:	8d 41 01             	lea    0x1(%ecx),%eax
	cmpl	%edx, %eax
  101610:	39 d0                	cmp    %edx,%eax
	ja	.L204
  101612:	77 36                	ja     10164a <strstr+0x36a>
	movl	-76(%ebp), %edi
  101614:	8b 7d b4             	mov    -0x4c(%ebp),%edi
	movl	%ebx, %ecx
  101617:	89 d9                	mov    %ebx,%ecx
	addl	%edi, -52(%ebp)
  101619:	01 7d cc             	add    %edi,-0x34(%ebp)
	subl	%edi, %ecx
  10161c:	29 f9                	sub    %edi,%ecx
	jmp	.L154
  10161e:	e9 f8 fd ff ff       	jmp    10141b <strstr+0x13b>
  101623:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10162a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	.align 16
.L164:
	addl	%esi, -44(%ebp)
  101630:	01 75 d4             	add    %esi,-0x2c(%ebp)
	movl	-44(%ebp), %eax
  101633:	8b 45 d4             	mov    -0x2c(%ebp),%eax
	leal	-12(%ebp), %esp
  101636:	8d 65 f4             	lea    -0xc(%ebp),%esp
	popl	%ebx
  101639:	5b                   	pop    %ebx
	popl	%esi
  10163a:	5e                   	pop    %esi
	popl	%edi
  10163b:	5f                   	pop    %edi
	popl	%ebp
  10163c:	5d                   	pop    %ebp
	ret
  10163d:	c3                   	ret    
  10163e:	66 90                	xchg   %ax,%ax
	.align 16
.L175:
	movl	-68(%ebp), %esi
  101640:	8b 75 bc             	mov    -0x44(%ebp),%esi
	movl	-72(%ebp), %ebx
  101643:	8b 5d b8             	mov    -0x48(%ebp),%ebx
	movl	%ecx, %edx
  101646:	89 ca                	mov    %ecx,%edx
	jmp	.L150
  101648:	eb c3                	jmp    10160d <strstr+0x32d>
.L204:
	movl	-52(%ebp), %esi
  10164a:	8b 75 cc             	mov    -0x34(%ebp),%esi
	addl	%esi, -44(%ebp)
  10164d:	01 75 d4             	add    %esi,-0x2c(%ebp)
	jmp	.L140
  101650:	e9 1e fd ff ff       	jmp    101373 <strstr+0x93>
  101655:	66 90                	xchg   %ax,%ax
  101657:	66 90                	xchg   %ax,%ax
  101659:	66 90                	xchg   %ax,%ax
  10165b:	66 90                	xchg   %ax,%ax
  10165d:	66 90                	xchg   %ax,%ax
  10165f:	90                   	nop

00101660 <memset>:
/ C: void *memset(void *s, int c, unsigned int n);
.align 16
.globl	memset
.type	memset, @function
memset:
	pushl	%ebp
  101660:	55                   	push   %ebp
	movl	%esp, %ebp
  101661:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  101663:	57                   	push   %edi
	pushl	%esi
  101664:	56                   	push   %esi
	pushl	%ebx
  101665:	53                   	push   %ebx
	subl	$28, %esp
  101666:	83 ec 1c             	sub    $0x1c,%esp
	movl	16(%ebp), %ebx
  101669:	8b 5d 10             	mov    0x10(%ebp),%ebx
	movl	8(%ebp), %esi
  10166c:	8b 75 08             	mov    0x8(%ebp),%esi
	cmpl	$11, %ebx
  10166f:	83 fb 0b             	cmp    $0xb,%ebx
	jbe	.L27
  101672:	76 7c                	jbe    1016f0 <memset+0x90>
	movzbl	12(%ebp), %edi
  101674:	0f b6 7d 0c          	movzbl 0xc(%ebp),%edi
	xorl	%eax, %eax
  101678:	31 c0                	xor    %eax,%eax
	movl	%esi, %ecx
  10167a:	89 f1                	mov    %esi,%ecx
	movl	%edi, %edx
  10167c:	89 fa                	mov    %edi,%edx
	sall	$8, %edx
  10167e:	c1 e2 08             	shl    $0x8,%edx
	orl	%edi, %edx
  101681:	09 fa                	or     %edi,%edx
	testl	%edi, %edi
  101683:	85 ff                	test   %edi,%edi
	cmove	%eax, %edx
  101685:	0f 44 d0             	cmove  %eax,%edx
	movl	%esi, %eax
  101688:	89 f0                	mov    %esi,%eax
	andl	$3, %ecx
  10168a:	83 e1 03             	and    $0x3,%ecx
	je	.L6
  10168d:	74 24                	je     1016b3 <memset+0x53>
	movl	$4, %eax
  10168f:	b8 04 00 00 00       	mov    $0x4,%eax
	leal	-4(%ecx,%ebx), %ebx
  101694:	8d 5c 19 fc          	lea    -0x4(%ecx,%ebx,1),%ebx
	subl	%ecx, %eax
  101698:	29 c8                	sub    %ecx,%eax
	movl	%eax, -28(%ebp)
  10169a:	89 45 e4             	mov    %eax,-0x1c(%ebp)
	je	.L8
  10169d:	74 0f                	je     1016ae <memset+0x4e>
	xorl	%ecx, %ecx
  10169f:	31 c9                	xor    %ecx,%ecx
.L7:
	movl	%edi, %eax
  1016a1:	89 f8                	mov    %edi,%eax
	movb	%al, (%esi,%ecx)
  1016a3:	88 04 0e             	mov    %al,(%esi,%ecx,1)
	addl	$1, %ecx
  1016a6:	83 c1 01             	add    $0x1,%ecx
	cmpl	-28(%ebp), %ecx
  1016a9:	3b 4d e4             	cmp    -0x1c(%ebp),%ecx
	jb	.L7
  1016ac:	72 f3                	jb     1016a1 <memset+0x41>
.L8:
	movl	-28(%ebp), %eax
  1016ae:	8b 45 e4             	mov    -0x1c(%ebp),%eax
	addl	%esi, %eax
  1016b1:	01 f0                	add    %esi,%eax
.L6:
	movl	%ebx, %ecx
  1016b3:	89 d9                	mov    %ebx,%ecx
	andl	$-4, %ecx
  1016b5:	83 e1 fc             	and    $0xfffffffc,%ecx
	addl	%eax, %ecx
  1016b8:	01 c1                	add    %eax,%ecx
  1016ba:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	.align 16
.L9:
	movl	%edx, (%eax)
  1016c0:	89 10                	mov    %edx,(%eax)
	addl	$4, %eax
  1016c2:	83 c0 04             	add    $0x4,%eax
	cmpl	%eax, %ecx
  1016c5:	39 c1                	cmp    %eax,%ecx
	jne	.L9
  1016c7:	75 f7                	jne    1016c0 <memset+0x60>
	andl	$3, %ebx
  1016c9:	83 e3 03             	and    $0x3,%ebx
	je	.L16
  1016cc:	74 0e                	je     1016dc <memset+0x7c>
	xorl	%eax, %eax
  1016ce:	31 c0                	xor    %eax,%eax
.L10:
	movl	%edi, %edx
  1016d0:	89 fa                	mov    %edi,%edx
	movb	%dl, (%ecx,%eax)
  1016d2:	88 14 01             	mov    %dl,(%ecx,%eax,1)
	addl	$1, %eax
  1016d5:	83 c0 01             	add    $0x1,%eax
	cmpl	%ebx, %eax
  1016d8:	39 d8                	cmp    %ebx,%eax
	jb	.L10
  1016da:	72 f4                	jb     1016d0 <memset+0x70>
.L16:
	leal	-12(%ebp), %esp
  1016dc:	8d 65 f4             	lea    -0xc(%ebp),%esp
	movl	%esi, %eax
  1016df:	89 f0                	mov    %esi,%eax
	popl	%ebx
  1016e1:	5b                   	pop    %ebx
	popl	%esi
  1016e2:	5e                   	pop    %esi
	popl	%edi
  1016e3:	5f                   	pop    %edi
	popl	%ebp
  1016e4:	5d                   	pop    %ebp
	ret
  1016e5:	c3                   	ret    
  1016e6:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1016ed:	8d 76 00             	lea    0x0(%esi),%esi
	.align 16
.L27:
	testl	%ebx, %ebx
  1016f0:	85 db                	test   %ebx,%ebx
	je	.L16
  1016f2:	74 e8                	je     1016dc <memset+0x7c>
	movzbl	12(%ebp), %eax
  1016f4:	0f b6 45 0c          	movzbl 0xc(%ebp),%eax
	subl	$4, %esp
  1016f8:	83 ec 04             	sub    $0x4,%esp
	pushl	%ebx
  1016fb:	53                   	push   %ebx
	pushl	%eax
  1016fc:	50                   	push   %eax
	pushl	%esi
  1016fd:	56                   	push   %esi
	call	memset
  1016fe:	e8 5d ff ff ff       	call   101660 <memset>
	addl	$16, %esp
  101703:	83 c4 10             	add    $0x10,%esp
	leal	-12(%ebp), %esp
  101706:	8d 65 f4             	lea    -0xc(%ebp),%esp
	movl	%esi, %eax
  101709:	89 f0                	mov    %esi,%eax
	popl	%ebx
  10170b:	5b                   	pop    %ebx
	popl	%esi
  10170c:	5e                   	pop    %esi
	popl	%edi
  10170d:	5f                   	pop    %edi
	popl	%ebp
  10170e:	5d                   	pop    %ebp
	ret
  10170f:	c3                   	ret    

00101710 <bzero>:
/ bzero: void bzero(void *s, unsigned int n);
.align 16
.globl	bzero
.type	bzero, @function
bzero:
	pushl	%ebp
  101710:	55                   	push   %ebp
	movl	%esp, %ebp
  101711:	89 e5                	mov    %esp,%ebp
	pushl	%edi
  101713:	57                   	push   %edi
	pushl	%esi
  101714:	56                   	push   %esi
	pushl	%ebx
  101715:	53                   	push   %ebx
	subl	$12, %esp
  101716:	83 ec 0c             	sub    $0xc,%esp
	movl	12(%ebp), %ebx
  101719:	8b 5d 0c             	mov    0xc(%ebp),%ebx
	movl	8(%ebp), %esi
  10171c:	8b 75 08             	mov    0x8(%ebp),%esi
	cmpl	$11, %ebx
  10171f:	83 fb 0b             	cmp    $0xb,%ebx
	jbe	.L51
  101722:	76 5c                	jbe    101780 <bzero+0x70>
	movl	%esi, %eax
  101724:	89 f0                	mov    %esi,%eax
	andl	$3, %eax
  101726:	83 e0 03             	and    $0x3,%eax
	je	.L31
  101729:	74 1c                	je     101747 <bzero+0x37>
	movl	$4, %edx
  10172b:	ba 04 00 00 00       	mov    $0x4,%edx
	leal	-4(%eax,%ebx), %ebx
  101730:	8d 5c 18 fc          	lea    -0x4(%eax,%ebx,1),%ebx
	subl	%eax, %edx
  101734:	29 c2                	sub    %eax,%edx
	je	.L33
  101736:	74 0d                	je     101745 <bzero+0x35>
	xorl	%eax, %eax
  101738:	31 c0                	xor    %eax,%eax
.L32:
	movb	$0, (%esi,%eax)
  10173a:	c6 04 06 00          	movb   $0x0,(%esi,%eax,1)
	addl	$1, %eax
  10173e:	83 c0 01             	add    $0x1,%eax
	cmpl	%edx, %eax
  101741:	39 d0                	cmp    %edx,%eax
	jb	.L32
  101743:	72 f5                	jb     10173a <bzero+0x2a>
.L33:
	addl	%edx, %esi
  101745:	01 d6                	add    %edx,%esi
.L31:
	movl	%ebx, %edi
  101747:	89 df                	mov    %ebx,%edi
	subl	$4, %esp
  101749:	83 ec 04             	sub    $0x4,%esp
	andl	$-4, %edi
  10174c:	83 e7 fc             	and    $0xfffffffc,%edi
	pushl	%edi
  10174f:	57                   	push   %edi
	pushl	$0
  101750:	6a 00                	push   $0x0
	pushl	%esi
  101752:	56                   	push   %esi
	addl	%edi, %esi
  101753:	01 fe                	add    %edi,%esi
	call	memset
  101755:	e8 06 ff ff ff       	call   101660 <memset>
	addl	$16, %esp
  10175a:	83 c4 10             	add    $0x10,%esp
	andl	$3, %ebx
  10175d:	83 e3 03             	and    $0x3,%ebx
	je	.L28
  101760:	74 0d                	je     10176f <bzero+0x5f>
	xorl	%eax, %eax
  101762:	31 c0                	xor    %eax,%eax
.L34:
	movb	$0, (%esi,%eax)
  101764:	c6 04 06 00          	movb   $0x0,(%esi,%eax,1)
	addl	$1, %eax
  101768:	83 c0 01             	add    $0x1,%eax
	cmpl	%ebx, %eax
  10176b:	39 d8                	cmp    %ebx,%eax
	jb	.L34
  10176d:	72 f5                	jb     101764 <bzero+0x54>
.L28:
	leal	-12(%ebp), %esp
  10176f:	8d 65 f4             	lea    -0xc(%ebp),%esp
	popl	%ebx
  101772:	5b                   	pop    %ebx
	popl	%esi
  101773:	5e                   	pop    %esi
	popl	%edi
  101774:	5f                   	pop    %edi
	popl	%ebp
  101775:	5d                   	pop    %ebp
	ret
  101776:	c3                   	ret    
  101777:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  10177e:	66 90                	xchg   %ax,%ax
	.align 16
.L51:
	testl	%ebx, %ebx
  101780:	85 db                	test   %ebx,%ebx
	je	.L28
  101782:	74 eb                	je     10176f <bzero+0x5f>
	subl	$4, %esp
  101784:	83 ec 04             	sub    $0x4,%esp
	pushl	%ebx
  101787:	53                   	push   %ebx
	pushl	$0
  101788:	6a 00                	push   $0x0
	pushl	%esi
  10178a:	56                   	push   %esi
	call	memset
  10178b:	e8 d0 fe ff ff       	call   101660 <memset>
	addl	$16, %esp
  101790:	83 c4 10             	add    $0x10,%esp
	leal	-12(%ebp), %esp
  101793:	8d 65 f4             	lea    -0xc(%ebp),%esp
	popl	%ebx
  101796:	5b                   	pop    %ebx
	popl	%esi
  101797:	5e                   	pop    %esi
	popl	%edi
  101798:	5f                   	pop    %edi
	popl	%ebp
  101799:	5d                   	pop    %ebp
	ret
  10179a:	c3                   	ret    
