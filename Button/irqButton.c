#include "button.h"
#include "lpc17xx.h"
#include "../Button/button.h"

int down0  = 0;
int down1 = 0;
int down2 = 0;

/*----------------------------------------------------------------------------
  The registers that control the flags of external interrupts is in the system
	control block, register EXTINT(External interrupt flag register) writing
	1s in the right position in this register clears the corresponding interrupt
 *----------------------------------------------------------------------------*/


void EINT0_IRQHandler (void){			/* This handler is currently managing the button INT0 */
	buttonDisableIrq(INT0);
	buttonSetMode(INT0GPIO);
	int0Counter=1;													
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt EINT0 */
}

void EINT1_IRQHandler(void)	  	/* This handler is currently managing the button KEY1 */
{
	buttonDisableIrq(KEY1);
	buttonSetMode(KEY1GPIO);
	key1Counter=1;													
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt EINT1    */
}

void EINT2_IRQHandler(void)	  	/* This handler is currently managing the button KEY2 */
{
	buttonDisableIrq(KEY2);
	buttonSetMode(KEY2GPIO);
	key2Counter=1;													
	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt EINT1*/
}


