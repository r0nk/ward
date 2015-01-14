int gdbInput;//the fd we write to
int gdbOutput;//the fd we read from
int gdbPID;//the pid of gdb, NOT the pid of gdbs debug-e

typedef char *token;//any sequence of digits
#include "gdbInput.h"
#include "gdbOutput.h"
