#include "nios2_control.h"
#include "timer.h"
#include "chario.h"
#include "button.h"
#include "switches.h"


void	Init(void)
{
  /* initialize software variables */
	

  /* set timer start value for interval of HALF SECOND (0.5 sec) */
  //half a second at 50mhz is 250000000 cyles in hex is 0x0EE6B280, we set top and bottom half acordingly
  
	*TIMER_START_LO = 0x7840;
	*TIMER_START_HI= 0x017D;
	
  /* clear extraneous timer interrupt */
	*TIMER_STATUS =0x0;
  *PUSHBUTTON_EDGE = 0x0; //clear extraneous timer interrupt

  /* set ITO, CONT, and START bits of timer control register */
  //thats bits 0,1,2, 0111 = 0x7
	*TIMER_CONTROL = 0x7;

/////////////////////// TIMER INIT ////////////////////////////////
  
  *PUSHBUTTON_MASK = 0x2;  //bit 0 and 1

//////////////////////////////////////////////////////

  /* set device-specific bit for timer in Nios II ienable register */
//	NIOS2_WRITE_IENABLE(0x1);
    NIOS2_WRITE_IENABLE(0x3); //for button
  

  /* set IE bit in Nios II status register */
	  NIOS2_WRITE_STATUS(0x1);
}
void Switches(){
	
	
    PrintString("\b\b\b\b\b\b\b\b\b\b");
    unsigned int switchData = *SWITCHES_DATA;
    unsigned int mask = 1 << 9;
    int count = 0;
	int i;
  for (i = 0; i < 10; i++){

    if(switchData & mask){

      PrintChar('#');
      count++;

    } else {

      PrintChar(':');
    
    }

    mask = mask >> 1 ;

  }
  unsigned int* hexAddress = 0x10000020;

  if(count == 10){
    
    *hexAddress = 0xFFFFFFFF;

  } else {
    *hexAddress = 0x0;
  }

  
}

volatile int interuptFlag = 0;

int	main(void)
{

  /* perform initialization */
  Init();
  
  
	PrintString("ELEC371 Lab 3\n");
  PrintString("          ");
  while (1){
	  if (interuptFlag !=0){
			

    // Need to push stuff to do for button here
      
     
      Switches();

      interuptFlag=0;


			
	  }
	  



  }
    


  return 0; /* never reached, but needed to avoid compiler warning */
}
