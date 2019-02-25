#include "lpc17xx.h"
#include "rit.h"

void enableRit(void)
{
  LPC_RIT->RICTRL |= (1<<3);	
  return;
}

void disableRit(void)
{
	LPC_RIT->RICTRL &= ~(1<<3);	
  return;
}

void resetRit(void)
{
  LPC_RIT->RICOUNTER = 0;          					/* Set RIT counter value to 0 */
  return;
}

uint32_t initRit(uint32_t interval){
  LPC_SC->PCLKSEL1  &= ~(3<<26);						/* Set RIT clock to CCLK/4 = 100Mhz/4 = 25Mhz*/				
  LPC_SC->PCLKSEL1  |=  (1<<26); 						/* Set RIT clock to CCLK = 100Mhz*/
	LPC_SC->PCONP     |=  (1<<16);   
	LPC_RIT->RICOMPVAL = interval;      
	LPC_RIT->RICTRL    = (1<<1);		
	LPC_RIT->RICOUNTER = 0;          
	NVIC_EnableIRQ(RIT_IRQn);
  return(0);
}

