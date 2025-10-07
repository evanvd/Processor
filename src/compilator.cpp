#include <stdio.h>
#include "convert_to_native_code.h"
#include "write_to_file.h"


int main()
{
    asm_t assembler;
    InitAssembler(&assembler,"assembler.asm", "native_code.bin");
    GetFromFile(&assembler);
    PrintStringMatrix(assembler.asm_code, assembler.size);
    
    ConvertToNative(&assembler);

    PrintMatrix(assembler.native_code, assembler.size);

    WriteToFile(&assembler);

    AssemblerDestroy(&assembler);
}
