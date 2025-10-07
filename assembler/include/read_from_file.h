#include <stdio.h>
#ifndef READ_FROM_FILE_H
#define READ_FROM_FILE_H

struct asm_t
{
    size_t size = 0;
    char **asm_code = NULL;
    int* native_code = NULL;
    FILE *asm_file = NULL;
    FILE *native_file =NULL;
};

enum assembler_err
{
    BadFilenameErr = 0, // TODO add some check
    NoErr = -1,
    FileNull = 1,
    ReadError = 2
};

void GetFromFile(asm_t *assembler);
assembler_err InitAssembler(asm_t* data, const char* asm_filename, const char* native_filename);
size_t NumLines(const char *filename);
void AssemblerDestroy(asm_t *assembler);
#endif 
