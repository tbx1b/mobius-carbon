#include <libcarbon/hal.h>
#include <libcarbon/core.h>
#include <libcarbon/assert.h>
#include <libc/stdint.h>

#define I86_PIC1_REG_COMMAND		0x20
#define I86_PIC1_REG_STATUS			0x20
#define I86_PIC1_REG_DATA			0x21
#define I86_PIC1_REG_IMR			0x21
#define I86_PIC2_REG_COMMAND		0xA0
#define I86_PIC2_REG_STATUS			0xA0
#define I86_PIC2_REG_DATA			0xA1
#define I86_PIC2_REG_IMR			0xA1


/**
 * @brief      This routine sends a command byte to the PIC's command register.
 *
 * @param[in]  cmd     The command
 * @param[in]  pic_id  The PIC identifier
 */
inline 
MLTX_API void 
_os_pic_send_cmd(
	uint8_t cmd, 
	uint8_t pic_id) 
{
	assert(pic_id <= 1);

	uint8_t r = (pic_id == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;
	outb(r, cmd);
	return;
}

/**
 * @brief      Send data to a pic
 *
 * @param[in]  data    The data
 * @param[in]  pic_id  The PIC identifier
 */
inline 
MLTX_API void
_os_pic_send_dat(
	uint8_t data,
	uint8_t pic_id)
{
	assert(pic_id <= 1);

	uint8_t r = (pic_id == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	outb(r, data);
	return;
}

/**
 * @brief      Request data from the PIC
 *
 * @param[in]  pic_id  The PIC identifier
 *
 * @return     the data
 */
inline 
MLTX_API uint8_t
_os_pic_request_dat(
	uint8_t pic_id)
{
	assert(pic_id <= 1);
	uint8_t r = (pic_id == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
}

/**
 * @brief      Initialize the PIC
 *
 * @param[in]  b00   The b 00
 * @param[in]  b01   The b 01
 */
MLTX_API void 
_os_pic_init(
	uint8_t b00, uint8_t b01)
{
	uint8_t icw = 0;
	/* init PIC */
	icw = (icw & ~I86_PIC_ICW1_MASK_INIT) | I86_PIC_ICW1_INIT_YES;
	icw = (icw & ~I86_PIC_ICW1_MASK_IC4)  | I86_PIC_ICW1_IC4_EXPECT;

	_os_pic_send_cmd(icw, 0);
	_os_pic_send_cmd(icw, 1);

	/* send init ctrl word $2 */

	_os_pic_send_dat(b00, 0);
	_os_pic_send_dat(b01, 1);

	/* icw 3: Master PIC  -> decimal, Slave PIC -> binary */

	_os_pic_send_dat(0x04, 0);
	_os_pic_send_dat(0x02, 1);

	/* icw 4, i86pc mode */

	icw = (icw & ~I86_PIC_ICW4_MASK_UPM) | I86_PIC_ICW4_UPM_86MODE;

	_os_pic_send_dat(icw, 0);
	_os_pic_send_dat(icw, 1);

	return;
}
/*! EOF */