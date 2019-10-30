#include <avr/interrupt.h>
#include <string.h>

#define lo8(X) (((uint16_t)X)&0x00FF)
#define hi8(X) ((((uint16_t)X)&0xFF00)>>8)

#define TERMINATED 0
#define READY 1
#define RUNNING 2
#define STOPPED 3

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
ISR(__vector_TIMER1_COMPA_vect, ISR_NAKED)
{
	reti();
}

void testFunc()
{       
        while(true){
                continue;
        };
}       

void setup()
{
	for(uint32_t i=0; i<0x0004FFFF; i++)
	{
		contextPush();
		contextPop();
	}
	cli(); //interrupt during task creation would be bad
	void* sp;
	uint16_t i;
	void* func = (void*)(&testFunc);
	//initialize stack
	//note- stack grows down
	sp = (void*)4192;
	*(uint8_t*)(sp--) = lo8(func); //store PC(lo). reti() jmps here 
	*(uint8_t*)(sp--) = hi8(func); //store PC(hi).
	for(i=0; i<=23; i++){
		*(uint8_t*)(sp--) = 0x00;}
	//save args in r24:25 (input arguments stored in these registers)
	*(uint8_t*)(sp--) = 0;
	*(uint8_t*)(sp--) = 0;
	*(uint8_t*)(sp--) = 0x00; //store r26
	*(uint8_t*)(sp--) = 0x00; //store r27
	*(uint8_t*)(sp--) = 0; //store r28- lo8(Y)
	*(uint8_t*)(sp--) = 0; //store r29- hi(Y)
	*(uint8_t*)(sp--) = 0x00; //store r30
	*(uint8_t*)(sp--) = 0x00; //store r31
	*(uint8_t*)(sp--) = 0x00; //SREG
	//initialize task attributes
	SP=(uint16_t)((uint8_t*)sp);
	contextPop();
	for(int i=0; i<2; i++){
}
	//asm("ldi 30,34");
	//asm("ldi 31, 2");
	//asm("call z");
	//asm("nop");
	//((void(*)())(546))();
}

void loop()
{
}
