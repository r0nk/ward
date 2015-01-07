typedef struct Element Element;
struct Element{
//the address and destination variables point to opcodes in the program image
//moreThan is a array of pointers to elements that this element is more than
	int value;
	word address;//the address of this elements first op
	int numDestinations;
	word *destinations;
	int numMoreThan;
	Element ** moreThan;//this isn't an array of elements, because this
	//element doesn't own them, its parent lattice does.
};
