#include "lpc17xx.h"
#include "timer.h"

/*----------------------------------------------------------------------------
  Function that powers on the timer specified by timerNum
	Returns 1 if the argument is valid, 0 otherwise
 *----------------------------------------------------------------------------*/

uint8_t powerOnTimer(uint8_t timerNum){
	switch(timerNum){
		case 0:
			LPC_SC->PCONP |= 1<<1;
		  LPC_SC->PCLKSEL0  &= ~(3<<1);				/* Set TIMER0 clock to CCLK/4 = 100Mhz/4 = 25Mhz*/
			break;				
		case 1:
			LPC_SC->PCONP |= 1<<2;
			LPC_SC->PCLKSEL1  &= ~(3<<3);				/* Set TIMER1 clock to CCLK/4 = 100Mhz/4 = 25Mhz*/
			break;
		case 2:
			LPC_SC->PCONP |= 1<<22;
			LPC_SC->PCLKSEL1  &= ~(3<<11);			/* Set TIMER2 clock to CCLK/4 = 100Mhz/4 = 25Mhz*/
			break;		
		case 3:
			LPC_SC->PCONP |= 1<<23;
			LPC_SC->PCLKSEL1  &= ~(3<<13);			/* Set TIMER3 clock to CCLK/4 = 100Mhz/4 = 25Mhz*/
			break;
		default:
			return 0;
	}
	return 1;
}

/*----------------------------------------------------------------------------
  Function that powers off the timer specified by timerNum.
	Returns 1 if the argument is valid, 0 otherwise.
 *----------------------------------------------------------------------------*/

uint8_t powerOffTimer(uint8_t timerNum){
	switch(timerNum){
		case 0:
			LPC_SC->PCONP &= ~(1<<1);
			break;				
		case 1:
			LPC_SC->PCONP &= ~(1<<2);
			break;
		case 2:
			LPC_SC->PCONP &= ~(1<<22);
			break;		
		case 3:
			LPC_SC->PCONP &= ~(1<<23);
			break;
		default:
			return 0;
	}
	return 1;
}

/*----------------------------------------------------------------------------
  Function that enables the timer specified by timerNum.
	Returns 1 if the argument is valid, 0 otherwise.
	When a timer is enabled it starts immediately counting, so it's better
	to set it up in advance through a call to initTimer().
 *----------------------------------------------------------------------------*/

uint8_t enableTimer(uint8_t timerNum){
	switch(timerNum){
		case 0:
			LPC_TIM0->TCR = 1;
			break;
		case 1:
			LPC_TIM1->TCR = 1;
			break;
		case 2:
			LPC_TIM2->TCR = 1;
			break;
		case 3:
			LPC_TIM3->TCR = 1;
			break;
		default:
			return 0;
	}
  return 1;
}

/*----------------------------------------------------------------------------
  Function disables the timer specified by timerNum.
	Returns 1 if the argument is valid, 0 otherwise.
	When a timer is disabled it just stops counting, to reset it you need
	to call resetTimer().
 *----------------------------------------------------------------------------*/

uint8_t disableTimer(uint8_t timerNum){
  switch(timerNum){
		case 0:
			LPC_TIM0->TCR &= ~1;
		  break;
		case 1:
			LPC_TIM1->TCR &= ~1;
		  break;
		case 2:
			LPC_TIM2->TCR &= ~1;
		  break;
		case 3:
			LPC_TIM3->TCR &= ~1;
			break;
		default:
			return 0;
	}
  return 1;
}

/*----------------------------------------------------------------------------
  Function that resets the timer specified by timerNum.
	Returns 1 if the argument is valid, 0 otherwise.
	Resetting a timer will make it count from 0 again, to stop it you need to
	either disable it by calling disableTimer() or initialize it again with 
	the appropriate flag to make it stop on reaching the value specified on the
	match register you specified on the first call to initTimer().
 *----------------------------------------------------------------------------*/

