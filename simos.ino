#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "sys/fs.cpp"
#include "sys/serial.cpp"
#include "sys/tasks.cpp"
#include "sys/kernel.h"
#include "sys/sh.cpp"
#include "sys/kernel.cpp"

char serialBuf[SERIAL_BUF_SIZE];
//unsigned short eeprom_addr=0;

void boot();

void setup()
{
	cli(); //disable interrupts
	Serial.begin(SERIAL_BAUD_RATE);
	//wait for serial to initialize
	while(!Serial){
		continue; 
	}
	//flush buffer
	while(Serial.available()>0){
		char tmp = Serial.read();
	}
	Serial.print("Initializing kernel...\n");
	kernelInit();
	taskCreate(&boot, (uint16_t)512, (char*)0);
	kernel.taskRaw2Running(0);
}

void boot()
{
	Serial.print("Done!\n");
	Serial.flush();
	sei();//set enabled interrupts. Sets global interrupt mask.
	taskCreate(&testFunc, 256, (char*)0);
	taskCreate(&testFunc2, 256, (char*)0);
	taskCreate(&testFunc3, 256, (char*)0);
	for(uint16_t i=0; i<200; i++)
	{
		serialPrint(i);
		serialPrint('\n');
	}
	//taskTerminate(1);
	taskTerminate(3);
	//call sh
	while(true){
		continue;
	}
}

void loop()
{
	//shGetInput(serialBuf, SERIAL_BUF_SIZE);
	//sh(serialBuf, SERIAL_BUF_SIZE);
}
