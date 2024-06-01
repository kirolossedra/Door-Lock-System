/*
 * buzzer.c
 *
 *  Created on: 29 Oct 2021
 *      Author: kirol
 */


#include "buzzer.h"

void BUZZER_ON(void){
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}
void BUZZER_OFF(void){
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

