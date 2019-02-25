#include "lpc17xx.h"
#include "rit.h"
#include "../Button/button.h"
#include "../Joystick/joystick.h"
#include "../led/led.h"

void RIT_IRQHandler(void){
	/* INT0 managing */
	if(int0Counter!=0){
		if(buttonReadPin(0)){
			int0Counter++;				
			switch(int0Counter){
				case 2:
					//your action here
					break;
				default:
					break;
			}
		}
		else{
			int0Counter=0;			
			buttonEnableIrq(0);							 
			buttonSetMode(INT0EINT);    
		}
	}
	/* KEY1 managing */
	if(key1Counter!=0){
		if(buttonReadPin(1)){
			key1Counter++;				
			switch(key1Counter){
				case 2:
					//your action here
					break;
				default:
					break;
			}
		}
		else{
			key1Counter=0;			
			buttonEnableIrq(1);							 
			buttonSetMode(KEY1EINT);    
		}
	}
	/* KEY2 managing */
	if(key2Counter!=0){
		if(buttonReadPin(2)){
			key2Counter++;				
			switch(key2Counter){
				case 2:
					//your action here
					break;
				default:
					break;
			}
		}
		else{
			key2Counter=0;			
			buttonEnableIrq(2);							 
			buttonSetMode(KEY2EINT);    
		}
	}
	/* joystick select management */
	if(!(LPC_GPIO1->FIOPIN & (1<<JBITSELECT))){
		jSelectCounter++;
		onSelectPressed();
	}
	/* joystick down management */
	if(!(LPC_GPIO1->FIOPIN & (1<<JBITDOWN))){
		jDownCounter++;
		onDownPressed();
	}
	/* joystick left management */
	if(!(LPC_GPIO1->FIOPIN & (1<<JBITLEFT))){
		jLeftCounter++;
		onLeftPressed();
	}
	/* joystick right management */
	if(!(LPC_GPIO1->FIOPIN & (1<<JBITRIGHT))){
		jRightCounter++;
		onRightPressed();
	}
	/* joystick up management */
	if(!(LPC_GPIO1->FIOPIN & (1<<JBITUP))){
		jUpCounter++;
		onUpPressed();
	}
  LPC_RIT->RICTRL |= 0x1;								/* clear interrupt flag */
}

