#include "./include/common.h"
#include "include/interpreter.h"
#include "include/parser.h"
#include <stdio.h>

BvmError BvmExecute(Bvm* m)
{  
    if(m->ip >= m->program_length) return ERR_HALT;
    Inst inst = m->program[m->ip++];
    switch(inst.operation){
        case INC:
            m->tape[m->head]++;
            break;
        case DEC:
            m->tape[m->head]--;
            break;
        case HEADL:
            m->head--;
            break;
        case HEADR:
            m->head++;
            break;
        case PUTC:
            putchar(m->tape[m->head]);
            break;
        case GETC:
            m->tape[m->head] = getchar();
            break;
        case START_LOOP:
            if(m->tape[m->head] == 0) m->ip = inst.operand;
            break;
        case END_LOOP:
            if(m->tape[m->head] != 0) m->ip = inst.operand;
            break;
    }
    return ERR_NO_ERROR;
}

void BvmDestroy(Bvm *m){
    free(m->program);
}