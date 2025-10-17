#include <stdio.h>
#include "stack.h"
#ifndef IO_H
#define IO_H

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

void color_printf(const char* color, const char* format, ...);

void InitSPU(processor_t* spu, const char* filename);
void GetFromFile(processor_t* spu);
void PrintMatrix(int* data, const size_t size);
void DestroySPU(processor_t* spu);

#endif