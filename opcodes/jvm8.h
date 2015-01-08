//java virtual machine, version 8
typedef struct{
	int pid;
	char * filename;
	int waitingForInput;
	int fsize;
	int entryPoint;//entryPoint in mapped memory
	int instructionPointer;
	unsigned char * memory;//mapped memory image
	//struct Register regs[100];//process registers
	//TODO stack stuff
		//frames
			//locals
			//operand stack
			//reference to Run-Time constant pool
	//TODO heap stuff
	//TODO Method Area
	//TODO Run-Time Constant Pool 
} VirtualMachine;
typedef struct{
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	cp_info constant_pool[constant_pool_count-1];
	u2 access_flags;
#define ACC_PUBLIC 0x1
#define ACC_FINAL 0x10
#define ACC_SUPER 0x20
#define ACC_INTERFACE 0x200
#define ACC_ABSTRACT 0x400
#define ACC_SYNTHETIC 0x1000
#define ACC_ANNOTATION 0x2000
#define ACC_ENUM 0x4000
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 interfaces[interfaces_count];
 	u2 fields_count
	field_info fields[fields_count];
	u2 methods_count;
	method_info methods[methods_count];
	u2 attributes_count;
	attributes_info attributes[attributes_count];
} Classfile;
typedef struct{
	u1 tag;
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18
	u1 info[];
} cp_info;
typedef struct{
	u1 tag;
	u2 name_index;
} CONSTANT_Class_info;
typedef struct{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_Fieldref_info;
typedef struct{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_Methodref_info;
typedef struct{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;
typedef struct{
	u1 tag;
	u2 string_index;
} CONSTANT_String_info;
typedef struct{
	u1 tag;
	u4 bytes;
} CONSTANT_Integer_info;
typedef struct{
	u1 tag;
	u4 bytes;
} CONSTANT_Float_info;
typedef struct{
	u1 tag;
	u4 high_bytes;
	u4 low_bytes;
} CONSTANT_Double_info;
typedef struct{
	u1 tag;
	u2 name_index;
	u2 descriptor_index;
} CONSTANT_NameAndType_info;
typedef struct{
	u1 tag;
	u2 length;
	u1 bytes[length];
} CONSTANT_Utf8_info;
typedef struct{
	u1 tag;
	u1 reference_kind;
	u2 reference_index;
} CONSTANT_MethodHandle_info;
typedef struct{
	u1 tag;
	u2 descriptor_index;
} CONSTANT_MethodType_info;
typedef struct{
	u1 tag;
	u2 bootstrap_method_attr_index;
	u2 name_and_type_index;
} CONSTANT_InvokeDynamic_info;
typedef struct{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info attributes[attributes_count];
} field_info;
//leftoff on page 90 of the specification

typedef enum{//if the mnemonics is a c/c++ keyword, its prefixed with '_'
	//constants
	nop,
	aconst_null,
	iconst_m1,
	iconst_0,
	iconst_1,
	iconst_2,
	iconst_3,
	iconst_4,
	iconst_5,
	lconst_0,
	lconst_1,
	fconst_0,
	fconst_1,
	fconst_2,
	dconst_0,
	dconst_1,
	bipush,
	sipush,
	ldc,
	ldc_w,
	ldc2_w,
	//loads
	iload,
	lload,
	fload,
	dload,
	aload,
	iload_0,
	iload_1,
	iload_2,
	iload_3,
	lload_0,
	lload_1,
	lload_2,
	lload_3,
	fload_0,
	fload_1,
	fload_2,
	fload_3,
	dload_0,
	dload_1,
	dload_2,
	dload_3,
	aload_0,
	aload_1,
	aload_2,
	aload_3,
	iaload,
	faload,
	daload,
	aaload,
	baload,
	caload,
	saload,
	//stores
	istore,
	lstore,
	fstore,
	dstore,
	astore,
	istore_0,
	istore_1,
	istore_2,
	istore_3,
	lstore_0,
	lstore_1,
	lstore_2,
	lstore_3,
	fstore_0,
	fstore_1,
	fstore_2,
	fstore_3,
	dstore_0,
	dstore_1,
	dstore_2,
	dstore_3,
	astore_0,
	astore_1,
	astore_2,
	astore_3,
	iastore,
	lastore,
	fastore,
	dastore,
	aastore,
	bastore,
	castore,
	sastore,
	//stack
	pop,
	pop2,
	dup,
	dup_x1,
	dup_x2,
	dup2,
	dup2_x1,
	dup2_x2,
	swap,
	//math
	iadd,
	ladd,
	fadd,
	dadd,
	isub,
	lsub,
	fsub,
	dsub,
	imul,
	lmul,
	fmul,
	dmul,
	idiv,
	ldiv,
	fdiv,
	ddiv,
	irem,
	lrem,
	frem,
	drem,
	ineg,
	lneg,
	fneg,
	dneg,
	ishl,
	lshl,
	ishr,
	lshr,
	iushr,
	lushr,
	iand,
	land,
	ior,
	lor,
	ixor,
	lxor,
	iinc,
	//conversions
	i2l,
	i2f,
	i2d,
	l2i,
	l2f,
	l2d,
	f2i,
	f2l,
	f2d,
	d2i,
	d2l,
	d2f,
	i2b,
	i2c,
	i2s,
	//comparisons
	lcmp,
	fcmpl,
	fcmpg,
	dcmpl,
	dcmpg,
	ifeq,
	ifne,
	iflt,
	ifge,
	ifgt,
	ifle,
	if_icmpeq,
	if_icmpne,
	if_icmplt,
	if_icmpge,
	if_icmpgt,
	if_icmple,
	if_acmpeq,
	if_acmpne,
	//control
	_goto,
	jsr,
	ret,
	tableswitch,
	lookupswitch,
	ireturn,
	lreturn,
	freturn,
	dreturn,
	areturn,
	_return,
	//references
	getstatic,
	putstatic,
	getfield,
	putfield,
	invokevirtual,
	invokespecial,
	invokestatic,
	invokeinterface,
	invokedynamic,
	_new,
	newarray,
	anewarray,
	arraylength,
	athrow,
	checkcast,
	instanceof,
	monitorenter,
	monitorexit,
	//extended
	wide,
	multianewarray,
	ifnull,
	ifnonnull,
	goto_w,
	jsr_w,
	//reserved
	breakpoint
} opcode_mnemonic;
typedef struct{
	int size;
	word addr;
	Opcode_Mnemonics opcode;
	char operands[16];//TODO 16 is a temporary guess
}Opcode;
