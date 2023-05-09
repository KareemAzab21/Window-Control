#ifndef LIMIT_H_
#define LIMIT_H_


#include "types.h"
#include "DIO.h"

#define LIMIT_PORT 4
#define LIMIT_1   1
#define LIMIT_2   2



void Limit_Init(void);




uint8 Limit_Pressed(uint8 limit);





#endif