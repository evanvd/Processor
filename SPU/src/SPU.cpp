#include <stdio.h>
#include "io.h"
#include "complete_op_from_file.h"

int main()
{
    processor_t spu = {};
    InitSPU(&spu,"native_code.bin");
    PrintMatrix(spu.read_data,spu.size);

    RunCode(&spu);
    StackDump(&spu.stack_data);
    DestroySPU(&spu);
    return 0;
}