//This handles user input, 

void handle(int in){
	//handles char input
	switch(in){
		case 'R':
			{
			updateLattice(virtualMachine,lattice);
			shuffleLattice(20,0,*lattice);
			}
			break;
		case '`':
			//send the program (being debuged) a char of input
			sendInput(virtualMachine,input());
			break;
		case '~': 
			//continuously send the program(being debugged) input
			{
			int in;
			while((in = input())!='~')
				sendInput(virtualMachine,in);
			}
			break;
		case 'h':
			if(cX>0)
				cX--;
			break;
		case 'j':
			if(cY<LINES-1)
				cY++;
			break;
		case 'k':
			if(cY>0)
				cY--;
			break;
		case 'l':
			if(cX<COLS-1)
				cX++;
			break;
		case 'q':
			endwin();
			exit(0);
			break;
		case ' ':
			singleStep(virtualMachine);
			break;
	}
}
