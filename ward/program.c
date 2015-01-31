#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

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
VirtualMachine * getProgram(int pid,char * filename){
	VirtualMachine *p;
	p = calloc(sizeof(VirtualMachine),1);
	p->instructionPointer=0;
	p->memory = calloc(1000,sizeof(char));
	p->dataPointer=200;//TODO brainfuck dependent
	readFile(filename,p->memory);
	return p;
}
void sendInput(VirtualMachine *v, char input){
	v->memory[v->dataPointer]=input;//TODO this is brainfuck specific
	v->waitingForInput=0;
}
void singleStep(VirtualMachine *v){
	if(v->waitingForInput){
		status = "program is waiting for input";
		return;
	}
	doInstruction(v);
}
