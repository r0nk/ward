Opcode readOpcode(VirtualMachine * v, word address){
	Opcode o;
	o.size=1;
	o.addr = address;
	o.code = v->memory[address];
	o.vm = v;
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
		for(i=1;isValid(readOpcode(o.vm,o.addr+i));i++){
			if(readOpcode(o.vm,o.addr+i).code==']'){
				if(nLevel==0)
					return o.addr+1;
				nLevel--;
			}
			if(readOpcode(o.vm,o.addr+i).code=='[')
				nLevel++;
		}
	}else if(o.code==']'){
		for(i=1;isValid(readOpcode(o.vm,o.addr-i));i++){
			if(readOpcode(o.vm,o.addr-i).code=='['){
				if(nLevel==0)
					return o.addr-i+1;
				nLevel--;
			}
			if(readOpcode(o.vm,o.addr-i).code==']')
				nLevel++;
		}
		return -2;
	}
	return -5;
}
void doInstruction(VirtualMachine * v){
	Opcode o=readOpcode(v,v->instructionPointer);
	switch(o.code){
		case '>':
			v->dataPointer++;
			break;
		case '<':
			v->dataPointer--;
			break;
		case '+':
			v->memory[v->dataPointer]++;
			break;
		case '-':
			v->memory[v->dataPointer]--;
			break;
		case '.':
			programOutput(v->memory[v->dataPointer]);
			break;
		case ',':
			v->waitingForInput=1;
			break;
		case '[':
			if(!v->memory[v->dataPointer]){
				v->instructionPointer=jumpDestination(o);
				return;
			}
			break;
		case ']':
			if(v->memory[v->dataPointer]){
				v->instructionPointer=jumpDestination(o);
				return;
			}
			break;
	}
	v->instructionPointer++;
}
