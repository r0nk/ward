#include "element.h"
typedef struct{
	Element * elements;
	int (*order)(Element a, Element b);
	//The function for a order works by returning one of three values(
	//  1 = x more than y
	//  0 = x equals y
	// -1 = x less than y
	//) when given two elements
	int cardinality;//(size)
} Lattice;
#include "../ward/lattice.c"
