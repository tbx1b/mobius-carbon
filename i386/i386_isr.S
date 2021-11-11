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

.extern exstub

ISR_NO_EXCEPT(00)
ISR_NO_EXCEPT(01)
ISR_NO_EXCEPT(02)
ISR_NO_EXCEPT(03)
ISR_NO_EXCEPT(04)
ISR_NO_EXCEPT(05)
ISR_NO_EXCEPT(06)
ISR_NO_EXCEPT(07)
ISR          (08)
ISR_NO_EXCEPT(09)
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

.int isr_stub_00
.int isr_stub_01
.int isr_stub_02
.int isr_stub_03
.int isr_stub_04
.int isr_stub_05
.int isr_stub_06
.int isr_stub_07
.int isr_stub_08
.int isr_stub_09
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