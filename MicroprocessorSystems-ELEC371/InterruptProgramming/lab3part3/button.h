#ifndef _BUTTON_H_
#define _BUTTON_H_


/* define pointer macros for accessing the timer interface registers */

#define PUSHBUTTON_DATA	((volatile unsigned int *) 0x10000050)

#define PUSHBUTTON_MASK	((volatile unsigned int *) 0x10000058)

#define PUSHBUTTON_EDGE	((volatile unsigned int *) 0x1000005C)




/* define a bit pattern reflecting the position of the timeout (TO) bit
   in the timer status register */




#endif /* _BUTTON_H_ */