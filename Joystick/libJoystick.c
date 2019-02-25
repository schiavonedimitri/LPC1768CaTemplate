/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2019-02-24
** Last Version:        V1.00
** Descriptions:        Joystick init functions
** Correlated files:    libJoystick.c, functJoystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes the joystick by setting the pins to which it
	is connected to GPIO mode with input direction.
 *----------------------------------------------------------------------------*/

void joystickInit(void){
	LPC_PINCON->PINSEL3 &= ~(3<<PCONBP125);				/* P1.25 GPIO Mode */
	LPC_PINCON->PINSEL3 &= ~(3<<PCONBP126);				/* P1.26 GPIO Mode */
	LPC_PINCON->PINSEL3 &= ~(3<<PCONBP127);				/* P1.27 GPIO Mode */
	LPC_PINCON->PINSEL3 &= ~(3<<PCONBP128);				/* P1.28 GPIO Mode */
	LPC_PINCON->PINSEL3 &= ~(3<<PCONBP129); 			/* P1.29 GPIO Mode */
	LPC_GPIO1->FIODIR   &= ~(1<<JBITSELECT);	    /* P1.25 as INPUT  */
	LPC_GPIO1->FIODIR   &= ~(1<<JBITDOWN);	      /* P1.26 as INPUT  */
	LPC_GPIO1->FIODIR   &= ~(1<<JBITLEFT);			  /* P1.27 as INPUT  */
	LPC_GPIO1->FIODIR   &= ~(1<<JBITRIGHT);			  /* P1.28 as INPUT  */
	LPC_GPIO1->FIODIR   &= ~(1<<JBITUP);				  /* P1.29 as INPUT  */
}

/*----------------------------------------------------------------------------
  This function returns the value read at the the pin of the specified button.
	The buttons are active low and the function returns 1 if any of the buttons
  reads a 0 value at that pin. So if(joystickButtonReadPin(0)){button pressed}
	The function returns 2 in case the argument is not valid.
 *----------------------------------------------------------------------------*/

uint8_t joystickButtonReadPin(uint8_t button){
	uint8_t retCode = 0;
	switch(button){
		case JSELECT:
			if(!(LPC_GPIO1->FIOPIN & (1<<JBITSELECT))){
				retCode = 1;
			}
			break;
		case JDOWN:
			if(!(LPC_GPIO1->FIOPIN & (1<<JBITDOWN))){
				retCode = 1;
			} 
			break;
		case JLEFT:
			if(!(LPC_GPIO1->FIOPIN & (1<<JBITLEFT))){
				retCode = 1;
			}
		case JRIGHT:
			if(!(LPC_GPIO1->FIOPIN & (1<<JBITRIGHT))){
				retCode = 1;
			}
		case JUP:
			if(!(LPC_GPIO1->FIOPIN & (1<<JBITUP))){
				retCode = 1;
			}
			break;
		default:
			return 2;
	}
	return retCode;
}
