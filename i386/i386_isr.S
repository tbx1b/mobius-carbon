/*===---- io.S - IDT assembly stubs ----------------------------------------===
 *
 * Part of the Carbon kernel, under the GNU GPL v3.0 license.
 * See https://www.gnu.org/licenses/gpl-3.0.en.html
 * for license inFormation.
 *
 *===-----------------------------------------------------------------------===
 */

/*
 * TODO: Learn how to fucking use assembler macro loops. Anyways...
 * it just werks.
 */

#include <machine/asm.h>

ISR_NO_EXCEPT(0)
ISR_NO_EXCEPT(1)
ISR_NO_EXCEPT(2)
ISR_NO_EXCEPT(3)
ISR_NO_EXCEPT(4)
ISR_NO_EXCEPT(5)
ISR_NO_EXCEPT(6)
ISR_NO_EXCEPT(7)
ISR          (8)
ISR_NO_EXCEPT(9)
ISR          (10)
ISR          (11)
ISR          (12)
ISR          (13)
ISR          (14)
ISR_NO_EXCEPT(15)
ISR_NO_EXCEPT(16)
ISR          (17)
ISR_NO_EXCEPT(18)
ISR_NO_EXCEPT(19)
ISR_NO_EXCEPT(20)
ISR_NO_EXCEPT(21)
ISR_NO_EXCEPT(22)
ISR_NO_EXCEPT(23)
ISR_NO_EXCEPT(24)
ISR_NO_EXCEPT(25)
ISR_NO_EXCEPT(26)
ISR_NO_EXCEPT(27)
ISR_NO_EXCEPT(28)
ISR_NO_EXCEPT(29)
ISR          (30)
ISR_NO_EXCEPT(31)

.align 0x20
DSYM(stubs)
GLOB(stubs)

.int isr_stub_0
.int isr_stub_1
.int isr_stub_2
.int isr_stub_3
.int isr_stub_4
.int isr_stub_5
.int isr_stub_6
.int isr_stub_7
.int isr_stub_8
.int isr_stub_9
.int isr_stub_10
.int isr_stub_11
.int isr_stub_12
.int isr_stub_13
.int isr_stub_14
.int isr_stub_15
.int isr_stub_16
.int isr_stub_17
.int isr_stub_18
.int isr_stub_19
.int isr_stub_20
.int isr_stub_21
.int isr_stub_22
.int isr_stub_23
.int isr_stub_24
.int isr_stub_25
.int isr_stub_26
.int isr_stub_27
.int isr_stub_28
.int isr_stub_29
.int isr_stub_30
.int isr_stub_31
// eof