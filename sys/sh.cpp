#define MAX_ARGUMENTS 8
#define SH_ARGSBUF_MAX 2

//defined here, but a useful global function
uint8_t isAlphanumeric(char c)
{
	if((c>=48 && c<=57)||(c>=65 && c<=90)||(c>=97 && c<=122)){
		return 1;
	}
	else{
		return 0;
	}
}

typedef struct sh
{
	void (*getInput)(char*, uint8_t);
	void (*exec)(char*, uint8_t);
	void (*taskDefsInit)();
	char argsBuf[SH_ARGSBUF_MAX][SERIAL_BUF_SIZE];
} sh_T;
sh_T sh;

void shGetInput(char* buf, uint8_t bufSize)
{
	serialPrint("> ");
	serialRead(buf, bufSize);
	serialPrint(buf);
	serialPrint("\n");
    	//serialFlush();
}

unsigned char edit(char* file)
{
}

void shExec(char* buf, uint8_t bufSize)
{
	char cmd[MAX_ARGUMENTS][SERIAL_BUF_SIZE]={'\0'};
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
		int8_t taskid= -1;
		for(uint8_t i=0; i<MAX_TASK_DEFS; i++){
			if(strcmp(taskDefs.task[i].name, cmd[1])==0){
				taskid=i;
				char args[SERIAL_BUF_SIZE]="";
				for(uint8_t i=2; i<numberArgs; i++){
					strncat(args, cmd[i], SERIAL_BUF_SIZE);
					strcat(args, " ");
				}
				strncpy(sh.argsBuf[0], args, SERIAL_BUF_SIZE);
				cli();
				kernel.taskCreate(taskDefs.task[taskid].fp, 256, sh.argsBuf[0]);
				sei();
				break;
			}
		}
		if(taskid==-1){
			if(numberArgs==1){
				serialPrint("usage: exec [task]\nType 'tasks' to list all tasks\n");
			}
			else{
				serialPrint('\'');
				serialPrint(cmd[1]);
				serialPrint('\'');
				serialPrint(" is not a valid task\n");
			}
		}
	}
	else if(strcmp(cmd[0],"help")==0){
		serialPrint("List of commands:\n");
		serialPrint("edit\nhelp\nstatus\n");
	}
	else if(strcmp(cmd[0],"tasks")==0)
	{
		serialPrint("List of tasks:\n");
		for(uint8_t i=0; i<taskDefs.nbrOfTaskDefs; i++){
			serialPrint(taskDefs.task[i].name);
			serialPrint('\n');
		}
	}
	else if(strcmp(cmd[0],"edit")==0)
	{
		serialPrint("edit\n");
	}
	else if(strcmp(cmd[0],"status")==0)
	{
		serialPrint("Kernel.memptr: ");
		serialPrint((uint16_t)kernel.memptr);
		serialPrint('\n');
		serialPrint("kernel.nbrOfTasks: ");
		serialPrint(kernel.nbrOfTasks);
		serialPrint('\n');
	}
	else if(strcmp(cmd[0],"reboot")==0)
	{
		serialPrint("rebooting...\n");
		goto *0x0000;
	}
	else
	{
		Serial.write(cmd[0]);
		serialPrint(" is not a valid command\n");
	}
}

void shInit_()
{
	sh.getInput = &shGetInput;
	sh.exec = &shExec;
	taskDefsInit();
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
