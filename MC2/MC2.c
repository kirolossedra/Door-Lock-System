/*
 ================================================================================================
 Name        : MC2.c
 Author      : Mohamed Tarek
 Description : MC2 Code in Challenge
 Date        : 25/4/2014
 ================================================================================================
 */

#include "uart.h"
#include "lcd.h"
#include "external_eeprom.h"
#include "twi.h"
#include <avr/delay.h>
#include "buzzer.h"
#include "dcm.h"
#include "timer.h"
#define ACC 0xF3
#define MAX_ATTEMPTS 3
#define OPEN_DOOR 0xF4
#define BUZZ 0xF5

DcMotor_State state;

uint32 Motor_tick =0;

Timer_config T0config =  {timer0,FCPU_1024,Timer_CTC,0,250};
Timer_config T1config = {timer1 , FCPU_1024 , Timer_CTC , 65000};




void BUZZER(void){
	BUZZER_OFF();
	Timer0_Deinit();
}
void MotorHandle(void){
	Motor_tick++;
	if(Motor_tick==156){





		state=DCM_STOP;
		DcMotor_Rotate(state,50);
	}

	 if(Motor_tick==312){

			state=DCM_CW;
			DcMotor_Rotate(state,50);
			Motor_tick=0;
			Timer0_Deinit();



	}








}

void StorePassword(){
	for(int i=0; i<5; i++){
		uint8 key;
			key = UART_recieveByte();
			EEPROM_writeByte(i, key);

										/* Display the pressed key on LCD */
										if( (key >= 0) && (key <= 9) )
										{
											LCD_intgerToString(key);
										}
										else
										{
											LCD_displayCharacter(key);
										}
		}
}
void VerifyPassword(){
	uint8 vale;
	int x=0;



		uint8 password[5];
			uint8 verify[5];
			for(int i=0; i<5; i++){
					uint8 key;
						key = UART_recieveByte();
						password[i]=key;


					}
			for(int i=0; i<5; i++){
					EEPROM_readByte(i, &vale);
					verify[i]=vale;

				}
			for(int i=0; i<5; i++){
				if(verify[i]==password[i]){x++;}

			}
			if(x==5){UART_sendByte(ACC);}else{UART_sendByte('h'); }





}

int main(void)
{
	DcMotor_Init();











	uint8 val;

	UART_config uconfig = { STOP_ONE , Parity_STOP , Eight_BITS , 9600};
	UART_init(&uconfig);
	I2config I2_config = { Fast , 1};
	TWI_init(&I2_config);


	LCD_init();





	StorePassword();

	LCD_displayCharacter('w');
	for(int i=0; i<5; i++){
		EEPROM_readByte(i, &val);
		LCD_intgerToString(val);

	}
//	VerifyPassword();

		/* Receive the pressed key from MC1 through UART */





uint8 choice;

	while(1)
    {
		choice = UART_recieveByte();
		if(choice == '+'){
			VerifyPassword();
		}
		if(choice=='-'){
			StorePassword();
		}
		if(choice==BUZZ){
			Timer0_setCallBack(BUZZER);
			BUZZER_ON();
			Timer0_init(&T1config);
//			Timer_config config = { timer1,FCPU_1024 ,Timer_CTC,0,7800 };
//			Timer0_init(&config);
//			Timer1_setCallBack(BUZZERHandle);


		}
		if(choice==OPEN_DOOR){
			Timer0_setCallBack(MotorHandle);
			state=DCM_CCW;
			DcMotor_Rotate(state,50);
			Timer0_init(&T0config);



		}




    }

}
