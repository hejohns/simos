//TinyRealTime- Dan Henriksson, Anton Cervin
#define lo8(X) (((uint16_t)X)&0x00FF)
#define hi8(X) ((((uint16_t)X)&0xFF00)>>8)

#define contextPush() asm(\
		"push __tmp_reg__\n\t"\
		"push __zero_reg__\n\t"\
		"push r2\n\t"\
		"push r3\n\t"\
		"push r4\n\t"\
		"push r5\n\t"\
		"push r6\n\t"\
		"push r7\n\t"\
		"push r8\n\t"\
		"push r9\n\t"\
		"push r10\n\t"\
		"push r11\n\t"\
		"push r12\n\t"\
		"push r13\n\t"\
		"push r14\n\t"\
		"push r15\n\t"\
		"push r16\n\t"\
		"push r17\n\t"\
		"push r18\n\t"\
		"push r19\n\t"\
		"push r20\n\t"\
		"push r21\n\t"\
		"push r22\n\t"\
		"push r23\n\t"\
		"push r24\n\t"\
		"push r25\n\t"\
		"push r26\n\t"\
		"push r27\n\t"\
		"push r28\n\t"\
		"push r29\n\t"\
		"push r30\n\t"\
		"push r31\n\t"\
		"in __tmp_reg__,  __SREG__\n\t"\
		"push __tmp_reg__")
			
#define contextPop() asm(\
		"pop __tmp_reg__\n\t"\
		"out __SREG__, __tmp_reg__\n\t"\
		"pop r31\n\t"\
		"pop r30\n\t"\
		"pop r29\n\t"\
		"pop r28\n\t"\
		"pop r27\n\t"\
		"pop r26\n\t"\
		"pop r25\n\t"\
		"pop r24\n\t"\
		"pop r23\n\t"\
		"pop r22\n\t"\
		"pop r21\n\t"\
		"pop r20\n\t"\
		"pop r19\n\t"\
		"pop r18\n\t"\
		"pop r17\n\t"\
		"pop r16\n\t"\
		"pop r15\n\t"\
		"pop r14\n\t"\
		"pop r13\n\t"\
		"pop r12\n\t"\
		"pop r11\n\t"\
		"pop r10\n\t"\
		"pop r9\n\t"\
		"pop r8\n\t"\
		"pop r7\n\t"\
		"pop r6\n\t"\
		"pop r5\n\t"\
		"pop r4\n\t"\
		"pop r3\n\t"\
		"pop r2\n\t"\
		"pop __zero_reg__\n\t"\
		"pop __tmp_reg__")

const char taskHeader[] = "task header";
const char taskFooter[] = "task footer";

typedef enum state__
{
	terminated,
	raw,
	ready,
	running,
	stopped
} state_;

typedef struct task
{
	char header[strlen(taskHeader)+1];
	void* sTop;
	void* sp; //stack pointer
	state_ state;
	char footer[strlen(taskFooter)+1];
}task;

const char kernelHeader[] = "kernel header";
const char kernelFooter[] = "kernel footer";

typedef struct kernel_T
{
	char header[strlen(kernelHeader)+1];
	void* memptr; //pointer to bottom of stack
	uint8_t nbrOfTasks;
	uint8_t running;
	task tasks[8];
	char footer[strlen(kernelFooter)+1];
}kernel_T;
kernel_T kernel;

void kernelInit()//uint16_t idletask_stack)
{
	//set up timer 1
	TCCR1A = 0b00000000; //normal operation- disconnect OC1, disable pwm
	TCCR1B = 0b00001100; //reset counter on overflow, prescaler=256
	TIMSK1 = 0b00000010; //output compare (OCIE1A) bit set
	OCR1AH = 0x34;//100ms=6250 counts at 256 scale
	OCR1AL = 0xBC;//set to 200ms slices
	strcpy(kernel.header, kernelHeader);
	strcpy(kernel.footer, kernelFooter);
	kernel.memptr = (void*)(RAMEND-128);
	kernel.nbrOfTasks = 0;
	kernel.running = 0;
	TCNT1 = 0x0000; //reset counter 1 (register of timer 1)
}

void taskDestroy(uint8_t taskNumber)
{
	task* taskN = &kernel.tasks[taskNumber];
	kernel.memptr = taskN->sTop;
	kernel.nbrOfTasks--;
}

#define taskRunning2Ready(x) kernel.tasks[x].state=ready

#define taskReady2Running(x) kernel.tasks[x].state=running

#define taskRaw2Running(x) \
			kernel.tasks[x].state = running;\
			kernel.running = x;\
			SP = kernel.tasks[x].sp;\
			contextPop();\
			asm(\
			"pop r31\n\t"\
			"pop r30");\
			TCNT1 = 0x0000

void panic()
{
	cli();
	serialPrint("Kernel panic!\nJumping to bootloader...\n");
	goto *0x0000;
}

