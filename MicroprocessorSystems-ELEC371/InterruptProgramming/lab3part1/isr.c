#include "nios2_control.h"
#include "leds.h"
#include "timer.h"

extern volatile char interuptFlag;
void interrupt_handler(void)
{
	/* read current value in ipending register, using macro */
	unsigned int ipending;
	
	ipending = NIOS2_READ_IPENDING();
	
	/* _if_ ipending bit for timer is set,
	   _then_
	       clear timer interrupt,
	       and toggle the least-sig. LED
	       (use the C '^' operator for XOR with constant 1)
	*/
	
	
	//uses c bitwise and "&" on ipending and ox1, if the result is 1 (aka the ipending bit 0 is set to high) this evaluates to 1, which in c is true
	if(ipending & 0x1){
		//clear timer interupt bit 
		unsigned int timerStatus = *TIMER_STATUS;//get the timer status word
		timerStatus = timerStatus ^ TIMER_TO_BIT;//flip the timer interrupt bit
		*TIMER_STATUS = timerStatus;//write it back into mem/IO
		
		//flip led bits
		*LEDS = *LEDS ^ 0x1; //bitwise XOR on contents of word at LEDS address (led control bits), toggles lowest LED 
		interuptFlag = 1;
	}
	
	/*
	if(ipending & 0x2){
		//clear button edge reg
		unsigned int pushbuttonEdge = *PUSHBUTTON_EDGE;
		pushbuttonEdge = pushbuttonEdge ^ 0x1;
		*PUSHBUTTON_EDGE = pushbuttonEdge;

		//flip LED bits
		*LEDS = *LEDS ^ 0x2; //second lowest as specified
		interuptFlag = 1;
	}
	
	*/
}
