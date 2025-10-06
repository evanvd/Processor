#include <stdio.h>
#include "convert_to_native_code.h"

void PrintStringMatrix(char** data, const size_t size);
void PrintStringMatrix(char** data, const size_t size)
{
    for(size_t index = 0; index < size; index++)
    {
        printf("%s\n", data[index]);
    }
}
int main()
{
    asm_t assembler;
    InitAssembler(&assembler,"assembler.asm");
    GetFromFile(&assembler);
    PrintStringMatrix(assembler.asm_code, assembler.size);

    
    ConvertToNative(&assembler);

    PrintStringMatrix(assembler.native_code, assembler.size);

    AssemblerDestroy(&assembler);
}
