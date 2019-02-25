																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           led.h
** Last modified Date:  2019-02-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_led, funct_led .c files
** Correlated files:    libLed.c, functLed.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#ifndef __LED_H
#define __LED_H

/*----------------------------------------------------------------------------
  Led port and pins configuration
	Leds are connected to the port 2 of the system to the pins
	P2.0, P2.1, P2.2, P2.3, P2.4, P2.5, P2.6, P2.7
	The functionality of these pins is managed by the pin connect block
	register PINSEL4.
	The relationship between PINSEL4 register and port pins is the following:
	P2.0-->PINSEL3[1-0]
	P2.1-->PINSEL3[3-2]
	P2.2-->PINSEL3[5-4]
	P2.3-->PINSEL3[7-6]
	P2.4-->PINSEL3[9-8]
	P2.5-->PINSEL3[11-10]
	P2.6-->PINSEL3[13-12]
	P2.7-->PINSEL3[15-14]
	Each pair of bits of the PINSEL4 register specifies the corresponding
	pin functionality or mode. We are interested in the GPIO mode for the 
	pins of the leds since we have no other functions for them
	P2.0-->PINSEL3[1-0] 	== 00 --> GPIO
	P2.1-->PINSEL3[3-2] 	== 00 --> GPIO
	P2.2-->PINSEL3[5-4] 	== 00 --> GPIO
	P2.3-->PINSEL3[7-6] 	== 00 --> GPIO
	P2.4-->PINSEL3[9-8] 	== 00 --> GPIO
	P2.5-->PINSEL3[11-10] == 00 --> GPIO
	P2.6-->PINSEL3[13-12] == 00 --> GPIO
	P2.7-->PINSEL3[15-14] == 00 --> GPIO
	After setting the led pins to GPIO mode we need to specify if these
	pins are input or output. The register managing this functionality is in the
	GPIO2 block and precisely is FIODIR. a 1 to the corresponding bit means that
	the corresponding pin is set as output, a 0 means that it is set as input.
	The following table shows the relationship:
	P2.0-->GPIO2-->FIODIR[0]  == 0--> INPUT
	P2.1-->GPIO2-->FIODIR[26] == 0--> INPUT
	P2.2-->GPIO2-->FIODIR[27] == 0--> INPUT
	P2.3-->GPIO2-->FIODIR[28] == 0--> INPUT
	P2.4-->GPIO2-->FIODIR[29] == 0--> INPUT
	P2.5-->GPIO2-->FIODIR[0]  == 0--> INPUT
	P2.6-->GPIO2-->FIODIR[26] == 0--> INPUT
	P2.7-->GPIO2-->FIODIR[27] == 0--> INPUT
	P2.0-->GPIO2-->FIODIR[0]  == 0--> OUTPUT
	P2.1-->GPIO2-->FIODIR[26] == 0--> OUTPUT
	P2.2-->GPIO2-->FIODIR[27] == 0--> OUTPUT
	P2.3-->GPIO2-->FIODIR[28] == 0--> OUTPUT
	P2.4-->GPIO2-->FIODIR[29] == 0--> OUTPUT
	P2.5-->GPIO2-->FIODIR[0]  == 0--> OUTPUT
	P2.6-->GPIO2-->FIODIR[26] == 1--> OUTPUT
	P2.7-->GPIO2-->FIODIR[27] == 1--> OUTPUT
	Of course since these are leds we are interested in setting them as outputs
	To read the value of a led just probe the corresponding pin value
	Leds are active high
	e.g. if(LPC_GPIO2->FIOPIN & (1<<bit){led "bit" is on}
 *----------------------------------------------------------------------------*/


/* libLed */
void ledInit(void);
void ledDeinit(void);

/* functLed */
void ledOn(uint8_t num);
void ledOff(uint8_t num);
void ledOut(uint8_t value);

#endif
