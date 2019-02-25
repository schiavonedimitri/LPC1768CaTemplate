/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Author: 							Dimitri Schiavone (schiavone.dimitri.2@gmail.com)
** Last modified Date:  2019-02-23
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in libTimer, functTimer, irqTimer .c files
												and constants definitions
** Related files:    		libTimer.c, functTimer.c, irqTimer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#ifndef __TIMER_H
#define __TIMER_H

/*----------------------------------------------------------------------------
	At system boot or reset TIMER0 and TIMER1 are powered on and TIMER2 and
	TIMER3 are powered off, so you need to turn them on by setting the
	corresponding bits:
	PCONP-->[1] = 0 -->TIMER0 powered off
	PCONP-->[2] = 0 -->TIMER1 powered off
  PCONP-->[22] = 0 -->TIMER0 powered off
	PCONP-->[23] = 0 -->TIMER1 powered off
	PCONP-->[1] = 1 -->TIMER0 powered on
	PCONP-->[2] = 1 -->TIMER1 powered on
  PCONP-->[22] = 1 -->TIMER0 powered on
	PCONP-->[23] = 1 -->TIMER1 powered on
	At system boot or reset all the timers whether powered on or off are setup
	to use the default clock divider CCLK/4, so you need to set the correct bits
	in the PCLKSELX register to use different dividers. TIMER0 and TIMER1 clock
	sources are setup through PCLKSEL0 register whereas TIMER1 and TIMER2
	are setup using the PCLKSEL1 register. The following table 
	shows the possibile values for the clocks of the timers:
	PCLKSEL0-->[3-2] = 00 --> TIMER0 clock = CCLK/4
	PCLKSEL0-->[3-2] = 01 --> TIMER0 clock = CCLK
	PCLKSEL0-->[3-2] = 10 --> TIMER0 clock = CCLK/2
	PCLKSEL0-->[3-2] = 11 --> TIMER0 clock = CCLK/8
	PCLKSEL0-->[5-4] = 00 --> TIMER1 clock = CCLK/4
	PCLKSEL0-->[5-4] = 01 --> TIMER1 clock = CCLK
	PCLKSEL0-->[5-4] = 10 --> TIMER1 clock = CCLK/2
	PCLKSEL0-->[5-4] = 11 --> TIMER1 clock = CCLK/8
	PCLKSEL1-->[13-12] = 00 --> TIMER2 clock = CCLK/4
	PCLKSEL1-->[13-12] = 01 --> TIMER2 clock = CCLK
	PCLKSEL1-->[13-12] = 10 --> TIMER2 clock = CCLK/2
	PCLKSEL1-->[13-12] = 11 --> TIMER2 clock = CCLK/8
	PCLKSEL1-->[15-14] = 00 --> TIMER3 clock = CCLK/4
	PCLKSEL1-->[15-14] = 01 --> TIMER3 clock = CCLK
	PCLKSEL1-->[15-14] = 10 --> TIMER3 clock = CCLK/2
	PCLKSEL1-->[15-14] = 11 --> TIMER3 clock = CCLK/8	
	NOTE: at system boot or reset CCLK = 100Mhz
	NOTE2: to calculate the value k to set a counter to count for x seconds you
	can use this formula:
	k = x* CLOCK
	e.g. count 10 seconds with a reference clock of 25Mhz
	k = 10*25*10^6 = 0x?EE6B280? which is the value to set the timer to count
	to.
 *----------------------------------------------------------------------------*/


/* These constants are just a mask for setting up the appropriate timer(T0-T3), match register(MR0-MR3)
	 and flags (INT = interrupt, RST = reset, STP = stop)
	 e.g. TOMR2INTSTP means you want to setup timer 0, match register 2 and you want the timer to trigger
   an interrupt and stop on matching the value on match register 2																	  	 */

