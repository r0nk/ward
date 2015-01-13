static int isEndMsg(char * c){
	if(*raw[0]=='(' &&
	   *raw[1]=='g' &&
	   *raw[2]=='d' &&
	   *raw[3]=='b' &&
	   *raw[4]==')')
	{
		return 1;	
	}
}
void handleGdbOutput(){
	char * outs = getRawGdbOutput();
	OUTPUT * out = parseRawOutput(outs);
	free(outs);
}
int getToken(char ** raw){// ** because we move the * around
	int i;
	char * tkn;
	// the for here is checking if raw is a number character, like '0'
	for(i=0;(*raw[0]>48 && *raw[0]<58);i++){
		tkn=realloc(tkn,i+1);
		tkn[i]=*raw[0];
		*raw++;
	}
	if(i>0)
		return atoi(tkn);
	return -1;
}
void getAsyncOutput(int token,char **raw,OUTPUT * out){/*TODO*/}
void getStreamOutput(int token,char **raw,OUTPUT * out){/*TODO*/}
void getResultRecord(int token,char **raw,OUTPUT * out){/*TODO*/}
void getRecord(char ** raw,OUTPUT * out){
	if(isEndMsg(*raw))
		return 0;
	int t = getToken(raw);//getToken modifies raw
	switch(*raw[0]){
		//OUT-OF-BAND-RECORD
		case '*'://EXEC-ASYNC-OUTPUT
		case '+'://STATUS-ASYNC-OUTPUT
		case '='://NOTIFY-ASYNC-OUTPUT
			getAsyncOutput(t,raw,out);
			break;
		case '~'://CONSOLE-STREAM-OUTPUT
		case '@'://TARGET-STREAM-OUTPUT
		case '&'://LOG-STREAM-OUTPUT
			getStreamOutput(t,raw,out);
			break;
		case '^'://RESULT-RECORD
			getResultRecord(t,raw,out);
		default:
			return 0;
			
	}
	return 1;
}
OUTPUT * parseRawOutput(char * raw){
	while(raw[0]=='\n')// get rid of '\n's
		raw++;
	OUTPUT out = malloc(sizeof(OUTPUT));
	while(getRecord(raw,&out));
}
char * getRawGdbOutput(){
	/* TODO this function makes Ricky Bobby cry. */
	unsigned int bytesRead=0;
	char * msg;
	/*every OUTPUT from gdb ends with "(gdb)", so we read till we hit it.*/
	while(1){
		read(gdbOutput,msg+bytesRead,1);
		if(bytesRead>4 && isEndMsg(msg+bytesRead-4)
			return msg;
	}
	return -1;
}
