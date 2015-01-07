Opcode readOpcode(word address,char * memory){
	if((address+3)>MAXMEMORY)
		return;
	Opcode o;
	o.instruction=memory[address];
	o.a=memory[address+1];
	o.b=memory[address+2];
	//a and b are both pointers
	switch(o.instruction){
		case 0://mov a,b
			o.size=3;
			break;
		case 1://add a,b
			o.size=3;
			break;
		case 2://jmp a
			o.size=2;
			break;
		case 3://jz a,b (jump to a if b is zero)
			o.size=3;
			break;
		default:
			o.size=1;
	}
	return o;
}
int isJump(Opcode o){
	return (o.instruction ==2||o.instruction==3);
}
int isConditionalJump(Opcode o){
	return (o.instruction==3);
}
int isValid(Opcode o){
	return (o.instruction<4);
}
word jumpDestination(Opcode o){
	return (o.a);
}
void doInstruction(int *ip,unsigned char * memory){
	//a and b are both pointers
	//unless its a jump, then a is an immediate
	if(*ip+2>MAXMEMORY)
		return;
	unsigned char a = memory[*ip+1];
	unsigned char b = memory[*ip+2];
	switch(memory[*ip]){
		case 0://mov a,b
			memory[a] = memory[b];
			*ip+=3;
			break;
		case 1://add a,b
			memory[a] += memory[b];
			*ip+=3;
			break;
		case 2://jmp a
			*ip = a;
			break;
		case 3://jz a,b (jump to a if b is zero)
			if(memory[b]==0){
				*ip=a;
				break;
			}
			*ip+=3;
			break;
		default:
			*ip+=1;
			break;
	}
}
