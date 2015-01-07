//virtual machine for RIS
#include <stdlib.h>
unsigned char instructionPointer;
unsigned char * memory;//memoryImage
#include "graphics.c"

int checkMagic(FILE * fp){
	char * magic = malloc(3);
	magic[0]=fgetc(fp);
	magic[1]=fgetc(fp);
	magic[2]=fgetc(fp);
	if(magic[0]=='R'&& magic[1]=='I' && magic[2]=='S')
		return 1;
	return 0;
}
void readFile(char * filename){
	memory = malloc(256);
	int i;
	FILE * fp;
	fp = fopen(filename,"r");
	//checkMagic(fp);
	if(!fp)
		return;
	for(i=0;i<256;i++)
		memory[i]=fgetc(fp);
	fclose(fp);
}
void step(){
	unsigned char a = memory[instructionPointer+1];
	unsigned char b = memory[instructionPointer+2];
	switch(memory[instructionPointer]){
		case 0://mov a,b
			memory[a]=memory[b];
			instructionPointer+=3;
			break;
		case 1://add a,b
			memory[a]+=memory[b];
			instructionPointer+=3;
			break;
		case 2://jmp a
			instructionPointer=memory[a];
			return;
			break;//just in case we modify this later
		case 3://jz a,b (jump to a if b is 0)
			if(!memory[b])
				instructionPointer=memory[a];
			break;
		default:
			instructionPointer++;//oh dear, we should be 
			//able to just continue on until we find a opcode
	}
	if(instructionPointer>254)
		instructionPointer = 0;
}
int main(int argc,char *argv[]){
	readFile(argv[1]);
	initGraphics();
	instructionPointer=0;
	while(1){
		input();
		step();
		redraw();
	}
	return 0;
}
