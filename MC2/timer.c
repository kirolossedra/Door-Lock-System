/*
 * timer.c
 *
 *  Created on: 24 Oct 2021
 *      Author: kirol
 */


#include "timer.h"
#include "gpio.h"
#include "std_types.h"

#include <avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;





//((uint32)1000)/((gptr->seconds)*((uint32)(F_CPU*(gptr->CTC_CMPR)) /(uint32)(arr[gptr->divsor]*1000)) )


ISR(TIMER0_OVF_vect)
{



	if(g_callBackPtr != NULL_PTR)
	{

		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr != NULL_PTR)
		{

			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}

}
ISR(TIMER1_COMPA_vect){


	if(g_callBackPtr != NULL_PTR)
		{


			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}





void Timer0_init(Timer_config * ptr){

if(ptr->timer==timer0){

	TCNT0 = ptr->Timer_initial_value;
	if(ptr->mode == Timer_Ovf){
		ptr->CTC_CMPR=255;
		ptr->behavior = OC0_OFF;
	}
	else{
		OCR0 = ptr ->CTC_CMPR;
	}



	TIMSK |= (1<<OCIE0);
	SREG  |= (1<<7);
	TCCR0=(1<<FOC0)|((ptr->mode)<<WGM01)|(ptr->behavior)<<COM00|(ptr->divsor);
	if(ptr->behavior)GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
}
if(ptr->timer == timer1){
	TCNT1= ptr->Timer_initial_value;
			if(ptr->mode == Timer_Ovf){
						ptr->CTC_CMPR=255;
						ptr->behavior = OC0_OFF;
						TIMSK |= (1<<TOIE1);
					}
					else{
						OCR1A = ptr ->CTC_CMPR;
						TIMSK |= (1<<OCIE1A);
					}

			SREG  |= (1<<7);
			TCCR1A = (1<<FOC1A);
			TCCR1B = ((ptr->mode)<<WGM12) | (ptr->divsor);
}

}

void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
void Timer0_Deinit(void){
	TIMSK=0;
}


