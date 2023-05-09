#ifndef MOTOR_H_
#define MOTOR_H_


#include "DIO.h"


#define MOTOR_PORT PORTA
#define MOTOR_A_ENABLE 0
#define MOTOR_B_ENABLE 1
#define MOTOR_A_PIN0 2
#define MOTOR_A_PIN1 3
#define MOTOR_B_PIN0 4
#define MOTOR_B_PIN1 5

void MOTOR_A_INIT(void);
void MOTOR_B_INIT(void);

void MOTOR_A_FORWARD(void);
void MOTOR_A_BACKWARD(void);

void MOTOR_B_FORWARD(void);
void MOTOR_B_BACKWARD(void);


void MOTOR_A_STOP(void);

void MOTOR_B_STOP(void);

#endif