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

void taskCreate_(void(* func)(void*), uint16_t stacksize, char* args)
{
	void* sp;
	uint16_t i;

	//initialize stack
	//note: stack grows down
	task* taskN = &kernel.tasks[kernel.nbrOfTasks];
	kernel.nbrOfTasks++;
	taskN->sTop = kernel.memptr;
	sp = kernel.memptr;
	*(uint8_t*)(sp--) = lo8(func); //store PC for icall
	*(uint8_t*)(sp--) = hi8(func);
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
	//delete line 140?
	TCNT1 = 0x0000;
}
void taskTerminate_(uint8_t taskNumber)
{
	cli();
	kernel.tasks[taskNumber].state = terminated;
	sei();
}
void taskStop_(uint8_t taskNumber)
{
	cli();
	kernel.tasks[taskNumber].state = stopped;
	sei();
}
void taskResume_(uint8_t taskNumber)
{
	cli();
	kernel.tasks[taskNumber].state = ready;
	sei();
}
//functions below NOT to be called by user
void taskRunning2Ready_(uint8_t taskNumber)
{
	kernel.tasks[taskNumber].state = ready;
}
void taskReady2Running_(uint8_t taskNumber)
{
	kernel.tasks[taskNumber].state = running;
}
void taskRaw2Running_(uint8_t taskNumber)
{
	//destroy frames pushed onto stack by C function call
	//(otherwise jmp leaves these frames behind, littering the stack) 
	asm(
	"pop __tmp_reg__\n\t"
	"pop __tmp_reg__\n\t"
	"pop __tmp_reg__\n\t"
	"pop __tmp_reg__\n\t"
	"pop __tmp_reg__\n\t"
	"pop __tmp_reg__");

	kernel.tasks[taskNumber].state = running;
	kernel.running = taskNumber;
	SP = kernel.tasks[taskNumber].sp;
	contextPop();
	asm(
	"pop r31\n\t"
	"pop r30");
	TCNT1 = 0x0000;
	sei();
	asm("ijmp");
}
void taskDestroy_(uint8_t taskNumber)
{
	task* taskN = &kernel.tasks[taskNumber];
	kernel.memptr = taskN->sTop;
	kernel.nbrOfTasks--;
}
void panic()
{
	cli();
	serialPrint("Kernel panic!\nJumping to bootloader...\n");
	goto *0x0000;
}

void kernelInit(uint16_t stackReserve)
{
	//set up timer 1
	TCCR1A = 0b00000000; //normal operation- disconnect OC1, disable pwm
	TCCR1B = 0b00001100; //reset counter on overflow, prescaler=256
	TIMSK1 = 0b00000010; //output compare (OCIE1A) bit set
	OCR1AH = 0x34; //100ms=6250 counts at 256 scale
	OCR1AL = 0xBC; //set to 200ms slices
	strcpy(kernel.header, kernelHeader);
	strcpy(kernel.footer, kernelFooter);
	kernel.memptr = (void*)(RAMEND-stackReserve);
	kernel.nbrOfTasks = 0;
	kernel.running = 0;
	kernel.taskRunning2Ready = &taskRunning2Ready_;
	kernel.taskReady2Running = &taskReady2Running_;
	kernel.taskRaw2Running = &taskRaw2Running_;
	kernel.taskCreate = &taskCreate_;
	kernel.taskTerminate = &taskTerminate_;
	kernel.taskStop = &taskStop_;
	kernel.taskResume = &taskResume_;
	kernel.taskDestroy = &taskDestroy_;
	kernel.shInit = &shInit_;
	TCNT1 = 0x0000; //reset counter 1 (register of timer 1)
}

//called by timer interrupt. The "meat" of the kernel.
ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
	//prologue
	cli();
	contextPush();
	kernel.tasks[kernel.running].sp = SP;
	uint8_t runNext;
	//pop terminated tasks off kernel task stack
	for(int8_t i=kernel.nbrOfTasks-1; i>=0; i--){
		task* taskN = &kernel.tasks[i];
		if(taskN->state == terminated){
			kernel.taskDestroy(i);
			continue;
		}
		else{
			break;
		}
	}
	//Round Robin scheduler
	if(kernel.nbrOfTasks <= 0){
		panic();
	}
	else if(kernel.nbrOfTasks == 1){
		runNext = 0;
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
				kernel.taskRunning2Ready(kernel.running);
				kernel.taskReady2Running(i);
				kernel.running = i;
				runNext = i;
				break;
			}
			else if(taskN->state == raw){
				kernel.taskRunning2Ready(kernel.running);
				kernel.taskRaw2Running(i);
			}
			else
			{
				serialPrint("Scheduler Failure\n");
				panic();
			}
		} while(true);
	}
	//epilogue
	SP = kernel.tasks[runNext].sp;
	contextPop();
	TCNT1 = 0x0000;
	reti();
}

//if called, something very bad has happened
ISR(BADISR_vect)
{
	cli();
	Serial.print("Catch-all interrupt triggered\n");
	Serial.flush();
	ramDump();
	panic();
}
