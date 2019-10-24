void shGetInput(char* buf, unsigned char bufSize)
{
  serialPrint("> ");
  serialRead(buf, bufSize);
  serialPrint(buf);
  serialPrint("\n");
}

void sh(char* buf, unsigned char bufSize)
{
  unsigned char i=0;
  unsigned char space;
  unsigned char cmd[SERIAL_BUF_SIZE];
  while(i < bufSize)
  {
    if(buf[i]>=33 && buf[i]<=126)
    {
      cmd[i]=buf[i];
      i++;
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
