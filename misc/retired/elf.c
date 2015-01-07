#include <elf.h>
#include <string.h>
void parseELF(Program p){
//TODO this should check for sys arch
	Elf64_Ehdr e;
	memcpy(&e,p.memory,sizeof(Elf64_Ehdr));
	p.entryPoint = e.e_entry;	
//TODO make it actually find the entrypoint,rather then the common one
	p.entryOffset = p.entryPoint - 0x400000;
	return;
}
