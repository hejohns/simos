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
	//void kernelInit(uint16_t stackReserve)
	//whats the minimum safe stackReserve? Using 128 bytes now just to be cautious
	kernelInit(128);
	kernel.taskCreate(&boot, (uint16_t)1024, (char*)0);
	kernel.taskRaw2Running(0);
}

void boot()
{
	Serial.print("Done!\n");
	Serial.flush();
	sei();//set enabled interrupts. Sets global interrupt mask.
	kernel.taskCreate(&testFunc, 256, "SUCCESS");
	kernel.taskCreate(&testFunc2, 256, (char*)0);
	kernel.taskCreate(&testFunc3, 256, (char*)0);
	//kernel.taskTerminate(2);
	//kernel.taskTerminate(3);
	//call sh
	kernel.shInit();
	while(true){
		sh.getInput(serialBuf, SERIAL_BUF_SIZE);
		sh.exec(serialBuf, SERIAL_BUF_SIZE);
	}
}

void loop(){}
