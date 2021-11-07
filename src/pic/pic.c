#include <hali86pc/pic.h>

void
pic_init(unsigned char master_base, unsigned char slave_base)
{
	/* Initialize the master. */
	outb_p(MASTER_ICW, PICM_ICW1);
	outb_p(MASTER_OCW, master_base);
	outb_p(MASTER_OCW, PICM_ICW3);
	outb_p(MASTER_OCW, PICM_ICW4);

	/* Initialize the slave. */
	outb_p(SLAVES_ICW, PICS_ICW1);
	outb_p(SLAVES_OCW, slave_base);
	outb_p(SLAVES_OCW, PICS_ICW3);
	outb_p(SLAVES_OCW, PICS_ICW4);

	/* Ack any bogus intrs by setting the End Of Interrupt bit. */
	outb_p(MASTER_ICW, NON_SPEC_EOI);
	outb_p(SLAVES_ICW, NON_SPEC_EOI);
}