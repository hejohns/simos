#include <EEPROM.h>
#include <SoftwareSerial.h>

#define SERIAL_BUF_SIZE 64

char serialBuf[SERIAL_BUF_SIZE];
unsigned short eeprom_addr=0;
char file[1024];

void serialFlush()
{
  while(Serial.available()>0)
    {
      char tmp = Serial.read();
    }
}

void serialPrint(char* str)
{
  for(unsigned char i=0; str[i] != '\0'; i++)
  {
    Serial.write(str[i]);
  }
  Serial.flush();
}

void serialRead(char* buf, unsigned char bufSize)
{
  unsigned char i=0;
  serialFlush();
  while(i < bufSize-1)
  {
    if(Serial.peek()<0 || Serial.peek()>127)
    {
      continue;
    }
    else if(Serial.peek() == '\n')
    {
      break;
    }
    else
    {
      buf[i] = Serial.read();
      i++;
    }
  }
    buf[i]='\0';
}

void shGetInput(char* buf, unsigned char bufSize)
{
  serialPrint("> ");
  serialRead(buf, bufSize);
  serialPrint(buf);
  serialPrint("\n");
}

void sh(char* buf, bufSize)
{
  unsigned char i=0;
  unsigned char space;
  unsigned char cmd[SERIAL_BUF_SIZE];
  while(i < bufSize)
  {
    if(buf[i]>=33 && buf[i]<=126)
    {
      cmd[i]=buf[i];
      i++
    }
    else if(buf[i]==' ')
    {
      space=i;
      i++;
    }
    else if(buf[i]=='\0')
    {
      return;
    }
    else
    {
      serialPrint("Panic!\n");
      return;
    }
  }
}

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
