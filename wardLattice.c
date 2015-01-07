#include "lattice.h"
int hasDestination(Lattice l, word destination){
	if(l.cardinality==0)
		return 0;
	int i;
	for(i=0;i<l.cardinality;i++)
		if(l.elements[i].address == destination)
			return i;
	return 0;
}
void linkUp(Element *e, Lattice *l){
//if an element e has a destination in one of l's elements, link them to e
	if(l->cardinality==0)
		return;
	if(e->destinations==NULL)
		return;
	int i;
	for(i=0;i<e->numDestinations;i++){
		int a = hasDestination(*l,e->destinations[i]);
		if(a)
			addMoreThan(e,&l->elements[a]);
	}
}
word unhandledDestination(Lattice *l){
//return a unhandled address, or zero if there are none
	int i,j;
	for(i=0;i<l->cardinality;i++)
		for(j=0;j<l->elements[i].numDestinations;j++)
			if(!hasDestination(*l,l->elements[i].destinations[j]))
				return l->elements[i].destinations[j];
	return 0;
}
Element * getElement(Program *p,word addr){
	Element * e = calloc(sizeof(Element),1);
	e->value=0;
	e->address=addr;
	e->numDestinations=0;
	Opcode o;
	do {
		if(addr>MAXMEMORY)
			return e;
		o=readOpcode(p,addr);
		if(!isValid(o))
			return e;
		addr+=o.size;
		e->value++;
	} while(!isJump(o));
	if(isConditionalJump(o)){
		e->numDestinations++;
		e->destinations = malloc(2*sizeof(addr));
		e->destinations[1] = addr+o.size;
	}else{
		e->destinations = malloc(1*sizeof(addr));
	}
	e->numDestinations++;
	e->destinations[0]=jumpDestination(o);
	return e;
}
void freeLattice(Lattice * l){
	int i,j;
	for(i=0;i<l->cardinality;i++){
		free(l->elements[i].destinations);
		free(l->elements[i].moreThan);
	}
	free(l->elements);
	l->elements = malloc(1);
	l->cardinality = 0;
}
void updateLattice(Program *p,Lattice *l){
	int i;
	freeLattice(l);
	Element * e = getElement(p,p->entryPoint);
	addElement(*e,l);
	free(e);
	while(unhandledDestination(l)){
		e = getElement(p,unhandledDestination(l));
		addElement(*e,l);
		free(e);
	}
	for(i=0;i<l->cardinality;i++)
		linkUp(&l->elements[i],l);
}
void copyLattice(Lattice * to, Lattice * from){
//TODO we have to relink each pointer in the lattices
	to->elements=realloc(to->elements,(sizeof(Element))*from->cardinality);
	//copy each element
	to->cardinality=from->cardinality;
	memcpy(to->elements,from->elements,sizeof(Element)*to->cardinality-1);
}
void combineElements(Lattice * l,Element * a,Element * b){
	//combine elements a and b
	Element * c = malloc(sizeof(Element));
	c->value = a->value + b->value;
	c->address = (a->address<b->address)?a->address:b->address;
	c->numDestinations=0;
	//adding destinations is tricky, because a & b might share a few.
	int i,j;
	for(i=0;i<a->numDestinations;i++){
		for(j=0;j<b->numDestinations;j++){
			if(a->destinations[i]==b->destinations[j])
				continue;
			c->numDestinations++;
			c->destinations =
				realloc(c->destinations,
					sizeof(word)*c->numDestinations);
			c->destinations[c->numDestinations++]=
				a->destinations[i];
		}
	}
}
void combineLeastElements(Lattice *l){
	//it's important to keep in mind that the two least elements aren't
	//neccecarily connectable
	if(l->cardinality<2)
		return;
	unsigned int ls,lsi,lsj = 0;//lsi = least sum
	ls = 888888888;
	//ls equals big because we want it to be bigger then the first sum in 
	//the foor loop
	Element *e;
	int i,j,sum;
	for(i=0;i<l->cardinality;i++){
		for(j=0;j<l->elements[i].numDestinations;j++){
			sum=(l->elements[i].value)
				+(l->elements[i].moreThan[j]->value);
			if(sum<ls){
				ls=sum;
				lsi=i;
				lsj=j;
			}
		}
	}
	combineElements(l,&l->elements[lsi],l->elements[lsi].moreThan[lsj]);
}
Lattice * generateRootLattice(Program *p){
	Lattice *l = calloc(1,sizeof(Lattice));
	l->elements = calloc(1,sizeof(Element));
	updateLattice(p,l);
	return l;
}
Lattice * generateDisplayLattice(Lattice root,int desiredNumElements){
	int i;
	Lattice *l = calloc(1,sizeof(Lattice));
	l->elements = calloc(1,sizeof(Element));
	copyLattice(l,&root);
	while(l->cardinality>desiredNumElements)
		combineLeastElements(l);
	return l;
}
