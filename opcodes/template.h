//these are all the functions that ward uses, and must be implemented in order
//for ward to work.

typedef struct{
	int pid;
	char * filename;
	int waitingForInput;
	int fsize;
	int entryPoint;//entryPoint in mapped memory
	int instructionPointer;
	unsigned char * memory;//mapped memory image
	//struct Register regs[100];//process registers
}Program;
typedef struct{
	int size;
	word addr;
	//...
}Opcode;
Opcode readOpcode(Program program,word address);
int isJump(Opcode o);
int isConditionalJump(Opcode o);
int isValid(Opcode o);
word jumpDestination(Opcode o);
void doInstruction(Program program);
