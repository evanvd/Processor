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
    OP_JMP = 50,
    OP_JB = 52,
    OP_CALL = 69,
    OP_RET = 72
};


static size_t labels[10] = {}; 
void FindLabels (char* assembler_text);
typedef bool (*args_fn) (char*, asm_t*);

struct operation
{
    const char* op_name = NULL;
    op_code operation_code;
};
struct args_op
{
    const char* op_name = NULL;
    op_code operation_code;
    args_fn fn = NULL;
};


bool ComparePush(char* assembler_text, asm_t* assembler);
bool ComparePushR(char* assembler_text, asm_t* assembler);
bool ComparePopR(char* assembler_text, asm_t* assembler);
bool CompareJump(char* assembler_text, asm_t* assembler);
bool CompareJB(char* assembler_text, asm_t* assembler);
bool CompareCall(char* assembler_text, asm_t* assembler);

//static args_fn op_arg[] = {ComparePush, ComparePopR, ComparePushR, CompareJump, CompareJB};

const int op_args_count = 6;
const int simple_op_count = 9;

static operation operation [simple_op_count] = 
{
    {.op_name = "POP", .operation_code = OP_POP},
    {.op_name = "DUMP", .operation_code = OP_DUMP},
    {.op_name = "MUL", .operation_code = OP_MUL},
    {.op_name = "SUB", .operation_code = OP_SUB},
    {.op_name = "OUT", .operation_code = OP_OUT},
    {.op_name = "DIV", .operation_code = OP_DIV},
    {.op_name = "HLT", .operation_code = OP_HLT},
    {.op_name = "RET", .operation_code = OP_RET},
    {.op_name = "ADD", .operation_code = OP_ADD}
};

static args_op op_arg[op_args_count] =
{
    {.op_name = "PUSH", .operation_code = OP_PUSH, .fn = ComparePush},
    {.op_name = "POPR", .operation_code = OP_POPR, .fn = ComparePopR},
    {.op_name = "PUSHR", .operation_code = OP_PUSHR, .fn = ComparePushR},
    {.op_name = "JMP", .operation_code = OP_JMP, .fn = CompareJump},
    {.op_name = "JB", .operation_code = OP_JB, .fn = CompareJB},
    {.op_name = "CALL", .operation_code = OP_CALL, .fn = CompareCall},
}; 



void ConvertToNative(asm_t* assembler);
assembler_err NativeTranslator(asm_t* assembler, char* assembler_text);
void FirstPass(asm_t* assembler);