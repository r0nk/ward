Opcode readOpcode(Program * program, word address){
	Opcode o;
	o.size=1;
	o.addr = address;
	o.code = program->memory[address];
	o.program = program;
	return o;
}
int isJump(Opcode o){
	return ((o.code=='[') || (o.code==']'));
}
int isConditionalJump(Opcode o){
	return isJump(o);
}
int isValid(Opcode o){
	return ((o.code=='>')||(o.code=='<')||
		(o.code=='+')||(o.code=='-')||
		(o.code=='.')||(o.code==',')||
		(o.code=='[')||(o.code==']'));
}
word jumpDestination(Opcode o){
	//dont forget about nested loops!
	int i;
	int nLevel = 0;
	if(o.code=='['){
		for(i=1;isValid(readOpcode(o.program,o.addr+i));i++){
			if(readOpcode(o.program,o.addr+i).code==']'){
				if(nLevel==0)
					return o.addr+1;
				nLevel--;
			}
			if(readOpcode(o.program,o.addr+i).code=='[')
				nLevel++;
		}
	}else if(o.code==']'){
		for(i=1;isValid(readOpcode(o.program,o.addr-i));i++){
			if(readOpcode(o.program,o.addr-i).code=='['){
				if(nLevel==0)
					return o.addr-i+1;
				nLevel--;
			}
			if(readOpcode(o.program,o.addr-i).code==']')
				nLevel++;
		}
		return -2;
	}
	return -5;
}
void doInstruction(Program * program){
	Opcode o=readOpcode(program,program->instructionPointer);
	switch(o.code){
		case '>':
			program->dataPointer++;
			break;
		case '<':
			program->dataPointer--;
			break;
		case '+':
			program->memory[program->dataPointer]++;
			break;
		case '-':
			program->memory[program->dataPointer]--;
			break;
		case '.':
			programOutput(program->memory[program->dataPointer]);
			break;
		case ',':
			program->waitingForInput=1;
			break;
		case '[':
			if(!program->memory[program->dataPointer]){
				program->instructionPointer=jumpDestination(o);
				return;
			}
			break;
		case ']':
			if(program->memory[program->dataPointer]){
				program->instructionPointer=jumpDestination(o);
				return;
			}
			break;
	}
	program->instructionPointer++;
}
