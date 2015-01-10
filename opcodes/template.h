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
} VirtualMachine;
typedef struct{
	int size;
	word addr;
	//...
}Opcode;
Opcode readOpcode(VirtualMachine vm,word address);
int isJump(Opcode o);//conditional || unconditional return 1
int isConditionalJump(Opcode o);
int isValid(Opcode o);
word jumpDestination(Opcode o);
void doInstruction(VirtualMachine vm);//do the next instruction
