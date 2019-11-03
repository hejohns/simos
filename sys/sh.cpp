#define MAX_ARGUMENTS 8
//defined here, but a useful global function
uint8_t isAlphanumeric(char c)
{
	if((c>=48 && c<=57)||(c>=65 && c<=90)||(c>=97 && c<=122))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

typedef struct sh_
{
	void (*getInput)(char*, uint8_t);
	void (*exec)(char*, uint8_t);
} sh_T;
sh_ sh;

void shGetInput(char* buf, uint8_t bufSize)
{
	serialPrint("> ");
	serialRead(buf, bufSize);
	serialPrint(buf);
	serialPrint("\n");
}

unsigned char edit(char* file)
{
}

void shExec(char* buf, uint8_t bufSize)
{
	char cmd[MAX_ARGUMENTS][SERIAL_BUF_SIZE];
	if(buf[0]=='\0'){
		return;}
	{
	uint8_t i;
	uint8_t j=0;
	uint8_t k=0;
	for(i=0; buf[i]!='\0'; i++)
	{
		if(isAlphanumeric(buf[i]))
		{
			cmd[j][k] = buf[i];
			k++;
			continue;
		}
		else if(buf[i]==' ')
		{
			cmd[j][k]='\0';
			j++;
			k=0;
			continue;
		}
		else
		{
			serialPrint("sh: could not parse command\n");
			return;
		}
	}
	cmd[j][k]='\0';
	}
	uint8_t numberArgs=1;
	for(uint8_t i=0; buf[i]!='\0'; i++)
	{
		if(buf[i]==' ')
		{
			numberArgs++;
		}
	}
	if(strcmp(cmd[0],"exec")==0)
	{
		serialPrint("exec\n");
	}
	else if(strcmp(cmd[0],"edit")==0)
	{
		serialPrint("edit\n");
	}
	else
	{
		Serial.write(cmd[0]);
		serialPrint(" is not a valid command\n");
	}
/* debugging
	for(int i=0; i<numberArgs; i++)
	{
	serialPrint(cmd[i]);
	serialPrint("\n");
	}
*/
}

void shInit_()
{
	sh.getInput = &shGetInput;
	sh.exec = &shExec;
}

void ramDump()
{
	Serial.write('\n');
	for(uint8_t* i=0x0000; i<RAMEND-1; i++)
	{
		Serial.write(*i);
	}
	Serial.write('\n');
	Serial.flush();
}
