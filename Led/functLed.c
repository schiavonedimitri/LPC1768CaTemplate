/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        High level led management functions
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"

#define LEDNUM 8                   

const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };
extern unsigned char led_value;

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void ledOn(uint8_t num){
	LPC_GPIO2->FIOPIN |= led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void ledOff(uint8_t num) {
  LPC_GPIO2->FIOPIN &= ~led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void ledOut(uint8_t value) {
  uint8_t i;
  for (i=0; i<LEDNUM; i++) {
    if (value & (1<<i)) {
      ledOn(i);
		}
		else{
			ledOff(i);
    }
  }
	led_value = value;
}
