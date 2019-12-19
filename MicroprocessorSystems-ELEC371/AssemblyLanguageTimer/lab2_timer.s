#-----------------------------------------------------------------------------
# This template source file for ELEC 371 Lab 2 experimentation with interrupts
# also serves as the template for all assembly-language-level coding for
# Nios II interrupt-based programs in this course. DO NOT USE the approach
# shown in the documentation for the DE0 Basic (or Media) Computer. The
# approach illustrated in this template file is far simpler for learning.
#
# N. Manjikian  Sept. 2019
#-----------------------------------------------------------------------------

	.text		# start a code segment 

	.global	_start	# export _start symbol for linker 

#-----------------------------------------------------------------------------
# Define symbols for memory-mapped I/O register addresses and use them in code
#-----------------------------------------------------------------------------

# the symbols below are specifically for the Lab 2 pushbutton/LED experiment

	.equ	BUTTONS_MASK_REGISTER, 0x10000058
	.equ	BUTTONS_EDGE_REGISTER, 0x1000005C

	.equ	LEDS_DATA_REGISTER, 0x10000010
	
	.equ	LAST_RAM_WORD, 0x007FFFFC 

	.equ	TIMER_STATUS, 0x10002000
	.equ	CONTROL, 0x10002004
	.equ	START_LO, 0x10002008
	.equ	START_HI, 0x1000200C

	.equ	HEX_DISPLAY, 0x10000020


#-----------------------------------------------------------------------------
# Define two branch instructions in specific locations at the start of memory
#-----------------------------------------------------------------------------

	.org	0x0000	# this is the _reset_ address 
_start:
	br	main	# branch to actual start of main() routine 

	.org	0x0020	# this is the _exception/interrupt_ address
 
	br	isr	# branch to start of interrupt service routine 
			# (rather than placing all of the service code here) 

#-----------------------------------------------------------------------------
# The actual program code (incl. service routine) can be placed immediately
# after the second branch above, or another .org directive could be used
# to place the program code at a desired address (e.g., 0x0080). It does not
# matter because the _start symbol defines where execution begins, and the
# branch at that location simply force execution to continue where desired.
#-----------------------------------------------------------------------------

main:
	movia 	sp, LAST_RAM_WORD		# initialize stack pointer
	call	Init					# call hw/sw initialization subroutine
	mov	r2, r0					# perform any local initialization before main loop 

mainloop:
	addi	r2, r2, 1	# body of main loop
	br		mainloop

#-----------------------------------------------------------------------------
# This subroutine should encompass preparation of I/O registers as well as
# special processor registers for recognition and processing of interrupt
# requests. Preparation of program data can also be included here.
#-----------------------------------------------------------------------------

Init:
	subi	sp,sp,12
	stw		r4, 8(sp)
	stw		r2, 4(sp)
	stw		r3, 0(sp)
	
	movi	r2, 4		#4 corresponds to 0100 which puts a 1 in bit position of btn 2
	movia	r3, BUTTONS_MASK_REGISTER
	stwio	r2, 0(r3)	#writing 1 to btn 2 bit pos. in btn_mask_reg (interrupt enable)
	
	rdctl	r2, ienable	
	ori		r2, r2, 0x3	#2 corresponds to 0010 which puts a 1 in bit position of btns
	wrctl	ienable, r2	#change ienable in proc to allow btn interrupts
	
	rdctl	r2, status	#change "status" (the PS register) to allow interrupts
	ori		r2, r2, 1	#lowest bit in "status" is for interrupts
	wrctl	status, r2	#write 1 to lowest "status" bit to allow interrupts generally
	
	movia 	r4, START_LO
	movi	r2, 0x7840
	stwio	r2, 0(r4)

	movia 	r4, START_HI
	movi	r2, 0x17D
	stwio	r2, 0(r4)

	movia r4, CONTROL
	movi r3, 7
	stwio r3, 0(r4) 
	
	ldw		r4, 8(sp)
	ldw		r2, 4(sp)
	ldw		r3, 0(sp)
	addi	sp, sp, 12
	
	ret

#-----------------------------------------------------------------------------
# The code for the interrupt service routine is below. Note that the branch
# instruction at 0x0020 is executed first upon recognition of interrupts,
# and that branch brings the flow of execution to the code below. Therefore,
# the actual code for this routine can be anywhere in memory for convenience.
# This template involves only hardware-generated interrupts. Therefore, the
# return-address adjustment on the ea register is performed unconditionally.
# Programs with software-generated interrupts must check for hardware sources
# to conditionally adjust the ea register (no adjustment for s/w interrupts).
#-----------------------------------------------------------------------------

