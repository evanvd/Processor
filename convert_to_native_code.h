#include <stdio.h>
#include <stdlib.h>
#include "read_from_file.h"

void ConvertToNative(asm_t* assembler);
assembler_err NativeTranslator(char** native_code, char* assembler_text, size_t* index);