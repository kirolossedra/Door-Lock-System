/*
 * timer.h
 *
 *  Created on: 24 Oct 2021
 *      Author: kirol
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"








typedef enum {
	Timer_OFF , FCPU_1 , FCPU_8 ,FCPU_64 , FCPU_256 ,FCPU_1024 ,Ext_FALLING , Ext_RISING
}Clock_SEL;

typedef enum {
	Timer_Ovf , Timer_CTC

}Timer_Mode;

typedef enum {
	OC0_OFF , OC0_TGL , OC0_CLR , OC0_SET

}OC_behavior;

typedef enum{
	timer0 , timer1

}Timer_SEL;

typedef struct  {
	Timer_SEL timer;
	Clock_SEL divsor;
	Timer_Mode mode;
	uint8 Timer_initial_value;
	uint16 CTC_CMPR;
	OC_behavior behavior;




}Timer_config;


void Timer0_init(Timer_config * ptr);
void Timer0_setCallBack(void(*a_ptr)(void));
void Timer1_setCallBack(void(*a_ptr)(void));
void Timer0_Deinit(void);


#endif /* TIMER_H_ */
