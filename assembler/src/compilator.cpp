#include <stdio.h>
#include "convert_to_native_code.h"
#include "write_to_file.h"

int main()
{
    asm_t assembler;
    InitAssembler(&assembler,"assembler.asm", "native_code.bin"); // TODO do not hardcode
    GetFromFile(&assembler);
    
    ConvertToNative(&assembler);
    WriteToFile(&assembler);

    AssemblerDestroy(&assembler);
}
