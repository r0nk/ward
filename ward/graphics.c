#include <curses.h>
#include "latticeGraphics.c"
#include "time.h"
int numOutChars;//number of chars currently output
char * outputDevice;//simulated terminal for debugged program to output to.
void initCurses(){
	initscr();
	start_color();
	use_default_colors();
	init_color(1,700,700,1000);
	init_color(2,500,250,0);
	init_color(0,0,0,0);
	init_pair(0,COLOR_WHITE,-1);
	init_pair(1,COLOR_CYAN,-1);//(cyan on default)
	init_pair(2,COLOR_WHITE,2);
	init_pair(3,1,-1);
	init_pair(4,COLOR_GREEN,-1);
	init_pair(5,COLOR_BLUE,-1);
	init_pair(6,COLOR_YELLOW,-1);
	init_pair(7,COLOR_MAGENTA,-1);
	init_pair(8,COLOR_WHITE,COLOR_BLUE);
	init_pair(9,COLOR_BLACK,COLOR_YELLOW);
	init_pair(10,COLOR_BLACK,COLOR_RED);
	init_pair(11,COLOR_BLACK,COLOR_WHITE);
	cbreak();
	noecho();		
}
void initGraphics(){
	srand(time(NULL));
	numOutChars=0;
	outputDevice = calloc(1,24*80);
	outputDevice[0]='>';
	initCurses();
}
void deInitCurses(){
	endwin();
}
void deInitGraphics(){
	free(outputDevice);
	deInitCurses();
}
void drawHexDump(int xL,int yL,VirtualMachine v,word offset){
//draws out the memory in hex,	16 bytes across, starting at x,y
	int x,y,i;
	i=0;
	for(y=0;y<16;y++){
		for(x=0;x<16;x++){
			if(i==v.instructionPointer){
				attron(COLOR_PAIR(11));
				mvprintw(yL+y,xL+(x*2),"%02x",v.memory[i++]);
				attroff(COLOR_PAIR(11));
				continue;
			}
			if(i==v.dataPointer){
				attron(COLOR_PAIR(2));
				mvprintw(yL+y,xL+(x*2),"%02x",v.memory[i++]);
				attroff(COLOR_PAIR(2));
				continue;
			}
			mvprintw(yL+y,xL+(x*2),"%02x",v.memory[i++]);
		}
	}
}
void drawStatus(int x, int y){
	attron(COLOR_PAIR(6));
	mvprintw(y,x,status);
	attroff(COLOR_PAIR(6));
	attron(COLOR_PAIR(9));
	mvprintw(y,x+(COLS/2),debug);
	attroff(COLOR_PAIR(9));
}
void drawProgramOutput(int x, int y, int width, int height){
	int offset=((80-width)*(24-height))-numOutChars;
	offset=(offset>0)?offset:0;
	mvprintw(y++,x,"program output>");
	mvprintw(y++,x,"%s",(outputDevice+offset));
}
void drawDisassembly(int xL, int yL,VirtualMachine v){
	int i;
	Opcode o;
	for(i=0;i<MAXMEMORY;i++){
		o = readOpcode(&v,v.entryPoint+i);
		if(i==v.instructionPointer){
			attron(COLOR_PAIR(11));
			mvprintw(yL,xL+i,"%c",o.code);
			attroff(COLOR_PAIR(11));
			continue;
		}
		mvprintw(yL,xL+i,"%c",o.code);
	}
}
void drawRegisters(int x, int y/*,Register *regs*/){
//	int i;
//	for(i=0;reg[i]!=NULL;i++)
//		mvprintw(y++,x,"%s:%016llx",regs[i].name,regs[i].value);
	;
}
void redraw(){
	erase();
	drawDisassembly(0,LINES-8,*virtualMachine);
	drawHexDump(COLS-32,0,*virtualMachine,0);
	//drawRegisters(COLS-54,LINES-17,program.regs);
	//drawCurrentOpcode(COLS-80,LINES-30);
	drawProgramOutput(0,LINES-7,80,3);
	drawStatus(0,LINES-1);
	drawLattice(*lattice,5,1);
	move(cY,cX);
	refresh();
}
void programOutput(char c){
	//add a char one at a time to the output stream
	if(c==0)
		return;
	int i;
	if(numOutChars>=((80*3)))
		for(i=0;i<=((80*3));i++)
			outputDevice[i]=outputDevice[i+1];
	else
		numOutChars++;
	outputDevice[numOutChars]=c;
}
int input(){
	return getch();
}
