//java virtual machine, version 8
//holy structures batman
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
typedef struct{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info attributes[attributes_count];
} method_info;
typedef struct{
	u2 attribute_name_index;
	u4 attribute_length;
	u1 info[attribute_length];
} attribute_info;
typedef struct{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 constantvalue_index;
}
typedef struct{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1 code[code_length];
	u2 exception_table_length;
	{
		u2 start_pc;
		u2 end_pc;
		u2 handler_pc;
		u2 catch_type;
	} exception_table[exception_table_length];
	u2 attributes_count;
	attribute_info attributes[attributes_count];
}
typedef struct{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 number_of_entries;
	stack_map_frame entries[number_of_entries];
} StackMapTable_attribute;
union verification_type_info {
	Top_variable_info;
	Integer_variable_info;
	Float_variable_info;
	Long_variable_info;
	Double_variable_info;
	Null_variable_info;
	UninitializedThis_variable_info;
	Object_variable_info;
}
typdef struct {
	u1 tag = ITEM_Integer; /* 1 */
}Integer_variable_info
typedef struct {
	u1 tag = ITEM_Float; /* 2 */
}Float_variable_info;
typedef struct {
	u1 tag = ITEM_Null; /* 5 */
}Null_variable_info;
typedef struct {
	u1 tag = ITEM_UninitializedThis; /* 6 */
}UninitializedThis_variable_info;
typedef struct {
	u1 tag = ITEM_Object; /* 7 */
	u2 cpool_index;
}Object_variable_info;
typedef struct {
	u1 tag = ITEM_Uninitialized /* 8 */
		u2 offset;
}Uninitialized_variable_info;
typedef struct {
	u1 tag = ITEM_Long; /* 4 */
}Long_variable_info;
typedef struct {
	u1 tag = ITEM_Double; /* 3 */
}Double_variable_info;
union stack_map_frame {
	same_frame;
	same_locals_1_stack_item_frame;
	same_locals_1_stack_item_frame_extended;
	chop_frame;
	same_frame_extended;
	append_frame;
	full_frame;
}
typedef struct {
	u1 frame_type = SAME; /* 0-63 */
}same_frame;
typedef struct {
	u1 frame_type = SAME_LOCALS_1_STACK_ITEM; /* 64-127 */
	verification_type_info stack[1];
}same_locals_1_stack_item_frame;
typedef struct {
	u1 frame_type = SAME_LOCALS_1_STACK_ITEM_EXTENDED; /* 247 */
	u2 offset_delta;
	verification_type_info stack[1];
}same_locals_1_stack_item_frame_extended;
typedef struct {
	u1 frame_type = CHOP; /* 248-250 */
	u2 offset_delta;
}chop_frame;
typedef struct {
	u1 frame_type = SAME_FRAME_EXTENDED; /* 251 */
	u2 offset_delta;
}same_frame_extended;
typedef struct {
	u1 frame_type = APPEND; /* 252-254 */
	u2 offset_delta;
	verification_type_info locals[frame_type - 251];
}append_frame;
typedef struct {
	u1 frame_type = FULL_FRAME; /* 255 */
	u2 offset_delta;
	u2 number_of_locals;
	verification_type_info locals[number_of_locals];
	u2 number_of_stack_items;
	verification_type_info stack[number_of_stack_items];
}full_frame;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 number_of_exceptions;
	u2 exception_index_table[number_of_exceptions];
}Exceptions_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 number_of_classes;
	{
		u2 inner_class_info_index;
		u2 outer_class_info_index;
		u2 inner_name_index;
		u2 inner_class_access_flags;
	} classes[number_of_classes];
}InnerClasses_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 class_index;
	u2 method_index;
}EnclosingMethod_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
}Synthetic_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 signature_index;
}Signature_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 sourcefile_index;
}SourceFile_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 debug_extension[attribute_length];
}SourceDebugExtension_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 line_number_table_length;
	{
		u2 start_pc;
		u2 line_number;
	} line_number_table[line_number_table_length];
}LineNumberTable_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 local_variable_table_length;
	{
		u2 start_pc;
		u2 length;
		u2 name_index;
		u2 descriptor_index;
		u2 index;
	} local_variable_table[local_variable_table_length];
}LocalVariableTable_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 local_variable_type_table_length;
	{
		u2 start_pc;
		u2 length;
		u2 name_index;
		u2 signature_index;
		u2 index;
	} local_variable_type_table[local_variable_type_table_length];
} LocalVariableTypeTable_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
}Deprecated_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 num_annotations;
	annotation annotations[num_annotations];
}RuntimeVisibleAnnotations_attribute;
typedef struct {
	u2 type_index;
	u2 num_element_value_pairs;
	{
		u2
			element_name_index;
		element_value value;
	} element_value_pairs[num_element_value_pairs];
} annotation;
typedef struct {
	u1 tag;
	union {
		u2 const_value_index;
		{
			u2 type_name_index;
			u2 const_name_index;
		} enum_const_value;
		u2 class_info_index;
		annotation annotation_value;
		{
			u2
				num_values;
			element_value values[num_values];
		} array_value;
	} value;
}element_value
typedef struct {
	u2	attribute_name_index;
	u4	attribute_length;
	u2	num_annotations;
	annotation annotations[num_annotations];
}RuntimeInvisibleAnnotations_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 num_parameters;
	{
		u2
			num_annotations;
		annotation annotations[num_annotations];
	} parameter_annotations[num_parameters];
}RuntimeVisibleParameterAnnotations_attribute
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 num_parameters;
	{
		u2
			num_annotations;
		annotation annotations[num_annotations];
	} parameter_annotations[num_parameters];
}RuntimeInvisibleParameterAnnotations_attribute;
typedef struct {
	u2	attribute_name_index;
	u4	attribute_length;
	u2	num_annotations;
	type_annotation annotations[num_annotations];
}RuntimeVisibleTypeAnnotations_attribute;
typedef struct {
	u1 target_type;
	union {
		type_parameter_target;
		supertype_target;
		type_parameter_bound_target;
		empty_target;
		method_formal_parameter_target;
		throws_target;
		localvar_target;
		catch_target;
		offset_target;
		type_argument_target;
	} target_info;
	type_path target_path;
	u2 type_index;
	u2 num_element_value_pairs;
	{
		u2 element_name_index;
		element_value value;
	} element_value_pairs[num_element_value_pairs];
}type_annotation;
typedef struct {
	u1 type_parameter_index;
}type_parameter_target;
typedef struct {
	u2 supertype_index;
}supertype_target;
typedef struct {
	u1 type_parameter_index;
	u1 bound_index;
}type_parameter_bound_target;
typedef struct {} empty_target;
typedef struct {
	u1 formal_parameter_index;
}formal_parameter_target;
typedef struct {
	u2 throws_type_index;
}throws_target;
typedef struct {
	u2 table_length;
	{
		u2 start_pc;
		u2 length;
		u2 index;
	} table[table_length];
}localvar_target;
typedef struct {
	u2 exception_table_index;
}catch_target;
typedef struct {
	u2 offset;
}offset_target;
typedef struct {
	u2 offset;
	u1 type_argument_index;
}type_argument_target;
typedef struct {
	u1 path_length;
	{
		u1 type_path_kind;
		u1 type_argument_index;
	} path[path_length];
}type_path;
typedef struct {
	u2	attribute_name_index;
	u4	attribute_length;
	u2	num_annotations;
	type_annotation annotations[num_annotations];
}RuntimeInvisibleTypeAnnotations_attribute;
typedef struct {
	u2	attribute_name_index;
	u4	attribute_length;
	element_value default_value;
}AnnotationDefault_attribute;
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 num_bootstrap_methods;
	{
		u2 bootstrap_method_ref;
		u2 num_bootstrap_arguments;
		u2 bootstrap_arguments[num_bootstrap_arguments];
	} bootstrap_methods[num_bootstrap_methods];
}BootstrapMethods_attribute
typedef struct {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 parameters_count;
	{
		u2 name_index;
		u2 access_flags;
	} parameters[parameters_count];
}MethodParameters_attribute
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
