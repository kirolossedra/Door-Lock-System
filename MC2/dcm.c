/*
 * dcm.c
 *
 *  Created on: 12 Oct 2021
 *      Author: kirol
 */

#include "dcm.h"
#include "gpio.h"
#include "common_macros.h"
#include "pwm.h"
#include <avr/io.h>



void DcMotor_Init(void){
	GPIO_setupPinDirection(DCM_IN_PORT,DCM_IN1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCM_IN_PORT,DCM_IN2_PIN, PIN_OUTPUT);
	GPIO_writePin( DCM_IN_PORT,DCM_IN1_PIN , LOGIC_LOW);
	GPIO_writePin( DCM_IN_PORT,DCM_IN2_PIN , LOGIC_LOW);


}


void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	switch(state){
	case 0:
		 GPIO_writePin(  DCM_IN_PORT,DCM_IN1_PIN , LOGIC_LOW);
		 GPIO_writePin( DCM_IN_PORT,DCM_IN2_PIN , LOGIC_LOW);
		 break;
	case 2:
		GPIO_writePin(  DCM_IN_PORT,DCM_IN1_PIN , LOGIC_LOW);
		GPIO_writePin( DCM_IN_PORT,DCM_IN2_PIN , LOGIC_HIGH);
		break;
	case 1:
		GPIO_writePin(  DCM_IN_PORT,DCM_IN1_PIN , LOGIC_HIGH);
		GPIO_writePin( DCM_IN_PORT,DCM_IN2_PIN , LOGIC_LOW);
		break;

	}
	PWM_Timer0_Start(speed);


}
void DcMotor_stop(void){
	 GPIO_writePin(  DCM_IN_PORT,DCM_IN1_PIN , LOGIC_LOW);
	 GPIO_writePin( DCM_IN_PORT,DCM_IN2_PIN , LOGIC_LOW);

}

