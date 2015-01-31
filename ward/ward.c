#include "../include/globals.h"

void startLoop(){
	redraw();
	while(1){
		handle(input());
		//we only update the lattice when the user asks us to
		//updateLattice(program,lattice);
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
				pid=atoi(optarg);
				break;
			case 'f'://then there specifying a file to read from
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
	virtualMachine = getProgram(0,filename);
	lattice = generateRootLattice(virtualMachine);
	startLoop();
	return 0;
}
