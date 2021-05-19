/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "usart_driver.h"
#include "Dio.h"
#include "LCD.h"
#include "LcdService.h"
#include "LED.h"
#include "LED_Cfg.h"
#include "Motor_Cfg.h"
#include "motor.h"
#include "Switch.h"
#include "Switch_Cfg.h"
#include "Keypad.h"
#include "Keypad_Cfg.h"
#include "Gpt.h"

#define F_CPU 8000000UL
#include <avr/io.h>

void system_init();

LED_t LED={.Channel=LED_1,.Level=STD_HIGH};
Motor_t HEATER={.Channel1=Heater,.Level=STD_HIGH};
Motor_t MOTOR={.Channel1=Motor,.Level=STD_HIGH};
Switch_t START={.Channel=Start,.Level=STD_HIGH};
Switch_t CANCLE={.Channel=Cancle,.Level=STD_HIGH};
Switch_t DOOR={.Channel=Door,.Level=STD_HIGH};
Switch_t WEIGHT={.Channel=Weight,.Level=STD_HIGH};
Gpt_ConfigType Timer={.Channel=Timer0_,.GenratationMode=Normal,.Prescaler=Prescaler8};

void T_KeypadEnterTime(void*p);
void T_Door(void*p);

TaskHandle_t KeypadEnterTime=NULL;
TaskHandle_t DoorTask=NULL;

EventGroupHandle_t Events=NULL;
EventBits_t Bits=NULL;

#define EventDoor                  1<<0
#define EventKeypad                1<<1

int main (void)
{
	//init priphral
	system_init();          //init program

	//Creat Event
	Events=xEventGroupCreate();

	//Creat tasks
	xTaskCreate(T_KeypadEnterTime,NULL,100,NULL,1,&KeypadEnterTime);
	xTaskCreate(T_Door,NULL,100,NULL,2,&DoorTask);

	//start RTOS
	vTaskStartScheduler();
	

	while(1);

	return 0;
}
void system_init(void)
{
	Dio_Init();
	LCD_init();
	Gpt_Init(&Timer);
	usart_init(9600);
	usart_puts("Started\r\n");
	/*MotorDirectionClockWise(&MOTOR);
	MotorDirectionClockWise(&HEATER);

	while(1)
	{

		if(SwitchStatus(&START)==STD_HIGH)
		{
			LedOn(&LED);
		}
		else
		{
			LedOff(&LED);
		}

	staus=GetKeyState ();

	if(staus!=KeyNotPressed)
			{
					LCD_WriteData(staus);
			}
	}*/

}

void T_KeypadEnterTime(void*p)
{
	u8 time;
	usart_puts("KeyPad\r\n");
	LCD_WriteString("Enter Time");
	Gpt_StartTimer(Timer0_,time);
	while(1)
	{
		time=GetKeyState ();

		if(time!=KeyNotPressed)
		{
				LCD_WriteData(time);
		}
		if(time=='=')
		{
			LCD_CursorMove(2,0);
			LCD_WriteString("Time Entered");
		}
	}

}

void T_Door(void*p)
{
	usart_puts("Door\r\n");
	DDRB=0;
	while(1)
	{
		if(SwitchStatus(&START)==STD_HIGH)
		{
			usart_puts("Door Closed\r\n");
			Bits=xEventGroupSetBits(Events,EventDoor);
			usart_puts("Door Event started\r\n");
		}
	}
}
