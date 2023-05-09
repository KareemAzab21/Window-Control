#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "DIO.h"
#include "types.h"
#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_C 2
#define BUTTON_D 3
#define BUT_OBJECT 6
#define BUTTON_PORT 3


void ButtonInit(void);
uint8 ButtonPressed(uint8 button);


#endif