const char taskHeader[] = "task header";
const char taskFooter[] = "task footer";
const char kernelHeader[] = "kernel header";
const char kernelFooter[] = "kernel footer";

typedef enum state_
{
	terminated,
	raw,
	ready,
	running,
	stopped
} state_T;

typedef struct task_
{
	char header[strlen(taskHeader)+1];
	void* sTop;
	void* sp; //stack pointer
	state_T state;
	char footer[strlen(taskFooter)+1];
}task;

typedef struct kernel_T
{
	char header[strlen(kernelHeader)+1];
	void* memptr; //pointer to bottom of stack
	uint8_t nbrOfTasks;
	uint8_t running;
	task tasks[8];
	char footer[strlen(kernelFooter)+1];
	void (*taskRunning2Ready)(uint8_t);
	void (*taskReady2Running)(uint8_t);
	void (*taskRaw2Running)(uint8_t);
	void (*taskCreate)(void(*)(void*), uint16_t, char*);
	void (*taskTerminate)(uint8_t);
	void (*taskStop)(uint8_t);
	void (*taskResume)(uint8_t);
	void (*shInit)();
}kernel_T;
kernel_T kernel;

void taskCreate(void(* func)(void*), uint16_t stacksize, char* args);
