#include <stdio.h>
#include <stdlib.h>
#include "io.h"

enum op_code
{
    OP_POP  = 33,
    OP_DUMP = 2,
    OP_PUSH = 42,
    OP_ADD  = 4,
    OP_SUB  = 5,
    OP_MUL  = 6,
    OP_DIV  = 7,
    OP_OUT  = 8,
    OP_HLT  = -1,
    OP_JB = 50
};

void RunCode(processor_t* spu);
void CallOperation(processor_t* spu);