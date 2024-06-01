/*
 * pwm.c
 *
 *  Created on: 12 Oct 2021
 *      Author: kirol
 */

#include "pwm.h"
#include "gpio.h"


#include <avr/io.h>  /*To use Timer0 Register*/

void PWM_Timer0_Start(uint8 duty_cycle)
{


	TCNT0 = 0; //Set Timer Initial value

		OCR0  = (uint8)(((uint32)(256)*duty_cycle)/(100)) -1 ;

		 //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

		 GPIO_setupPinDirection(PORTB_ID,PIN3_ID, PIN_OUTPUT);


		TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

