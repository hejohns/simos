#define MAX_TASK_DEFS 4

void testFunc()
{
	for(uint16_t i=0; ; i++)
	{
		asm("nop");
	}
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
	uint16_t i;
	for(i=0; i<65000; i++){}
	serialPrint(i);
}

//allows function pointers to be matched to string names
typedef struct taskDef_{
	char* name;
	void (*fp)(void*, uint16_t, char*);
} taskDef;

taskDef taskDefs[MAX_TASK_DEFS];

void taskDefsInit_()
{
	taskDefs[0].name = "testFunc";
	taskDefs[0].fp = &testFunc;
	taskDefs[1].name = "testFunc2";
	taskDefs[1].fp = &testFunc2;
	taskDefs[2].name = "testFunc3";
	taskDefs[2].fp = &testFunc3;
	taskDefs[3].name = "testFunc4";
	taskDefs[3].fp = &testFunc4;
}
