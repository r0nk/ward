//all the globals go in this file
//If it doesn't make sense in this context, it probably shouldn't be a global.
char *status = "<status>";
char *debug = "";
int cX,cY = 0;//cursor x,y
#define MAXMEMORY 256
typedef unsigned int word;//CPU bus width
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//ugly hack because many need to access graphics
void deInitGraphics();
void programOutput(char c);
#include "../ward/globals.c"
#include "program.h"
VirtualMachine * virtualMachine;
#include "../ward/program.c"
#include "../ward/wardLattice.c"
Lattice *lattice;
Lattice *displayLattice;
#include "graphics.h"
#include "../ward/interface.c"
