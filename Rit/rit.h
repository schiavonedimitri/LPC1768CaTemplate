/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           rit.h
** Last modified Date:  2019-02-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_RIT, funct_RIT, IRQ_RIT .c files
** Correlated files:    libRit.c, irqRit.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

/*----------------------------------------------------------------------------
	At system boot or reset the RIT timer is powered off, so you need to enable
	it by setting to 1 the 16th bit in the PCONP register.
	At system boot or reset the RIT timer uses by default CCLK/4, to use a 
	different clock divider you need to set the correct bits in PCLKSEL1.
	PCONP-->[16] = 0 -->RIT powered off
	PCONP-->[16] = 1 -->RIT powered on
	PCLKSEL-->[27-26] = 00 --> RIT clock = CCLK/4
	PCLKSEL-->[27-26] = 01 --> RIT clock = CCLK
	PCLKSEL-->[27-26] = 10 --> RIT clock = CCLK/2
	PCLKSEL-->[27-26] = 00 --> RIT clock = CCLK/8
	NOTE: at system boot or reset the system CCLK = 100Mhz
	NOTE2: to calculate the value k to set a counter to count for x seconds you
	can use this formula:
	k = x* CLOCK
	e.g. count 10 seconds with a reference clock of 25Mhz
	k = 10*25*10^6 = 0x?EE6B280? which is the value to set the timer to count
	to.
 *----------------------------------------------------------------------------*/

#ifndef __RIT_H
#define __RIT_H

extern int int0Counter;
extern int key1Counter;
extern int key2Counter;
extern int jSelectCounter;
extern int jDownCounter;
extern int jLeftCounter;
extern int jRightCounter;
extern int jUpCounter;

/* initRit.c */
uint32_t initRit(uint32_t interval);
void enableRit(void);
void disableRit(void);
void resetRit(void);

/* irqRit.c */
void RIT_IRQHandler(void);

#endif 
