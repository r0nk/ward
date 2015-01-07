typedef struct {
	unsigned char instruction;
	unsigned char a;
	unsigned char b;
	unsigned char size;
}Opcode;
Opcode  readOpcode(word address,char * memory);
int isJump(Opcode o);
int isConditionalJump(Opcode o);
int isValid(Opcode o);
word jumpDestination(Opcode o);
void doInstruction(int * ip, unsigned char * memory);
