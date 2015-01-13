typedef char *VALUE;

//"~"
typedef char *CONSOLE-STREAM-OUTPUT;

//"@"
typedef char *TARGET-STREAM-OUTPUT;

//"&"
typedef char *LOG-STREAM-OUTPUT;

typedef union{
	CONSOLE-STREAM-OUTPUT console-stream-output;
       	TARGET-STREAM-OUTPUT target-stream-output;
       	LOG-STREAM-OUTPUT log-stream-output;
} STREAM-RECORD;

typedef union{
	//there seperated by commas
	//"[]" |
	//"["
	VALUE * values;
	RESULT * results;
	//"]"
} LIST;

typedef struct{
	//"{}" |
	//"{"	
	RESULT *results;
	//[","
	//(more results) ]
	//"}"
}tuple;

typedef union{
	char * const;	
	TUPLE tuple;
	LIST list;
} VALUE;

typedef struct{
	VARIABLE variable;
	//"="
	VALUE value;
}RESULT;

typedef union{
	//"stopped" | OTHERS (where OTHERS will be added later)
} ASYNC-CLASS;

typedef union{
	//"done" | "running" | "connected" | "error" | "exit"
	char * class;
} RESULT-CLASS;

typedef struct{
	ASYNC-CLASS async-class;
	//(","
	RESULT * results;
	//)*
} ASYNC-OUTPUT;

typedef struct{
	TOKEN token;
       	//"="
	ASYNC-OUTPUT async-output;
} NOTIFY-ASYNC-OUTPUT;
typedef struct{
	TOKEN token;
       	//"+"
	ASYNC-OUTPUT async-output;
} STATUS-ASYNC-OUTPUT;
typedef struct{
	TOKEN token;
       	//"*"
	ASYNC-OUTPUT async-output;
} EXEC-ASYNC-OUTPUT;

typedef union{
	EXEC-ASYNC-OUTPUT  exec-async-output;
	STATUS-ASYNC-OUTPUT status-async-output;
   	NOTIFY-ASYNC-OUTPUT notify-async-output;
} ASYNC-RECORD;

typedef union{
	ASYNC-RECORD async-record;
	STREAM-RECORD stream-record;
} OUT-OF-BAND-RECORD;

typedef struct{
	TOKEN token;
	//"^"
	RESULT-CLASS result-class;
	//(
	//","
	RESULT * results;
	//)*
	//NL
} RESULT_RECORD;

typedef struct{ 
	OUT-OF-BOUND-RECORD * out-of-bound-records;
	RESULT-RECORD result-record;
	//"(gdb)"
	//NL
} OUTPUT;
