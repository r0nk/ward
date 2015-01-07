#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void parseHeader(Program p){
	//store the information from the file header into the program struct
//	if(strncmp(p.memory,"\x7F""ELF",4) == 0){
//		parseELF(p);
//		return;
//	}
//	status = "File not recognized as any known executable";
	;
}
int getFileSize(char *filename){
	struct stat st;
	stat(filename,&st);
	return (int)st.st_size;
}
void readFile(char * filename,char * memory){
	int i,c;
	FILE * fp;
	fp = fopen(filename,"r");
	//checkMagic(fp);
	if(!fp)
		errExit("!fp",1);
	for(i=0;i<956;i++){
		memory[i]=fgetc(fp);
		if(memory[i]==EOF){
			memory[i]=0;
			break;
		}
	}
	for(;i<956;i++)//zero out the rest
		memory[i]=0;
	fclose(fp);
}
Program * getProgram(int pid,char * filename){
//TODO make the program decide to either go with gdb or our opcodes
	Program *p;
	p = calloc(sizeof(Program),1);
	p->instructionPointer=0;
	p->memory = calloc(1000,sizeof(char));
	p->dataPointer=200;//TODO brainfuck dependent
	readFile(filename,p->memory);

	//if(!pid){
	//	start_gdb(filename);
	//}else{
	//	//attach ourselves to the process
	//	attach(pid);
	//}
	return p;
}
word getInstructionPointer(Program p){
	return p.instructionPointer;
	//return p.regs.rip;
}
void mapOpcodes(Program *p,word insp,int i){
//maps opcodes into instructions, starting at insp
}
void refreshProgramImage(){
//refreshes the registers, memory image, etc. of the program.
	//getRegisters(program.pid,&program.regs);
	//mapOpcodes(&p,getInstructionPointer(p));  //TODO
}
void sendInput(Program *p, char input){
	p->memory[p->dataPointer]=input;//TODO this is brainfuck specific
	p->waitingForInput=0;
}
void singleStep(Program *p){
	if(p->waitingForInput){
		status = "program is waiting for input";
		return;
	}
	doInstruction(p);
}
