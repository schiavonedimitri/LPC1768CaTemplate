#include "button.h"
#include "lpc17xx.h"

int int0Counter = 0;
int key1Counter = 0;
int key2Counter = 0;

/*----------------------------------------------------------------------------
  Function that initializes the buttons by setting them in EINT mode
	with direction as INPUT with interrupts enabled and set to a predefined
	priority level
 *----------------------------------------------------------------------------*/

void buttonInit(void) {
	buttonSetMode(INT0EINT);
	buttonSetMode(KEY1EINT);
	buttonSetMode(KEY2EINT);
	LPC_SC->EXTMODE = 0x7;
	buttonEnableIrq(INT0);
	buttonEnableIrq(KEY1);
	buttonEnableIrq(KEY2);
	buttonSetIrqPriority(INT0, 0);
	buttonSetIrqPriority(KEY1, 1);
	buttonSetIrqPriority(KEY2, 2);
}

/*----------------------------------------------------------------------------
  This function returns the value read at the the pin of the specified button.
	The buttons are active low and the function returns 1 if any of the buttons
  reads a 0 value at that pin. So if(buttonReadPin(0)){button pressed}
	The function returns 2 in case the argument is not valid.
 *----------------------------------------------------------------------------*/

uint8_t buttonReadPin(uint8_t button){
	uint8_t retCode = 0;
	switch(button){
		case 0:
			if(!(LPC_GPIO2->FIOPIN & (1<<INT0BITS))){
				retCode = 1;
			}
			break;
		case 1:
			if(!(LPC_GPIO2->FIOPIN & (1<<KEY1BITS))){
				retCode = 1;
			} 
			break;
		case 2:
			if(!(LPC_GPIO2->FIOPIN & (1<<KEY2BITS))){
				retCode = 1;
			}
			break;
		default:
			return 2;
	}
	return retCode;
}

uint8_t buttonEnableIrq(uint8_t button){
	switch(button){
		case INT0:
			NVIC_EnableIRQ(EINT0_IRQn);
			break;
		case KEY1:
			NVIC_EnableIRQ(EINT1_IRQn); 
			break;
		case KEY2:
			NVIC_EnableIRQ(EINT2_IRQn);
			break;
		default:
			return 0;
	}
	return 1;
}

uint8_t buttonDisableIrq(uint8_t button){
	switch(button){
		case INT0:
			NVIC_DisableIRQ(EINT0_IRQn);
			break;
		case KEY1:
			NVIC_DisableIRQ(EINT1_IRQn);
			break;
		case KEY2:
			NVIC_DisableIRQ(EINT2_IRQn);
			break;
		default:
			return 0;
	}
	return 1;
}

uint8_t buttonSetIrqPriority(uint8_t button, uint32_t priority){
	switch(button){
		case INT0:
			NVIC_SetPriority(EINT0_IRQn, priority);
			break;
		case KEY1:
			NVIC_SetPriority(EINT1_IRQn, priority); 
			break;
		case KEY2:
			NVIC_SetPriority(EINT2_IRQn, priority);
			break;
		default:
			return 0;
	}
	return 1;
}


uint8_t buttonSetMode(uint8_t flags){
	uint8_t button = 0x3 & flags;
	uint8_t mode = 0x1 & flags >> 2;
	switch(button){
		case 0:
			if(mode == 0){
				LPC_PINCON->PINSEL4 &= ~(1 << PCONBP210);				/* pin 2.10 set as GPIO  */
				LPC_GPIO2->FIODIR      &= ~(1 << INT0BITS);					/* pin 2.10 set as INPUT */
			}
			else if(mode == 1){
				LPC_PINCON->PINSEL4    |= (1 << PCONBP210);			/* pin 2.10 set as Eternal Interrupt 0 */
				LPC_GPIO2->FIODIR      &= ~(1 << INT0BITS);					/* pin 2.10 set as INPUT */
			}
			break;
		case 1:
			if(mode == 0){
				LPC_PINCON->PINSEL4 &= ~(1 << PCONBP211);				/* pin 2.11 set as GPIO  */
				LPC_GPIO2->FIODIR      &= ~(1 << KEY1BITS);					/* pin 2.11 set as INPUT */
			}
			else if(mode == 1){
				LPC_PINCON->PINSEL4    |= (1 << PCONBP211);			/* pin 2.11 set as External Interrupt 1 */
				LPC_GPIO2->FIODIR      &= ~(1 << KEY1BITS);					/* pin 2.11 set as INPUT */
			}
			break;
		case 2:
			if(mode == 0){
				LPC_PINCON->PINSEL4 &= ~(1 << PCONBP212); 			/* pin 2.12 set as GPIO  */
				LPC_GPIO2->FIODIR      &= ~(1 << KEY2BITS);						/* pin 2.12 set as INPUT */
			}
			else if(mode == 1){
				LPC_PINCON->PINSEL4    |= (1 << PCONBP212);			/* pin 2.12 set as External Interrupt 2 */
				LPC_GPIO2->FIODIR      &= ~(1 << KEY2BITS);						/* pin 2.12 set as INPUT */
			}
			break;
		default:
			return 0;
	}
	return 1;
}
