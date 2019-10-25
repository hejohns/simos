#define SERIAL_BUF_SIZE 64
#define SERIAL_BAUD_RATE 9600

#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "sys/fs.cpp"
#include "sys/serial.cpp"
#include "sys/sh.cpp"

char serialBuf[SERIAL_BUF_SIZE];
unsigned short eeprom_addr=0;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  while(!Serial)
  {
    continue; 
  }
  serialFlush();
  serialPrint("Booting...\n");
  for(unsigned long long i=0; i<1000000; i++)
  {
    continue;
  }
  serialPrint("Done!\n");
}

void loop()
{
  shGetInput(serialBuf, SERIAL_BUF_SIZE);
  sh(serialBuf, SERIAL_BUF_SIZE);
}