isr:
	addi	ea, ea, -4	# this is _required_ for hardware interrupts

	subi	sp, sp, 20
	stw		ra, 16(sp)
	stw		r5, 12(sp)
	stw		r4, 8(sp)
	stw		r2, 4(sp)
	stw		r3, 0(sp)
	
	rdctl		r2, ipending
	movi		r3, 2				
	and		r5, r2, r3
	beq		r5, r3, button_interrupt

	movi		r3, 1
	and		r5, r2, r3
	beq		r5, r3, timer_interrupt

	beq		r5, r0, exit_isr	#ipending bit for btn not 1, don't change LED
	
	button_interrupt:
	call	handle_button			#write the new state to LED (LEDG0 should change)
	br	exit_isr

	timer_interrupt:
	call	handle_timer
	br	exit_isr
	
	
exit_isr:
	ldw		ra, 16(sp)
	ldw		r5, 12(sp)
	ldw		r4, 8(sp)
	ldw		r2, 4(sp)
	ldw		r3, 0(sp)
	addi	sp, sp, 20
	eret

handle_button:
	subi	sp, sp, 20
	stw		ra, 16(sp)
	stw		r5, 12(sp)
	stw		r4, 8(sp)
	stw		r2, 4(sp)
	stw		r3, 0(sp)

	movi r4, 1
	movia r5, 0x10000040
	ldw r5, 0(r5)
	and r5, r5, r4
	bne r5, r4, not_enabled
				
	movi	r2, 4				#ipending bit for btn is 1, change LED
	movia	r3, BUTTONS_EDGE_REGISTER
	stwio	r2, 0(r3)			#clears edge bits, clears interrupt source
	movia	r3, LED_STATE
	ldw		r2, 0(r3)			#retrieve LED_STATE from memory
	addi	r2, r2, 1			#complement state value retrieved from memory
	stw		r2, 0(r3)			#update state in memory
	movia 	r3, LEDS_DATA_REGISTER
    	stwio	r2, 0(r3)

	not_enabled:

	ldw		ra, 16(sp)
	ldw		r5, 12(sp)
	ldw		r4, 8(sp)
	ldw		r2, 4(sp)
	ldw		r3, 0(sp)
	addi	sp, sp, 20

	ret

handle_timer:
	subi	sp, sp, 20
	stw		ra, 16(sp)
	stw		r5, 12(sp)
	stw		r4, 8(sp)
	stw		r2, 4(sp)
	stw		r3, 0(sp)

	movia	r2, TIMER_STATUS
	ldwio	r3, 0(r2)
	andi	r3, r3, 0xFFFE
	stwio	r3, 0(r2)

	movia	r3, HEX_DISPLAY
	ldw	r4, 0(r3)
	and	r4, r4, r0
	stwio	r4, 0(r3)
	
	movia r3, LIT
	ldw r3, 0(r3)
	
		
	movi r4, 1
	beq r3, r4, one
	movi r4, 2
	beq r3, r4, two
	movi r4, 3
	beq r3, r4, three
	movi r4, 4
	beq r3, r4, four	 
one:
	movi r5, 0xFF

	movia r4, LIT
	ldw r3, 0(r4)
	addi r3, r3, 1
	stw r3, 0(r4)
	
	br end_four

two:
	movia r5, 0xFF00
	movia r4, LIT
	ldw r3, 0(r4)
	addi r3, r3, 1
	stw r3, 0(r4)
	br end_four
three:
	movia r5, 0xFF0000
	movia r4, LIT
	ldw r3, 0(r4)
	addi r3, r3, 1
	stw r3, 0(r4)
	br end_four
four:	
	movia r5, 0xFF000000
	movia r4, LIT
	ldw r3, 0(r4)
	movi r3, 1
	stw r3, 0(r4)
	br end_four
end_four:		
	
	
	movia	r3, HEX_DISPLAY
	ldw	r4, 0(r3)
	xor	r4, r4, r5
	stwio	r4, 0(r3)
	

	

	ldw		ra, 16(sp)
	ldw		r5, 12(sp)
	ldw		r4, 8(sp)
	ldw		r2, 4(sp)
	ldw		r3, 0(sp)
	addi	sp, sp, 20


	ret
		

#-----------------------------------------------------------------------------
# Definitions for program data, incl. anything shared between main/isr code
#-----------------------------------------------------------------------------

	.org	0x1000		# start should be fine for most small programs
	
LED_STATE:	.word	0	#define start state to be off
LIT:		.word	1	#1 is right-most, 4 is left-most

	.end