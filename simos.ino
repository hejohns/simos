#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "sys/fs.cpp"
#include "sys/serial.cpp"
void testFunc2()
{
	for(uint16_t i=0; ; i++)
	{
		serialPrint(i);
		serialPrint("!\n");
	}
}
void testFunc()
{
	for(uint16_t i=0; ; i++)
	{
		serialPrint(i);
		serialPrint("?\n");
	}
}
void taskCreate(void(* func)(void*), uint16_t stacksize, char* args);
void ramDump();
void boot();
#include "sys/kernel.cpp"
#include "sys/sh.cpp"

char serialBuf[SERIAL_BUF_SIZE];
//unsigned short eeprom_addr=0;

void setup()
{
	cli(); //disable interrupts
	Serial.begin(SERIAL_BAUD_RATE);
	while(!Serial)
	{
		continue; 
	}
	serialFlush();
	serialPrint("Initializing kernel...\n");
	kernelInit();
	serialPrint("Done!\n");
	cli();
	taskCreate(&boot, (uint16_t)512, (char*)0);
	taskRaw2Running(0);
	asm("ijmp");
}

void boot()
{
	sei();//set enabled interrupts. Sets global interrupt mask.
	taskCreate(&testFunc, 256, (char*)0);
	taskCreate(&testFunc2, 256, (char*)0);
	for(uint16_t i=0; ; i++)
	{
		serialPrint(i);
		serialPrint('\n');
	}
	//call sh
}

void loop()
{
	//shGetInput(serialBuf, SERIAL_BUF_SIZE);
	//sh(serialBuf, SERIAL_BUF_SIZE);
}
