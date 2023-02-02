#pragma once

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "./parser.h"
#include "./common.h"


typedef enum BvmError{
    ERR_OVERFLOW,
    ERR_UNDERFLOW,
    ERR_HEAD_OUT_OF_BOUNDS,
    ERR_IP_OUT_OF_BOUNDS,
    ERR_NO_MATCHING_LOOP,
    ERR_NO_ERROR,
    ERR_HALT,
} BvmError;

typedef struct Bvm{
    Inst *program;
    int program_length;
    int ip;

    char tape[TAPE_MAX];
    int head;
} Bvm;

BvmError BvmExecute(Bvm* m);
void BvmDestroy(Bvm *m);