#include "DIO.H"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "Motor.h"
#include "Button.h"
#include "Switch.h"
#include "Limit.h"



#define LOCK 			0
#define UNLOCK 		1

xQueueHandle xQueue;
xSemaphoreHandle xBinarySemaphore;
xSemaphoreHandle Mutex;

void Object_Detect()
{
	xSemaphoreTake( Mutex, 0 );//take el mutex
	MOTOR_A_STOP();
	Delay_MS(3000);
	MOTOR_A_BACKWARD();
	Delay_MS(1500);
	MOTOR_A_STOP();
	xSemaphoreGive(  Mutex ); //release el mutex
	
	
}
void Drive_Motor_Forward_AUTO()
{
	 xSemaphoreTake( Mutex, 0 );//take el mutex
	
	while(Limit_Pressed(LIMIT_1)==LOW )
	{
			if(ButtonPressed(BUT_OBJECT)==LOW)
				 {
					 xSemaphoreGive(  Mutex );
					 Object_Detect();
					 return;
				 }

			 MOTOR_A_FORWARD();
	}

	MOTOR_A_STOP();
	
	xSemaphoreGive(  Mutex ); //release el mutex
	
}
void Drive_Motor_Forward_MANUAL()
{
	 xSemaphoreTake( Mutex, 0 );//take el mutex
	
	 MOTOR_A_FORWARD();
	
	
	 xSemaphoreGive(  Mutex ); //release el mutex
	
}


void Drive_Motor_Backward_AUTO()
{
		xSemaphoreTake( Mutex, 0 );//take el mutex
	
	while(Limit_Pressed(LIMIT_2)==LOW)
	{
		 MOTOR_A_BACKWARD();
	}
	
	MOTOR_A_STOP();
	
	  xSemaphoreGive(  Mutex ); //release el mutex
}

void Drive_Motor_Backward_MANUAL()
{
	xSemaphoreTake( Mutex, 0 );//take el mutex
	
	 MOTOR_A_BACKWARD();
	
	  xSemaphoreGive(  Mutex ); //release el mutex
}
void vReceiverTask()
{
	while(1)
	{
		const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
		uint8 action;
		(void) xQueueReceive(xQueue,&action,xTicksToWait);
		if(action==LOCK)
		{
			//take smeaphore
			 xSemaphoreTake( xBinarySemaphore, 0 );
		}
		else{
			//unlock semaphore
			xSemaphoreGive(  xBinarySemaphore );
		}
	}
}
void vSenderTask()
{
	uint8 action;
	while(1)
	{
		   if(SwitchPressed()==HIGH)
       {
          //send to reciever to lock
				 action=LOCK;
				 (void)xQueueSendToBack( xQueue, &action, 0 );
				   
       }
       else
       {
          action=UNLOCK;
				 (void)xQueueSendToBack( xQueue, &action, 0 );
       }
		 if( ButtonPressed(BUTTON_A) == LOW ){

					vTaskDelay(150 / portTICK_RATE_MS);
			 	if(ButtonPressed(BUTTON_A)==HIGH && uxSemaphoreGetCount(xBinarySemaphore)==1)
				 {
					 Drive_Motor_Forward_AUTO();
				 }
 

       while(ButtonPressed(BUTTON_A)==LOW && uxSemaphoreGetCount(xBinarySemaphore)==1 && Limit_Pressed(LIMIT_1)==LOW && ButtonPressed(BUTTON_D)==HIGH)
       {
				 //if(SwitchPressed()==LOW)
					// break;

				 if(ButtonPressed(BUT_OBJECT)==LOW)
				 {
					 Object_Detect();
					 break;
				 }
				 if(SwitchPressed()==HIGH)
				 {
					 break;
				 }
				 

					Drive_Motor_Forward_MANUAL();


         
        }
       MOTOR_A_STOP();


       }

		 if( ButtonPressed(BUTTON_B) == LOW ){

				 vTaskDelay(150 / portTICK_RATE_MS);
				 if(ButtonPressed(BUTTON_B)==HIGH && uxSemaphoreGetCount(xBinarySemaphore)==1)
				 {
					 Drive_Motor_Backward_AUTO();
				 }       

       while(ButtonPressed(BUTTON_B)==LOW && uxSemaphoreGetCount(xBinarySemaphore)==1 && Limit_Pressed(LIMIT_2)==LOW && ButtonPressed(BUTTON_C)==HIGH)
       {
				 if(SwitchPressed()==HIGH)
				 {
					 break;
				 }

					Drive_Motor_Backward_MANUAL();


        }
       MOTOR_A_STOP();

        
       }

		 if( ButtonPressed(BUTTON_C) == LOW ){


					vTaskDelay(150 / portTICK_RATE_MS);
				 if(ButtonPressed(BUTTON_C)==HIGH)
				 {
					 Drive_Motor_Forward_AUTO();
				 }
       while(ButtonPressed(BUTTON_C)==LOW && Limit_Pressed(LIMIT_1)==LOW && ButtonPressed(BUTTON_B)==HIGH)
       {
					if(ButtonPressed(BUT_OBJECT)==LOW)
					{
						Object_Detect();
						break;
					}


				Drive_Motor_Forward_MANUAL();


         
        }
       MOTOR_A_STOP();

       }

		 if( ButtonPressed(BUTTON_D) == LOW ){

				vTaskDelay(150 / portTICK_RATE_MS);
				 if(ButtonPressed(BUTTON_D)==HIGH)
				 {
					 Drive_Motor_Backward_AUTO();
				 }
       while(ButtonPressed(BUTTON_D)==LOW && Limit_Pressed(LIMIT_2)==LOW && ButtonPressed(BUTTON_A)==HIGH)
       {


					Drive_Motor_Backward_MANUAL();


         
        }
       MOTOR_A_STOP();

       }


			 
			 
			 
	}
}

  
int main()
{ 
	xQueue = xQueueCreate( 1, sizeof( uint8 ) );
	vSemaphoreCreateBinary( xBinarySemaphore );
	Mutex=xSemaphoreCreateMutex();
	
	DIO_Init(PORTF,1,OUT,PULLDOWN);
	DIO_Init(PORTF,2,OUT,PULLDOWN);
	 MOTOR_A_INIT();
   ButtonInit();
   SwitchInit();
	 Limit_Init();

	
	
	xTaskCreate( vSenderTask, "Sender ", 240, NULL, 1, NULL );
	xTaskCreate( vReceiverTask, "Receiver", 240, NULL, 2, NULL );
	
	vTaskStartScheduler();
   while(1)
   {


   }



  } 

