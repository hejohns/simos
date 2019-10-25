#define SERIAL_BUF_SIZE 64
#define SERIAL_BAUD_RATE 9600

#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "sys/serial.cpp"
#include "sys/sh.cpp"

typedef struct file_{
  unsigned char flag;
  unsigned char file[1023];
} file;

char serialBuf[SERIAL_BUF_SIZE];
unsigned short eeprom_addr=0;
file test;

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
    char throw = i%2;
    continue;
  }
  serialPrint("Done!\n");
}

void loop()
{
  shGetInput(serialBuf, SERIAL_BUF_SIZE);
  ramDump();
  sh(serialBuf, SERIAL_BUF_SIZE);
}
