#include "globals.h"
//TODO getopt(); support

void initProgram(int pid,char* filename){
//read the file, get/make the process, generate lattice etc.
	program = getProgram(0,filename);
	refreshProgramImage();
	lattice = generateRootLattice(program);
	//displayLattice = generateDisplayLattice(*lattice,20);
}
void startLoop(){
	refreshProgramImage();	
	redraw();
	while(1){
		handle(input());
		//we only update the lattice when the user asks us to
		//updateLattice(program,lattice);
		refreshProgramImage(program);
		redraw();
	}
}
void handleOptions(int argc,char* argv[]){
	if(argc<2){
		printf("usage: ward <filename>\n");
		exit(1);
	}
	int opt;
	int pid;//TODO
	while((opt=getopt(argc,argv,"pfg"))!=-1){
		switch(opt){
			case 'p'://then there specifying a pid to attach to.
				break;
			case 'f'://then there specifying a file to read from
				pid=atoi(optarg);
				break;	
			case 'g'://gdb||!gdb
				break;
			default:
				printf("usage: ward -f <filename>\n"
						"or ward -p <pid>\n");
				exit(1);
		}
	}
}
int main(int argc,char* argv[]){
	handleOptions(argc,argv);
	initGraphics();
	initProgram(0,argv[1]);
	startLoop();
	return 0;
}