#define T0MR0	0x0
#define T0MR0INT 0x1
#define T0MR0RST 0x2
#define T0MR0INTRST 0x3
#define T0MR0STP 0x4
#define T0MR0INTSTP	0x5
#define T0MR0RSTSTP 0x6
#define T0MR0INTRSTSTP 0x7
#define T0MR1	0x8
#define T0MR1INT 0x9
#define T0MR1RST 0xA
#define T0MR1INTRST 0xB
#define T0MR1STP 0xC
#define T0MR1INTSTP	0xD
#define T0MR1RSTSTP 0xE
#define T0MR1INTRSTSTP 0xF
#define T0MR2	0x10
#define T0MR2INT 0x11
#define T0MR2RST 0x12
#define T0MR2INTRST 0x13
#define T0MR2STP 0x14
#define T0MR2INTSTP	0x15
#define T0MR2RSTSTP 0x16
#define T0MR2INTRSTSTP 0x17
#define T0MR3	0x18
#define T0MR3INT 0x19
#define T0MR3RST 0x1A
#define T0MR3INTRST 0x1B
#define T0MR3STP 0x1C
#define T0MR3INTSTP	0x1D
#define T0MR3RSTSTP 0x1E
#define T0MR3INTRSTSTP 0x1F
#define T1MR0	0x20
#define T1MR0INT 0x21
#define T1MR0RST 0x22
#define T1MR0INTRST 0x23
#define T1MR0STP 0x24
#define T1MR0INTSTP	0x25
#define T1MR0RSTSTP 0x26
#define T1MR0INTRSTSTP 0x27
#define T1MR1	0x28
#define T1MR1INT 0x29
#define T1MR1RST 0x2A
#define T1MR1INTRST 0x2B
#define T1MR1STP 0x2C
#define T1MR1INTSTP	0x2D
#define T1MR1RSTSTP 0x2E
#define T1MR1INTRSTSTP 0x2F
#define T1MR2	0x30
#define T1MR2INT 0x31
#define T1MR2RST 0x32
#define T1MR2INTRST 0x33
#define T1MR2STP 0x34
#define T1MR2INTSTP	0x35
#define T1MR2RSTSTP 0x36
#define T1MR2INTRSTSTP 0x37
#define T1MR3	0x38
#define T1MR3INT 0x39
#define T1MR3RST 0x3A
#define T1MR3INTRST 0x3B
#define T1MR3STP 0x3C
#define T1MR3INTSTP	0x3D
#define T1MR3RSTSTP 0x3E
#define T1MR3INTRSTSTP 0x3F
#define T2MR0	0x40
#define T2MR0INT 0x41
#define T2MR0RST 0x42
#define T2MR0INTRST 0x43
#define T2MR0STP 0x44
#define T2MR0INTSTP	0x45
#define T2MR0RSTSTP 0x46
#define T2MR0INTRSTSTP 0x47
#define T2MR1	0x48
#define T2MR1INT 0x49
#define T2MR1RST 0x4A
#define T2MR1INTRST 0x4B
#define T2MR1STP 0x4C
#define T2MR1INTSTP	0x4D
#define T2MR1RSTSTP 0x4E
#define T2MR1INTRSTSTP 0x4F
#define T2MR2	0x50
#define T2MR2INT 0x51
#define T2MR2RST 0x52
#define T2MR2INTRST 0x53
#define T2MR2STP 0x54
#define T2MR2INTSTP	0x55
#define T2MR2RSTSTP 0x56
#define T2MR2INTRSTSTP 0x57
#define T2MR3	0x58
#define T2MR3INT 0x59
#define T2MR3RST 0x5A
#define T2MR3INTRST 0x5B
#define T2MR3STP 0x5C
#define T2MR3INTSTP	0x5D
#define T2MR3RSTSTP 0x5E
#define T2MR3INTRSTSTP 0x5F
#define T3MR0	0x60
#define T3MR0INT 0x61
#define T3MR0RST 0x62
#define T3MR0INTRST 0x63
#define T3MR0STP 0x64
#define T3MR0INTSTP	0x65
#define T3MR0RSTSTP 0x66
#define T3MR0INTRSTSTP 0x67
#define T3MR1	0x68
#define T3MR1INT 0x69
#define T3MR1RST 0x6A
#define T3MR1INTRST 0x6B
#define T3MR1STP 0x6C
#define T3MR1INTSTP	0x6D
#define T3MR1RSTSTP 0x6E
#define T3MR1INTRSTSTP 0x6F
#define T3MR2	0x70
#define T3MR2INT 0x71
#define T3MR2RST 0x72
#define T3MR2INTRST 0x73
#define T3MR2STP 0x74
#define T3MR2INTSTP	0x75
#define T3MR2RSTSTP 0x76
#define T3MR2INTRSTSTP 0x77
#define T3MR3	0x78
#define T3MR3INT 0x79
#define T3MR3RST 0x7A
#define T3MR3INTRST 0x7B
#define T3MR3STP 0x7C
#define T3MR3INTSTP	0x7D
#define T3MR3RSTSTP 0x7E
#define T3MR3INTRSTSTP 0x7F

/* libTimer.c */
uint8_t powerOnTimer(uint8_t timerNum);
uint8_t initTimer(uint8_t flags, uint32_t interval);
uint8_t enableTimer(uint8_t timerNum);
uint8_t disableTimer(uint8_t timerNum );
void reset_timer( uint8_t timer_num );

/* irqTimer.c */

void TIMER0_IRQHandler (void);
void TIMER1_IRQHandler (void);

#endif
