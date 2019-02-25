/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Joystick management functions
** Correlated files:    libJoystick.c, functJoystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"
#include "../Led/led.h"

int jSelectCounter = 0;
int jDownCounter = 0;
int jLeftCounter = 0;
int jRightCounter = 0;
int jUpCounter = 0;

void onSelectPressed(){
	//your action here
}

void onUpPressed(){
	//your action here
}

void onUpLongPressed(){
	//your action here
}

void onDownPressed(){
	//your action here
}

void onLeftPressed(){
	//your action here
}

void onRightPressed(){
	//your action here
}
