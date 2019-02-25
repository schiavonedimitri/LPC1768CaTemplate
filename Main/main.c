/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.c
** Author: 				Dimitri Schiavone (schiavone.dimitri.2@gmail.com)
** Last modified Date:  2019-02-23
** Last Version:        V1.00
** Descriptions:        main file of the project from which the system jumps after init
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
                  
#include <stdio.h>
#include "LPC17xx.h" 
#include "../Button/button.h"
#include "../Timer/timer.h"
#include "../Rit/rit.h"
#include "../Led/led.h"
#include "../Joystick/joystick.h"

/*----------------------------------------------------------------------------
  main function, this is where the system jumps after init and after reset
 *----------------------------------------------------------------------------*/
 
int main (void) {
	SystemInit();
	initRit(0x4C4B40);
	enableRit();
	powerOnTimer(1);
	initTimer(T1MR0RST, 0xEE6B280);								/* k = time(secs)*frequency(1/secs) where k is the number we want to set the timer to count to */
	enableTimer(1);
  buttonInit();
	joystickInit();
	ledInit();
	LPC_SC->PCON |= 0x1;													/* power-down	mode */
	LPC_SC->PCON &= ~(0x2);	
	
   while(1){
	   __ASM("wfi");															/* The system is in power-down mode and listents for enabled interrupts */
  }
}
