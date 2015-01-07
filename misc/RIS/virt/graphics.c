#include <curses.h>
int count;
void initCurses(){
	initscr();
	start_color();
	use_default_colors();
	init_color(1,700,700,1000);
	init_color(0,0,0,0);
	init_pair(0,COLOR_WHITE,-1);
	init_pair(1,COLOR_CYAN,-1);//(cyan on default)
	init_pair(2,COLOR_WHITE,-1);
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
	initCurses();
}
void drawLine(int x0,int y0,int x1,int y1){
//this was copy-pasted off some site, I know the formatting is horrific
	int dx=abs(x1-x0),sx=x0<x1?1:-1;
	int dy=abs(y1-y0),sy=y0<y1?1:-1;
	int err=(dx>dy?dx:-dy)/2,e2;
	char *c;
	while(!(x0==x1&&y0==y1)){
		e2 = err;
		if(e2>-dx){
			c="_";
			err-=dy;
			x0+=sx;
		}
		if(e2<dy){
			c="|";
			err+=dx;
			y0+=sy;
		}
		if(e2<dy&&e2>-dx)
			if(sy>0)
				c=(sx>0)?"\\":"/";
			else
				c=(sx>0)?"/":"\\";
		if(!(x0==x1&&y0==y1)){
			if(c=="_"&&sy<0)
				mvprintw(y0-1,x0,c);
			else
				mvprintw(y0,x0,c);
		}
	}
}
void drawHexDump(int xLoc,int yLoc){
	int x,y,i;
	i=0;
	for(y=0;y<16;y++){
		for(x=0;x<16;x++){
			if(i==instructionPointer){
				attron(COLOR_PAIR(11));
				mvprintw(yLoc+y,xLoc+(x*2),"%02x",memory[i++]);
				attroff(COLOR_PAIR(11));
			}else{
				mvprintw(yLoc+y,xLoc+(x*2),"%02x",memory[i++]);
			}
		}
	}
}
void redraw(){
	erase();
	drawHexDump(0,0);
	mvprintw(20,40,"count:%i",count++);
	mvprintw(21,40,"instructionPointer:%i",instructionPointer);
	refresh();
}
int input(){
	return getch();
}
