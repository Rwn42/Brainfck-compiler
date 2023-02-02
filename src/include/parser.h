#pragma  once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum CommandToken{
    INC,
    DEC,
    HEADL,
    HEADR,
    START_LOOP,
    END_LOOP,
    GETC,
    PUTC,
} CommandToken;

typedef struct Inst{
    CommandToken operation;
    int operand;
} Inst;

typedef struct{
    Inst* program;
    int length;
} ProgramData;

ProgramData BfInstructionsFromFile(const char* filepath);