#define SERIAL_BUF_SIZE 64
#define SERIAL_BAUD_RATE 9600

void serialFlush()
{
  while(Serial.available()>0)
    {
      char tmp = Serial.read();
    }
}

#define serialPrint(x) Serial.print(x); Serial.flush()

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