uint8_t reseTimer(uint8_t timerNum){
	switch(timerNum){
		case 0:
		  LPC_TIM0->TCR |= 1<<1;
			break;
		case 1:
		  LPC_TIM1->TCR |= 1<<1;
			break;
		case 2:
		  LPC_TIM2->TCR |= 1<<1;
			break;
		case 3:
		  LPC_TIM2->TCR |= 1<<1;
			break;
		default: 
			return 0;
	}
	return 1;
}

/*----------------------------------------------------------------------------
	Function that sets up timer parameters according to flags and interval
	parameters.
	Returns 1 if the flags are valid, 0 if the flags are not valid or if 
	you specify a 0 interval.
	The flags parameter contains bit fields that setup the timer according to
	the following structure:
	bits 6 and 5 specify the timer (T0-T3);
	bits 4 and 3 specify the match register (MR0-MR3) that will be initialized;
	with the values specifies by the interval parameter;
	bit 2 specifies if the timer stops when reaching the value of the match
	register;
	bit 1 specifies if the timer resets when reaching the value of the match 
	register;
	bit	0 specifies if the timer triggers an interrupt when reaching the value 
	of the match register.
	This function can setup one match register at a time with the value of 
	the interval parameter, if you need to setup more register you should
	call this function again with the appropriate flags.
	The header file declaring this function has predefined constants to use
	when calling this function.
 *----------------------------------------------------------------------------*/

