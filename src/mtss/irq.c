/******************************************************************************************
 * 
 * ---- MODES: 		LEVEL TRIGGERED
 * 				*
 * 				* _____-------____
 * 				*     ^      ^
 * 				*.  signal. irq. (waits for irq)
 * 
 * ---- 		EDGE TRIGGERED
 * 				*
 * 				* ______-___________ ... irq will come...
 * 				*	^
 * 				*	signal. (doesn't wait)
 * 
 * ----			HYBRID
 * 				*
 * 				* Check for the NMI on the CPU.
 * 				*
 * 				*
 * 
 ******************************************************************************************/

// Registers:

/*
 * - Command Registers				This is a write only register that is used 
 *						to send commands to the microcontroller.
 *
 * - Interrupt Request Register (IRR)  		This register specifies
 *						which interrupts are pending acknowledgment.
 *
 * - In-Sevice Register (ISR)			This register specifies which interrupts 
 * 						have already been acknowledged, but are 
 *						awaiting for the End of Interrupt (EOI)
 *
 * - Interrupt Mask Register (IMR)			
 *
 */