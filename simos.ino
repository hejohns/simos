#define SERIAL_BUF_SIZE 64

#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "sys/serial.cpp"
#include "sys/sh.cpp"

typedef struct file_{
  unsigned char flag;
  unsigned char file[1024];
} file;

char serialBuf[SERIAL_BUF_SIZE];
unsigned short eeprom_addr=0;
file test;

void setup()
{
  Serial.begin(9600);
  while(!Serial)
  {
    continue; 
  }
  serialFlush();
  serialPrint("Booting...\n");
  for(unsigned char i=0; i<64000; i++)
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