//called by timer interrupt. The "meat" of the kernel.
ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
	//prologue
	cli();
	contextPush();
	//serialPrint((uint16_t)kernel.tasks[kernel.running].sp);
	kernel.tasks[kernel.running].sp = SP;
	/*
	serialPrint("Running:");
	serialPrint(kernel.running);
	serialPrint(',');
	serialPrint(kernel.nbrOfTasks);
	serialPrint(',');
	serialPrint((uint16_t)(kernel.tasks[kernel.running].sp));
	serialPrint("memptr:");
	serialPrint((uint16_t)kernel.memptr);
	serialPrint(',');
	serialPrint((uint16_t)SP);
	serialPrint("\n");
	*/
	uint8_t runNext;
	//pop terminated tasks off kernel task stack
	/*
	for(int8_t i=kernel.nbrOfTasks-1; i>=0; i--){
		task* taskN = &kernel.tasks[i];
		if(taskN->state == terminated){
			taskDestroy(i);
			continue;}
		else{
			break;
		}
	}
	*/
	//Round Robin scheduler
	if(kernel.nbrOfTasks <= 0){
		panic();
	}
	else if(kernel.nbrOfTasks == 1){
		runNext=0;
	}
	else{
		uint8_t i = kernel.running+1;
		do{
			//check i bounds
			if(i == kernel.nbrOfTasks){
				i=0;
				continue;
			}
			//process based on state
			task* taskN = &kernel.tasks[i];
			if(taskN->state == stopped){
				i++;
				continue;
			}
			else if(taskN->state == ready){
				//serialPrint("trigger\n");
				//serialPrint(i);
				//serialPrint(kernel.running);
				//serialPrint(kernel.tasks[kernel.running].state);
				taskRunning2Ready(kernel.running);
				taskReady2Running(i);
				kernel.running = i;
				//serialPrint(kernel.running);
				runNext = i;
				break;
			}
			else if(taskN->state == raw){
				//serialPrint(kernel.running);
				//serialPrint(i);
				taskRunning2Ready(kernel.running);
				//serialPrint(kernel.tasks[0].state);
				taskRaw2Running(i);
				sei();
				asm("ijmp");
			}
			else
			{
				//serialPrint(kernel.running);
				//serialPrint(i);
				//serialPrint(kernel.tasks[i].state);
				//serialPrint("Scheduler Failure\n");
				panic();
			}
		} while(true);
	}
	//epilogue
	/*
	serialPrint((uint16_t)(kernel.tasks[0].sp));
	serialPrint('.');
	serialPrint((uint16_t)(kernel.running));
	serialPrint("\n");
	*/
	SP = kernel.tasks[runNext].sp;
	contextPop();
	TCNT1 = 0x0000;
	reti();
}

//all functions below to be called by user
void taskCreate(void(* func)(void*), uint16_t stacksize, char* args)
{
	/*
	serialPrint("memptrBegin:");
	serialPrint((uint16_t)kernel.memptr);
	serialPrint("\n");
	*/
	void* sp;
	uint16_t i;

	//initialize stack
	//note- stack grows down
	task* taskN = &kernel.tasks[kernel.nbrOfTasks];
	kernel.nbrOfTasks++;
	taskN->sTop = kernel.memptr;
	sp = kernel.memptr;
	*(uint8_t*)(sp--) = lo8(func); //store PC(lo). for icall
	*(uint8_t*)(sp--) = hi8(func); //store PC(hi).
	for(i=0; i<=23; i++){
		*(uint8_t*)(sp--) = 0x00;}
	//save args in r24:25 (input arguments stored in these registers)
	*(uint8_t*)(sp--) = lo8(args);
	*(uint8_t*)(sp--) = hi8(args);
	*(uint8_t*)(sp--) = 0x00; //store r26
	*(uint8_t*)(sp--) = 0x00; //store r27
	*(uint8_t*)(sp--) = lo8(taskN->sTop); //store r28- lo8(Y)
	*(uint8_t*)(sp--) = hi8(taskN->sTop); //store r29- hi(Y)
	*(uint8_t*)(sp--) = 0x00; //store r30
	*(uint8_t*)(sp--) = 0x00; //store r31
	*(uint8_t*)(sp--) = 0x00; //SREG
	//initialize task attributes
	kernel.memptr -= (stacksize+33);
	strcpy(taskN->header, taskHeader);
	strcpy(taskN->footer, taskFooter);
	taskN->state = raw;
	taskN->sp = sp;
	/*
	serialPrint((uint16_t)sp);
	serialPrint(",memptrEnd:");
	serialPrint((uint16_t)kernel.memptr);
	serialPrint("\n");
	*/
	TCNT1 = 0x0000;
}

void taskTerminate(uint8_t taskNumber)
{
	cli();
	kernel.tasks[taskNumber].state = terminated;
	sei();
}

void taskStop(uint8_t taskNumber)
{
	cli();
	kernel.tasks[taskNumber].state = stopped;
	sei();
}

void taskResume(uint8_t taskNumber)
{
	cli();
	kernel.tasks[taskNumber].state = ready;
	sei();
}

ISR(BADISR_vect)
{
	cli();
	serialPrint("Catch-all interrupt triggered\n");
	ramDump();
	panic();
}