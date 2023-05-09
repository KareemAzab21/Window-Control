#ifndef __SWITCH_H__
#define __SWITCH_H__


#include "types.h"
#include "DIO.h"


#define SWITCH_PORT 3
#define SWITCH 7



void SwitchInit();
uint8 SwitchPressed();


#endif