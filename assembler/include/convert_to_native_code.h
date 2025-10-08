#include <stdio.h>
#include <stdlib.h>
#include "read_from_file.h"

enum op_code
{
    OP_POP  = 1,
    OP_DUMP = 2,
    OP_PUSH = 3,
    OP_ADD  = 4,
    OP_SUB  = 5,
    OP_MUL  = 6,
    OP_DIV  = 7,
    OP_OUT  = 8,
    OP_HLT  = 9
};

void ConvertToNative(asm_t* assembler);
assembler_err NativeTranslator(asm_t* assembler, char* assembler_text);
bool ComparePush(char* assembler_text, asm_t* assembler);