/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           button.h
** Author: 							Dimitri Schiavone (schiavone.dimitri.2@gmail.com)
** Last modified Date:  2019-02-24
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in libTimer, functTimer, irqTimer .c files
												and constants definitions
** Related files:    		libButton.c, functButton.c, irqButton.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

/*----------------------------------------------------------------------------
  Buttons port and pins configuration
	Layout of the buttons as seen on the physical board:
  [KEY1][KEY2][INT0][RESET]
	P2.10-->INT0
	P2.11-->KEY1
	p2.12-->KEY2
	The buttons are connected to the port 2 of the system to the pins
	P2.10, P2.11, P2.12
	The functionality of these pins is managed by the pin connect block
	register PINSEL4.
	The relationship between PINSEL4 register and port pins is the following:
	P2.10-->PINSEL4[21-20]
	P2.11-->PINSEL4[23-22]
	P2.12-->PINSEL4[25-24]
	Each pair of bits of the PINSEL4 register specifies the corresponding
	pin functionality or mode.
	For the buttons we usually are interested in the EINT functionality to
	manage the pression event through interrupts, but when it's needed
	these pins can also be setup to GPIO mode. The following table shows
	the possible modes for these pins (the ones we are interested in, see
	the manual for other functions):
	P2.10-->PINSEL4[21-20]==[00]-->GPIO
	P2.11-->PINSEL4[23-22]==[00]-->GPIO
	P2.12-->PINSEL4[25-24]==[00]-->GPIO
	If GPIO mode is selected we need to setup the direction of the pins to be either input or output.
	We can do so by setting the FIODIR register in the GPIO2 block.
	P2.10-->GPIO2-->FIODIR[10]==0-->INPUT
	P2.10-->GPIO2-->FIODIR[11]==0-->INPUT
	P2.10-->GPIO2-->FIODIR[12]==0-->INPUT
	P2.10-->GPIO2-->FIODIR[10]==1-->OUTPUT
	P2.10-->GPIO2-->FIODIR[11]==1-->OUTPUT
	P2.10-->GPIO2-->FIODIR[12]==1-->OUTPUT
	In GPIO mode we can read the status of the pins, the buttons as per the schematic are all active low.
	For example to know if the INT0 button has been pressed we can do as following:
	if(!(LPC_GPIO2->FIOPIN & (1<<11)) --> INT0 button has been pressed.
	NOTE1: to get the value of the pin into a variable you need to shift the bit you got in the previous expression
	by the right amount to get it into the least significant position(assuming you need 1 bit, otherise you shift less)
	and and it with a mask of 0s where you want to clear unneeded bits and 1s where you want to keep the bits.
	NOTE2: if these pins are in EINT mode apparently you cannot read their value, so remember to put them in GPIO
	mode before reading them.	
	NOTE3: due to electrical things and because the buttons are low quality and are not hardware debounced
	we might want to debounce them by setting up a RIT timer to count for 50ms after a button has been pressed
	and so the first time we enter the handler of a button press EINTX_IRQHandler() we disable the handler relative
	to the current button and start the rit. In the RIT handler when it triggers(50ms after a button has been pushed)
	we can do some checks and finally assert that the button has really been pressed and do accordingly and re-enable the
	EINTX_IRQHandler() to make the button reactive to new pressures.
	NOTE4: The joystick is an example of hardware debounced device (although its pins cannot be configured as EINTX)
	P2.10-->PINSEL4[21-20]==[01]-->EINT0
	P2.11-->PINSEL4[23-22]==[01]-->EINT1
	P2.12-->PINSEL4[25-24]==[01]-->EINT2
	If the pins are configured to EINT mode the manual says that the hardware manages by itself the direction
	of the pins so we shouldn't worry.
 *----------------------------------------------------------------------------*/

#ifndef __BUTTON_H
#define __BUTTON_H

#include "LPC17xx.h"

#define PCONBP210 20				/* INT0 */
#define PCONBP211	22				/* KEY1 */
#define PCONBP212 24				/* KEY2 */

#define INT0BITS 10
#define KEY1BITS 11
#define KEY2BITS 12

#define INT0 0
#define KEY1 1
#define KEY2 2

#define INT0GPIO 0x0
#define KEY1GPIO 0x1
#define KEY2GPIO 0x2
#define INT0EINT 0x4
#define KEY1EINT 0x5
#define KEY2EINT 0x6

/*----------------------------------------------------------------------------
  These variables are declared in the file rit.h to mitigate the effects of
	the bouncing of the buttons
 *----------------------------------------------------------------------------*/

extern int int0Counter;
extern int key1Counter;
extern int key2Counter;

/* libButton.c */

void buttonInit(void);
uint8_t buttonSetMode(uint8_t flags);
uint8_t buttonEnableIrq(uint8_t button);
uint8_t buttonDisableIrq(uint8_t button);
uint8_t buttonSetIrqPriority(uint8_t button, uint32_t priority);
uint8_t buttonReadPin(uint8_t button);

/* irqButton.c */

void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);

#endif
