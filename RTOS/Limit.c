#include "Limit.h"



void Limit_Init()
{
	DIO_Init(LIMIT_PORT,LIMIT_1,IN,PULLDOWN);
	DIO_Init(LIMIT_PORT,LIMIT_2,IN,PULLDOWN);
}



uint8 Limit_Pressed(uint8 limit)
{
	return DIO_ReadPin(LIMIT_PORT,limit);
}

