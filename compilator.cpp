#include <stdio.h>
#include "read_from_file.h"

int main()
{
    asm_t assembler;
    InitAssembler(&assembler,"assembler.asm");
    GetFromFile(&assembler);
    AssemblerDestroy(&assembler);
}
