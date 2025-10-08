#include <stdio.h>
#include "io.h"

int main()
{
    processor_t spu = {};
    InitSPU(&spu,"native_code.bin");
    PrintMatrix(spu.read_data,spu.size);
    DestroySPU(&spu);
}