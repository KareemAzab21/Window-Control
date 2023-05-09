#include "Button.h"



void ButtonInit(){
  DIO_Init(BUTTON_PORT,BUTTON_A,IN,PULLUP);
  DIO_Init(BUTTON_PORT,BUTTON_B,IN,PULLUP);
  DIO_Init(BUTTON_PORT,BUTTON_C,IN,PULLUP);
  DIO_Init(BUTTON_PORT,BUTTON_D,IN,PULLUP);
	DIO_Init(BUTTON_PORT,BUT_OBJECT	,IN,PULLUP);
}


uint8 ButtonPressed(uint8 button){
  return DIO_ReadPin(BUTTON_PORT,button);
}