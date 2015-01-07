//TODO not finished
//This file is used to communicate with gdb. (if its being used)
int start_gdb(const char *fName){
	status = "starting gdb";
	int rpipefd[2];
	int wpipefd[2];
	pipe(rpipefd);
	pipe(wpipefd);
	gdbPID = fork();	
	if(gdbPID==0){
		dup2(wpipefd[0],STDIN_FILENO);
		dup2(rpipefd[1],STDOUT_FILENO);
		dup2(rpipefd[1],STDERR_FILENO);
		execl("gdb","/bin/gdb","--interpreter==mi","-q",fName);
	}
	gdbInput = wpipefd[1];
	gdbOutput = rpipefd[0];
	startAndStop();
	status = "finished initalizing gdb"
	return 1;
}
int getEntryPoint(){/*TODO*/}
void insertBreak(int addr){//TODO
	//-break-insert
}
void startAndStop(){
	//sets a breakpoint at the first instruction, 
	//then starts the program.
	insertBreak(getEntryPoint());
	//exec-run
}
void stepInstruction(){
	//steps though a single instruction
	//-exec-step-instruction
}
void handleNotifications(){
	//gdb throws random-ass notifications whenever it feels like it,
	//so we have to multithread here.
}
unsigned long long int readMemory(unsigned long long int addr){
	//-data-read-memory-bytes
}
void getRegisters(Register * regs){
	//read registers into regs
	//-data-list-register-names
	//-data-list-register-values
}
void sendGdbMsg(/*message*/){
	//sends gdb a message
}
int parseGdbMsg(){
	//reads through and handles a gdb message
	char c[501]; 
       	read(gdbInput,500,c);
	int i;
	for(i = 0;i<500&&c[i]!='\0';i++){
		switch (c[i]){
			case '"':
				char cstring[500];
				int j = i;
				while(c[i]!='"')
					cstring[i-j]=c[i++];
				break;
		}
	}
}
void getGdbMsg(int token){ 
	//reads a message from gdb
	//the token is used to decide how to use the data, its before every
	//gdb message.
}
