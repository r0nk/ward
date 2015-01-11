int comparable(Element * e1, Element * e2){
	int i;
	for(i=0;i<e1->numMoreThan;i++){
		if(e1->moreThan[i]==e2)
			return 1;
	}
	for(i=0;i<e2->numMoreThan;i++){
		if(e2->moreThan[i]==e1)
			return 1;
	}
	return 0;
}
void addElement(Element e,Lattice *l){
	l->cardinality++;
	l->elements = realloc(l->elements,sizeof(Element)*(l->cardinality));
	l->elements[l->cardinality-1]=e;
	return;	
}
void addDestination(Element *e,word destination){
	int i;
	for(i=0;i<e->numDestinations;i++)//check if we already have destination
		if(destination==e->destinations[i])
			return;
	e->destinations = realloc(e->destinations,
					sizeof(destination)*e->numDestinations);
	e->numDestinations++;
}
void addMoreThan(Element *e, Element * lessThan){
	if(lessThan==NULL)
		return;
	int i;
	for(i=0;i<e->numMoreThan;i++)//check if we already are in lattice
		if(lessThan==e->moreThan[i])
			return;
	e->numMoreThan++;
	e->moreThan=realloc(e->moreThan,sizeof(lessThan)*(e->numMoreThan+1));
	e->moreThan[e->numMoreThan-1]=lessThan;
}
