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
    OP_HLT  = 9,
    OP_PUSHR = 42,
    OP_POPR = 33,
    OP_JMP = 50 
};

typedef void (*operation_fn_t) (asm_t*, int);

struct operation
{
    const char* op_name = NULL;
    op_code operation_code;
};

void ConvertToNative(asm_t* assembler);
assembler_err NativeTranslator(asm_t* assembler, char* assembler_text);
bool ComparePush(char* assembler_text, asm_t* assembler);
bool ComparePushR(char* assembler_text, asm_t* assembler);
bool ComparePopR(char* assembler_text, asm_t* assembler);
bool CompareJump(char* assembler_text, asm_t* assembler);