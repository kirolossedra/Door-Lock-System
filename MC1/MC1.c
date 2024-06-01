/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mohamed Tarek
 Description : MC1 Code in Challenge
 Date        : 25/4/2014
 ================================================================================================
 */


#include "uart.h"
#include <util/delay.h> /* For the delay functions */
#include "keypad.h"
#include "lcd.h"
#define ACC 0xF3
#define MAX_ATTEMPTS 3
#define OPEN_DOOR 0xF4
#define BUZZ 0xF5

uint8 Status;
uint8 send;


void writePassword(){
	uint8 key_num;
	uint8 password[5];
	uint8 verify;
	while(!send){
		LCD_displayStringRowColumn(0,0,"Enter new Pass :");
		LCD_displayStringRowColumn(1,0,"     ");
		LCD_moveCursor(1,0);
		for(int i=0; i<5; i++){
					while(!ready){key_num=KEYPAD_getPressedKey(); password[i]=key_num;  LCD_displayCharacter('*'); }

						ready=0;
						_delay_ms(1000);

				}
		LCD_displayStringRowColumn(0,0,"Re-Enter  Pass :");
		LCD_displayStringRowColumn(1,0,"     ");
		LCD_moveCursor(1,0);
		for(int i=0; i<5; i++){
							while(!ready){key_num=KEYPAD_getPressedKey(); if(key_num==password[i]){verify++;}  LCD_displayCharacter('*'); }

								ready=0;
								_delay_ms(1000);

						}
		if(verify==5){
			break;
		}

	}
	LCD_displayStringRowColumn(0,0,"Success..Saving ");
	LCD_displayStringRowColumn(1,0,"			    ");
	for(int i=0; i<5; i++){
				UART_sendByte(password[i]);
				_delay_ms(100);

			}


}
void sendPassword(){


	uint8 key_num;
	int i=MAX_ATTEMPTS;
	for(int i=0; i<5; i++){
			while(!ready){key_num=KEYPAD_getPressedKey(); UART_sendByte(key_num); LCD_displayCharacter('*'); }

				ready=0;
				_delay_ms(1000);

		}


}
uint8 VerifyPassword(){
	uint8 key_num;
	int i = MAX_ATTEMPTS;
	uint8 Decision=0;
	LCD_displayStringRowColumn(0,0,"Enter Password :");
	LCD_displayStringRowColumn(1,0,"                ");
	LCD_moveCursor(1,0);

		for(int i=0; i<5; i++){
			ready=0;
								while(!ready){key_num=KEYPAD_getPressedKey(); UART_sendByte(key_num);  LCD_displayCharacter('*'); }


									_delay_ms(1000);

							}
		Decision=UART_recieveByte();
		if(Decision==ACC){LCD_displayString("Done"); return 1;}
		return 0;









}
void MainMenu(void){
	LCD_displayStringRowColumn(0,0,"+ to Open Door  ");
	LCD_displayStringRowColumn(1,0,"- to Change Pass");
	uint8 choice;  while(!ready){choice=KEYPAD_getPressedKey();}
	ready=0;

	if(choice == '+'){
		uint8 m=0;
		uint8 j=0;
		for(int i=0; i<3; i++){
		UART_sendByte('+');
		j=VerifyPassword();
					if(j==1){
						break;
					}
					else{
						m++;
						LCD_displayStringRowColumn(3,0,"Attempts  :");
						LCD_intgerToString(MAX_ATTEMPTS - i-1);

					}
				}



			if(m==3){
				UART_sendByte(BUZZ);
			}
			else{
				UART_sendByte(OPEN_DOOR);
				LCD_displayStringRowColumn(0,0,"Unlocking Door ..");
				_delay_ms(5000);
			}
			ready=0;
	}
	if(choice == '-'){
		uint8 m=0;
				uint8 j=0;
				for(int i=0; i<3; i++){
				UART_sendByte('+');
				j=VerifyPassword();
							if(j==1){
								break;
							}
							else{
								m++;
								LCD_displayStringRowColumn(3,0,"Attempts  :");
								LCD_intgerToString(MAX_ATTEMPTS - i-1);

							}
						}



					if(m==3){
						UART_sendByte(BUZZ);
						LCD_displayStringRowColumn(0,0,"Error ....   ");
						_delay_ms(5000);
					}
					else{
						UART_sendByte('-');
						writePassword();

					}
					ready=0;
	}



}

int main(void)
{

	int counter=0;
	uint8 password[5];
	LCD_init();
	LCD_displayCharacter('c');

	UART_config uconfig = { STOP_ONE , Parity_STOP , Eight_BITS , 9600};
	UART_init(&uconfig);


	writePassword();
//	writePassword();



	while(1){
		MainMenu();

	}











	while(1)
	{



	}
}
