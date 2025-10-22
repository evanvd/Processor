#include <stdio.h>
#include "convert_to_native_code.h"
#include "write_to_file.h"

const char *asm_filename = "assembler.asm";
const char *native_filename ="native_code.bin";

int main()
{
    asm_t assembler;
    InitAssembler(&assembler, asm_filename, native_filename); // TODO do not hardcode
    GetFromFile(&assembler);
    
    if(ConvertToNative(&assembler) == NoErr) 
    {
        WriteToFile(&assembler);
    }

    AssemblerDestroy(&assembler);
}
