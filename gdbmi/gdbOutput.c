/*TODO as it currently stands, this Is all just related to language structure, it doesn't store anything
  Into OUTPUT yet*/

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
	// the 'for' here is checking if raw is a ascii number, like '0'
	for(i=0;(*raw[0]>48 && *raw[0]<58);i++){
		tkn=realloc(tkn,i+1);
		tkn[i]=*raw[0];
		*raw++;
	}
	if(i>0)
		return atoi(tkn);
	return -1;
}
void getAsyncOutput(int token,char **raw,OUTPUT * out){
	switch(*raw[0]){
		//OUT-OF-BAND-RECORD
		case '*'://EXEC-ASYNC-OUTPUT
		case '+'://STATUS-ASYNC-OUTPUT
		case '='://NOTIFY-ASYNC-OUTPUT
			break;
	}
}
char * getCString(char ** raw){
	//Oh god the hacks I'm so sorry,
	//this is litterally so spaghetti it's making me hungry.
	int i=0;
	while((*raw[i++])!='"');//store the size of the string in i
	char * cstring = calloc(sizeof(char),i);
	i=0;
	while(*raw[i]!='"'){
		//store the string in cstring
		cstring[i]=*raw[i];
		i++;
	}
	*raw+=i+1;//plus 1 to get after the last (")
	return cstring;
}
void getConsoleStreamOutput(char ** raw, OUTPUT * out){
	raw++;//to go after the identifying character
	getCString(raw);
}
void getTargetStreamOutput(char ** raw, OUTPUT * out){
	raw++;//to go after the identifying character
	getCString(raw);
}
void getLogStreamOutput(char ** raw, OUTPUT * out){
	raw++;//to go after the identifying character
	getCString(raw);
}
void getStreamOutput(char **raw,OUTPUT * out){
	/*TODO*/
	switch(*raw[0]){
		case '~'://CONSOLE-STREAM-OUTPUT
			getConsoleStreamOutput(raw,out);
		case '@'://TARGET-STREAM-OUTPUT
			getTargetStreamOutput(raw,out);
		case '&'://LOG-STREAM-OUTPUT
			getLogStreamOutput(raw,out);
			break;
	}
}
void getResultRecord(int token,char **raw,OUTPUT * out){/*TODO*/}
void getOutOfBoundRecord(int token, char ** raw, OUTPUT * out){/*TODO*/
	//TODO malloc some shit here
	switch(*raw[0]){
		//OUT-OF-BAND-RECORD
		case '*'://EXEC-ASYNC-OUTPUT
		case '+'://STATUS-ASYNC-OUTPUT
		case '='://NOTIFY-ASYNC-OUTPUT
			getAsyncOutput(token,raw,out);
			break;
		case '~'://CONSOLE-STREAM-OUTPUT
		case '@'://TARGET-STREAM-OUTPUT
		case '&'://LOG-STREAM-OUTPUT
			getStreamOutput(token,raw,out);
			break;
	}
}
void getRecord(char ** raw,OUTPUT * out){
	if(isEndMsg(*raw))
		return 0;
	int t = getToken(raw);//getToken sometimes modifies raw
	switch(*raw[0]){
		//OUT-OF-BAND-RECORD
		case '*'://EXEC-ASYNC-OUTPUT
		case '+'://STATUS-ASYNC-OUTPUT
		case '='://NOTIFY-ASYNC-OUTPUT
		case '~'://CONSOLE-STREAM-OUTPUT
		case '@'://TARGET-STREAM-OUTPUT
		case '&'://LOG-STREAM-OUTPUT
			getOutOfBoundRecord(t,raw,out);
			break;
		case '^'://RESULT-RECORD
			getResultRecord(t,raw,out);
		default:
			return 0;
	}
	return 1;
}
OUTPUT * parseRawOutput(char * raw){
	while(raw[0]=='\n' || raw[0]=='\r')// get rid of '\r\n's
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