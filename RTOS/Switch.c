#include "Switch.h"




void SwitchInit(){
  DIO_Init(SWITCH_PORT,SWITCH,IN,PULLDOWN);
}

uint8 SwitchPressed(){
  return DIO_ReadPin(SWITCH_PORT,SWITCH);
}