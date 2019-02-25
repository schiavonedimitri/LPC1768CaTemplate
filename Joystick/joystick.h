																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2019-02-23
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in libJoystick, functJoystick .c files
												and constant definitions
** Correlated files:    libJoystick.c, functJoystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#ifndef __JOYSTICK_H
#define __JOYSTICK_H

/*----------------------------------------------------------------------------
  Joystick port and pins configuration
	The joystick is connected to the port 1 of the system to the pins
	P1.25, P1.26, P1.27, P1.28, P1.29.
	The functionality of these pins is managed by the pin connect block
	register PINSEL3.
	The relationship between PINSEL3 register and port pins is the following:
	P1.25-->PINSEL3[19-18]
	P1.26-->PINSEL3[21-20]
	P1.26-->PINSEL3[23-22]
	P1.26-->PINSEL3[25-24]
	P1.26-->PINSEL3[27-26]
	Each pair of bits of the PINSEL3 register specifies the corresponding
	pin functionality or mode. We are interested in the GPIO mode for the 
	pins of the joystick since its pins cannot be configured as external
	interrupt sources (hence we must do polling for managing events).
	The GPIO mode is enabled if the corresponding bits in the PINSEL3
	register take value 00 as the following table show:
	P1.25-->PINSEL3[19-18]==[00]-->GPIO
	P1.26-->PINSEL3[21-20]==[00]-->GPIO
	P1.27-->PINSEL3[23-22]==[00]-->GPIO
	P1.28-->PINSEL3[25-24]==[00]-->GPIO
	P1.29-->PINSEL3[27-26]==[00]-->GPIO
	After setting the joystick pins to GPIO mode we need to specify if these
	pins are input or output. The register managing this functionality is in the
	GPIO1 block and precisely is FIODIR. a 1 to the corresponding bit means that
	the corresponding pin is set as output, a 0 means that it is set as input.
	The following table shows the relationship:
	P1.25-->GPIO1-->FIODIR[25]==0-->INPUT
	P1.26-->GPIO1-->FIODIR[26]==0-->INPUT
	P1.27-->GPIO1-->FIODIR[27]==0-->INPUT
	P1.28-->GPIO1-->FIODIR[28]==0-->INPUT
	P1.29-->GPIO1-->FIODIR[29]==0-->INPUT
	The following tables shows the mapping of the joystick buttons to the
	corresponding ports:
	P1.25-->Select
	P1.26-->Down 
	P1.27-->Left 
	P1.28-->Right 
	P1.29-->Up 	
	The pins of the joystick are all active low, meaning that if you read a 0
	value on that pin, it means that the corresponding button has been pressed.
	This information is found in the schematic of the board.
	Finally the register storing the current value of the pins corresponding to
	the buttons is in the GPIO1 block and it is FIOPIN
	For example to know if the select button p1.25 has been pushed you do
	if(!(LPC_GPIO1->FIOPIN &= 1<<25))-->select has been pressed.
	NOTE: to get the value in a variable remember to shift the bit you want in the least
	significant position and clear the unwanted bits by anding with a mask of 0s where 
	you want to clear and 1 where you want to keep.
 *----------------------------------------------------------------------------*/

#define PCONBP125 18
#define PCONBP126 20
#define PCONBP127 22
#define PCONBP128 24
#define PCONBP129 26

#define JBITSELECT	25
#define JBITDOWN		26
#define JBITLEFT		27
#define JBITRIGHT		28
#define JBITUP		29

#define JSELECT 0
#define JDOWN 1
#define JLEFT 2
#define JRIGHT 3
#define JUP 4

extern int jSelectCounter;
extern int jDownCounter;
extern int jLeftCounter;
extern int jRightCounter;
extern int jUpCounter;


/* libJoystick */
void joystickInit(void);

/* functJoystick */
void onSelectPressed(void);
void onUpPressed(void);
void onUpLongPressed(void);
void onDownPressed(void);
void onLeftPressed(void);
void onRightPressed(void);

#endif
