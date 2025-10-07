#include <stdio.h>
#include "convert_to_native_code.h"

void PrintStringMatrix(char** data, const size_t size);
void PrintStringMatrix(char** data, const size_t size)
{
    for(size_t index = 0; index < size; index++)
    {
        printf("%s", data[index]);
        printf("\n");
    }
}

int main()
{
    asm_t assembler;
    InitAssembler(&assembler,"assembler.asm", "native_code.txt");
    GetFromFile(&assembler);
    //PrintStringMatrix(assembler.asm_code, assembler.size);
    
    ConvertToNative(&assembler);

    PrintStringMatrix(assembler.native_code, assembler.size);


    fwrite(assembler.native_code, sizeof(char*),assembler.size, assembler.native_file);

    AssemblerDestroy(&assembler);

    InitAssembler(&assembler,"native_code.txt", "random.txt");
    GetFromFile(&assembler);
    PrintStringMatrix(assembler.asm_code, assembler.size);
    AssemblerDestroy(&assembler);
}
