typedef union{
	char * C-STRING;
	char * NON-BLANK-SEQUENCE;
} PARAMETER;
typedef struct{
	//"-"
	PARAMETER paramter1;
	//" "
	PARAMETER paramter2;
} OPTION;
typedef struct{
	TOKEN token;
	//"-"
	OPERATION operation;
	//" "
	OPTION * options;
	//["--"]
	//" "
	PARAMETER * parameters;
	//NL
} MI_COMMAND;
typedef struct{
	TOKEN token;
	char * cli_command;	
	//NL
} CLI_COMMAND;
typedef union{
	CLI-COMMAND cli-command;
	MI-COMMAND mi-command;
} COMMAND;