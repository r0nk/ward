//TODO not finished
//This file is used to communicate with gdb. (if its being used)

int init_gdb(const char *fName){
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
	status = "finished initalizing gdb"
	return 1;
}
void sendGdbCommand(COMMAND command){/*TODO send gdb a COMMAND*/}
