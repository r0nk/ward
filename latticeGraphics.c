//the graphics used for drawing a latticies are large enough to justify their
//own file.
#define DESIRED_DISTANCE 2
static const int maxCardinality = 30;
static int nDrawnElements = 0;//number of drawn elements
static DrawnElement * drawnElements;//array of all elements current on screen
int isDrawn(Element * e){
	int i;
	for(i=0;i<nDrawnElements;i++)
		if(drawnElements[i].e==e)
			return i;
	return -1;
}
void drawLine(int x0,int y0,int x1,int y1){
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
void throwElements(Element *e,int x,int y){
	if(!e)
		return;
	int i;
	drawnElements[nDrawnElements++]=(DrawnElement){e,((-7)+rand()%14)+x,y,0};
	if(e->moreThan==NULL)
		return;
	for(i=0;i<e->numMoreThan;i++)
		if(isDrawn(e->moreThan[i])==-1)//If i isn't drawn yet
			throwElements(e->moreThan[i],x,y+2);
}
void linkElements(){
	//draw lines between all the connected drawn elements
	int i,j,k;
	for(i=0;i<nDrawnElements;i++){//for all elements
		for(j=0;j<drawnElements[i].e->numMoreThan;j++){
			k = isDrawn(drawnElements[i].e->moreThan[j]);
			if(k<0){
				debug="could not find line element";
				return;
			}
			drawLine(drawnElements[i].x,drawnElements[i].y,drawnElements[k].x,drawnElements[k].y);
		}
	}
}
void drawElements(){
	int closest=0;//index of closest to ip;
	int i,x,y,z;
	for(i=0;i<nDrawnElements;i++){
		x = drawnElements[i].x;
		y = drawnElements[i].y;
		mvprintw(y,x,"0");
	}
	for(i=0;i<nDrawnElements;i++){
		//find the element with ip in it and highlight it.
		if(((drawnElements[i].e->address)<=(program->instructionPointer))&&
				(drawnElements[i].e->address)>(drawnElements[closest].e->address))
			closest=i;
	}
	attron(COLOR_PAIR(11));
	x = drawnElements[closest].x;
	y = drawnElements[closest].y;
	mvprintw(y,x,"0");
	attroff(COLOR_PAIR(11));
}
void traceLattice(int x, int y, Lattice l){
	//debug verison of draw lattice
	mvprintw(y++,x,"l.cardinality: %i",l.cardinality);
	int i,j;
	for(i=0;i<l.cardinality;i++){
		attron(COLOR_PAIR(i));
//		mvprintw(y++,x,"l.elements[%i]",i);
//		mvprintw(y++,x," .value: %i",l.elements[i].value);
//		mvprintw(y++,x," .numDestinations: %i",l.elements[i].numDestinations);
//		for(j=0;j<l.elements[i].numDestinations;j++)
//			mvprintw(y++,x,"  .destinations[%i]: %i",j,l.elements[i].destinations[j]);
//		mvprintw(y++,x," .numMoreThan: %i",l.elements[i].numMoreThan);
//		mvprintw(y++,x," .address: %i",l.elements[i].address);
		attroff(COLOR_PAIR(i));
	}
	mvprintw(y++,x,"nDrawnElements: %i",nDrawnElements);
	for(i=0;i<nDrawnElements;i++){
		mvprintw(y++,x,"drawnElements[%i]",i);
		mvprintw(y++,x," .x: %i .y: %i",drawnElements[i].x,drawnElements[i].y);
	}
}
void shuffleLattice(int x, int y, Lattice l){
//regenerates the lattice image
	drawnElements = realloc(drawnElements,l.cardinality*sizeof(DrawnElement));
	nDrawnElements=0;
	Element *e = &l.elements[0];//we make e zero first, so its at the top
	throwElements(e,x+5,y);//this function is recursive
}
void drawLattice(Lattice l,int x, int y){
	if(l.cardinality > maxCardinality){
		debug = "Too many elements to draw!";
		return;
	}
	int i;
	//start at the maxima and go down
	if(drawnElements==NULL)
		shuffleLattice(x,y,l);
	linkElements();
	drawElements();
}
