#include <stdio.h>
#include "stack.h"
void InitSPU(processor_t* spu, const char* filename);
void GetFromFile(processor_t* spu);
void PrintMatrix(int* data, const size_t size);
void DestroySPU(processor_t* spu);