	//Brainfuck in a nutshell
// '>' increment the data pointer
// '<' decrement the data pointer
// '+' increment the data pointer
// '-' decrement the data pointer
// '.' output the byte at the data pointer
// ',' accept one byte of input, 
	//storing its value in the byte at the data pointer
// '[' if the byte at the data pointer is zero, then instead of moving the 
	//instruction pointer forward to the next command, jump it forward
	//to the command after the matching ']' command
// ']' if the byte at the data pointer is nonzero, then instead of moving the 
	//instruction pointer forward to the next command, jump it back
	//to the command after the matching '[' command

typedef struct{
	char * filename;
	int waitingForInput;
	int fsize;
	int entryPoint;//entryPoint in mapped memory
	int instructionPointer;
	unsigned char * memory;//mapped memory image
	word dataPointer;
	//struct Register regs[100];//process registers
} VirtualMachine;
typedef struct{
	int size;
	word addr;
	char code;
	VirtualMachine * vm;//we have weird jumps, so we need a pointer to our 
			//parent program
}Opcode;
#include "brainfuck.c"
