void shGetInput(char* buf, unsigned char bufSize)
{
  serialPrint("> ");
  serialRead(buf, bufSize);
  serialPrint(buf);
  serialPrint((const char*)"\n");
}

void ramDump()
{
  serialPrint((const char*)"\n");
  for(char* i=0; i<8191; i++)
  {
    Serial.write(*i);
  }
  serialPrint((const char*)"\n");
  Serial.flush();
}

void sh(char* buf, unsigned char bufSize)
{
  unsigned char i=0;
  unsigned char j=0;
  unsigned char space[SERIAL_BUF_SIZE/4];
  for(int k=0; k<SERIAL_BUF_SIZE/4; k++){
  space[k]='\0';}
  unsigned char cmd[SERIAL_BUF_SIZE];
  serialPrint("sh running\n");
  while(i < bufSize)
  {
    if(buf[i]>=33 && buf[i]<=126)
    {
      cmd[i]=buf[i];
      i++;
      continue;
    }
    else if(buf[i]==' ')
    {
      space[j]=i;
      j++;
      i++;
      continue;
    }
    else if(buf[i]=='\0')
    {
      cmd[i] = '\0';
      break;
    }
    else
    {
      serialPrint("Panic!\n");
      Serial.write(buf[i]);
      return;
    }
  }
  serialPrint(cmd);
  serialPrint('\n');
}
