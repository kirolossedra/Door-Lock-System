/*
 * buzzer.h
 *
 *  Created on: 29 Oct 2021
 *      Author: kirol
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#define BUZZER_PORT PORTC_ID
#define BUZZER_PIN  PIN2_ID



void BUZZER_ON(void);
void BUZZER_OFF(void);



#endif /* BUZZER_H_ */