uint8_t initTimer(uint8_t flags, uint32_t interval){
	uint8_t timerNum = 0x3 & flags >> 5;
	uint8_t matchRegister = 0x3 & flags >> 3;
	uint8_t interruptFlag = 0x1 & flags;
	uint8_t resetFlag = 0x1 & flags >> 1;
	uint8_t stopFlag = 0x1 & flags >> 2;
	if((interruptFlag > 1) || (resetFlag > 1) || (stopFlag > 1) || (interval == 0)){
		return 0;	
	}
	switch(timerNum){
		case 0:
			switch(matchRegister){
				case 0:
					LPC_TIM0->MR0 = interval;
				  if(interruptFlag){
						LPC_TIM0->MCR |= 1;
					  NVIC_EnableIRQ(TIMER0_IRQn);
				  }
				  if(resetFlag){
						LPC_TIM0->MCR |= 1<<1;
				  }
				  if(stopFlag){
						LPC_TIM0->MCR |= 1<<2;
				  }	
					break;
				case 1:
					LPC_TIM0->MR1 = interval;
				   if(interruptFlag){
						LPC_TIM0->MCR |= 1<<3;
					   NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
					   LPC_TIM0->MCR |= 1<<4;
				   }
				   if(stopFlag){
					   LPC_TIM0->MCR |= 1<<5;
				   }	
					  break;
				case 2:
					LPC_TIM0->MR2 = interval;
				   if(interruptFlag){
						LPC_TIM0->MCR |= 1<<6;
					   NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
					   LPC_TIM0->MCR |= 1<<7;
				   }
				   if(stopFlag){
					   LPC_TIM0->MCR |= 1<<8;
				   }	
					 break;
				case 3:
					LPC_TIM0->MR3 = interval;
				   if(interruptFlag){
						LPC_TIM0->MCR |= 1<<9;
				    NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
				    LPC_TIM0->MCR |= 1<<10;
				   }
				   if(stopFlag){
				    LPC_TIM0->MCR |= 1<<11;
				   }	
				  break;	
				default:
					return 0;
			}
			break;
		case 1:
			switch(matchRegister){
				case 0:
					LPC_TIM1->MR0 = interval;
				  if(interruptFlag){
						LPC_TIM1->MCR |= 1;
					  NVIC_EnableIRQ(TIMER0_IRQn);
				  }
				  if(resetFlag){
						LPC_TIM1->MCR |= 1<<1;
				  }
				  if(stopFlag){
						LPC_TIM1->MCR |= 1<<2;
				  }	
					break;
				case 1:
					LPC_TIM1->MR1 = interval;
				   if(interruptFlag){
						LPC_TIM1->MCR |= 1<<3;
					   NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
					   LPC_TIM1->MCR |= 1<<4;
				   }
				   if(stopFlag){
					   LPC_TIM1->MCR |= 1<<5;
				   }	
					  break;
				case 2:
					LPC_TIM1->MR2 = interval;
				   if(interruptFlag){
						LPC_TIM1->MCR |= 1<<6;
					   NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
					   LPC_TIM1->MCR |= 1<<7;
				   }
				   if(stopFlag){
					   LPC_TIM1->MCR |= 1<<8;
				   }	
					 break;
				case 3:
					LPC_TIM1->MR3 = interval;
				   if(interruptFlag){
						LPC_TIM1->MCR |= 1<<9;
				    NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
				    LPC_TIM1->MCR |= 1<<10;
				   }
				   if(stopFlag){
				    LPC_TIM1->MCR |= 1<<11;
				   }	
				  break;	
				default:
					return 0;
			}
			break;
		case 2:
			switch(matchRegister){
				case 0:
					LPC_TIM2->MR0 = interval;
				  if(interruptFlag){
						LPC_TIM2->MCR |= 1;
					  NVIC_EnableIRQ(TIMER0_IRQn);
				  }
				  if(resetFlag){
						LPC_TIM2->MCR |= 1<<1;
				  }
				  if(stopFlag){
						LPC_TIM2->MCR |= 1<<2;
				  }	
					break;
				case 1:
					LPC_TIM2->MR1 = interval;
				   if(interruptFlag){
						LPC_TIM2->MCR |= 1<<3;
					   NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
					   LPC_TIM2->MCR |= 1<<4;
				   }
				   if(stopFlag){
					   LPC_TIM2->MCR |= 1<<5;
				   }	
					  break;
				case 2:
					LPC_TIM2->MR2 = interval;
				   if(interruptFlag){
						LPC_TIM2->MCR |= 1<<6;
					   NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
					   LPC_TIM2->MCR |= 1<<7;
				   }
				   if(stopFlag){
					   LPC_TIM2->MCR |= 1<<8;
				   }	
					 break;
				case 3:
					LPC_TIM2->MR3 = interval;
				   if(interruptFlag){
						LPC_TIM2->MCR |= 1<<9;
				    NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
				    LPC_TIM2->MCR |= 1<<10;
				   }
				   if(stopFlag){
				    LPC_TIM2->MCR |= 1<<11;
				   }	
				  break;	
				default:
					return 0;
			}
			break;
		case 3:
			switch(matchRegister){
				case 0:
					LPC_TIM3->MR0 = interval;
				  if(interruptFlag){
						LPC_TIM3->MCR |= 1;
					  NVIC_EnableIRQ(TIMER0_IRQn);
				  }
				  if(resetFlag){
						LPC_TIM3->MCR |= 1<<1;
				  }
				  if(stopFlag){
						LPC_TIM3->MCR |= 1<<2;
				  }	
					break;
				case 1:
					LPC_TIM3->MR1 = interval;
				   if(interruptFlag){
						LPC_TIM3->MCR |= 1<<3;
					   NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
					   LPC_TIM3->MCR |= 1<<4;
				   }
				   if(stopFlag){
					   LPC_TIM3->MCR |= 1<<5;
				   }	
					  break;
				case 2:
					LPC_TIM3->MR2 = interval;
				   if(interruptFlag){
						LPC_TIM3->MCR |= 1<<6;
					   NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
					   LPC_TIM3->MCR |= 1<<7;
				   }
				   if(stopFlag){
					   LPC_TIM3->MCR |= 1<<8;
				   }	
					 break;
				case 3:
					LPC_TIM3->MR3 = interval;
				   if(interruptFlag){
						LPC_TIM3->MCR |= 1<<9;
				    NVIC_EnableIRQ(TIMER0_IRQn);
				   }
				   if(resetFlag){
				    LPC_TIM3->MCR |= 1<<10;
				   }
				   if(stopFlag){
				    LPC_TIM3->MCR |= 1<<11;
				   }	
				  break;	
				default:
					return 0;
			}
			break;	
		default:
			return 0;
	}	
  return 1;
} 
