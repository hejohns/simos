#define MAX_NUMBER_OF_TASKS 8

const char taskHeader[] = "task header";
const char taskFooter[] = "task footer";
const char kernelHeader[] = "kernel header";
const char kernelFooter[] = "kernel footer";

typedef enum state
{
	terminated,
	raw,
	ready,
	running,
	stopped
} state_T;

typedef struct task
{
	char header[strlen(taskHeader)+1];
	void* sTop;
	void* sp; //stack pointer
	state_T state;
	char footer[strlen(taskFooter)+1];
}task_T;

typedef struct kernel
{
	char header[strlen(kernelHeader)+1];
	void* memptr; //pointer to bottom of stack
	uint8_t nbrOfTasks;
	uint8_t running;
	task_T tasks[MAX_NUMBER_OF_TASKS];
	char footer[strlen(kernelFooter)+1];
	void (*taskRunning2Ready)(uint8_t);
	void (*taskReady2Running)(uint8_t);
	void (*taskRaw2Running)(uint8_t);
	void (*taskCreate)(void(*)(void*), uint16_t, char*);
	void (*taskTerminate)(uint8_t);
	void (*taskStop)(uint8_t);
	void (*taskResume)(uint8_t);
	void (*taskDestroy)(uint8_t);
	void (*shInit)();
}kernel_T;
kernel_T kernel;

void taskCreate(void(* func)(void*), uint16_t stacksize, char* args);
