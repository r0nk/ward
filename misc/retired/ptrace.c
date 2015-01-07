//this implements processes and general memory r/w for a linux specific arch
//all of this is to be replaced with gdb backend
#include <sys/ptrace.h>
#include <sys/user.h>
void attach(int pid){
//attach to a process to analyze
	ptrace(PTRACE_ATTACH,pid,0,0);
}
void getRegisters(int pid,void * regs){
	if(ptrace(PTRACE_GETREGS,pid,0,regs)==-1)
		status = "getRegisters err";
}
void inline traceMe(){
	ptrace(PTRACE_TRACEME,0,0,0);
}
unsigned long long int readMemory(int pid, unsigned long long int addr){
	return __builtin_bswap64(ptrace(PTRACE_PEEKDATA,pid,addr,0));
}
unsigned char readMemoryChar(int pid, unsigned long long int addr){
	return (char)((readMemory(pid,addr)>>56)&0xFF);
}
void singleStep(int pid){
	ptrace(PTRACE_SINGLESTEP,pid,0,0);
	waitpid(pid,0,0);
}
