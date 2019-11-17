#define MAX_TASK_DEFS 4
#define MAX_TASK_NAME_LEN 16

/*
 * ALWAYS SAVE ARGS IMMEDIATELY
 *
 * There is limited space reserved in sh.argsBuf for passing arguments
 * copy the string point to by char* arg as a stack variable
 * sh.args.Buf is left up to the user to decide how to allocate
 * Note- do not create more tasks back to back than SH_ARGSBUF_MAX has space for
 * otherwise, your tasks will not have a chance to copy the args before 
 * sh.argsBuf gets overwritten
 */

uint8_t isAlphanumeric(char);

void testFunc(char* arg)
{
	cli();
	uint8_t argLength;
	for(argLength=0; isAlphanumeric(arg[argLength]) || arg[argLength] == ' '; argLength++){}
	char args[argLength+1];
	strncpy(args, arg, argLength);
	sei();
	serialPrint(args);
	serialPrint('\n');
	while(true){}
}
void testFunc2()
{
	for(uint16_t i=0; ; i++)
	{
		asm("nop");
	}
}
void testFunc3()
{
	for(uint16_t i=0; ; i++)
	{
		asm("nop");
	}
}

void testFunc4()
{
	uint32_t i;
	for(i=0; ; i++){
		if(i==0 || i==1<<30 || i==1<<29){
			serialPrint(i);
			serialPrint('\n');
		}
	}
}

//allows function pointers to be identified by string names
typedef struct taskDef{
	char name[MAX_TASK_NAME_LEN];
	void (*fp)(void*, uint16_t, char*);
} taskDef_T;

typedef struct taskDefs{
	taskDef_T task[MAX_TASK_DEFS];
	uint8_t nbrOfTaskDefs;
} taskDefs_T;

taskDefs_T taskDefs;

void taskDefsInit()
{
	for(uint8_t i=0; i<MAX_TASK_DEFS; i++){
		taskDefs.task[i].name[0] = '\0';
	}
	memcpy(taskDefs.task[0].name,"testFunc",10);
	taskDefs.task[0].fp = &testFunc;
	memcpy(taskDefs.task[1].name,"testFunc2",10);
	taskDefs.task[1].fp = &testFunc2;
	memcpy(taskDefs.task[2].name,"testFunc3",10);
	taskDefs.task[2].fp = &testFunc3;
	memcpy(taskDefs.task[3].name,"testFunc4",10);
	taskDefs.task[3].fp = &testFunc4;
	for(taskDefs.nbrOfTaskDefs=0; taskDefs.task[taskDefs.nbrOfTaskDefs].name[0] != '\0'; taskDefs.nbrOfTaskDefs++){}
}
