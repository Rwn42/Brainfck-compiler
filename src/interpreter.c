#include "include/interpreter.h"

BvmError BvmExecute(Bvm* m)
{  
    if(m->ip >= m->program_length) return ERR_HALT;
    Inst inst = m->program[m->ip++];
    switch(inst.operation){
        case INC:
            if(m->tape[m->head] == BACKING_TYPE_MAX && !ALLOW_OVERFLOW) return ERR_OVERFLOW;
            m->tape[m->head]++;
            break;
        case DEC:
            if(m->tape[m->head] == BACKING_TYPE_MIN && !ALLOW_OVERFLOW) return ERR_UNDERFLOW;
            m->tape[m->head]--;
            break;
        case HEADL:
            if(m->head == 0) return ERR_HEAD_OUT_OF_BOUNDS;
            m->head--;
            break;
        case HEADR:
            if(m->head == (TAPE_MAX-1)) return ERR_HEAD_OUT_OF_BOUNDS;
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
            if(m->ip < 0 || m->ip > m->program_length) return ERR_IP_OUT_OF_BOUNDS;
            break;
        case END_LOOP:
            if(m->tape[m->head] != 0) m->ip = inst.operand;
            if(m->ip < 0 || m->ip > m->program_length) return ERR_IP_OUT_OF_BOUNDS;
            break;
    }
    return ERR_NO_ERROR;
}

const char* BvmStrError(BvmError e){
    switch(e){
    case ERR_OVERFLOW:
        return "Integer Overflow Signed Char Is the Limit";
    case ERR_UNDERFLOW:
        return "Integer Underflow Signed Char Is the Limit";
    case ERR_HEAD_OUT_OF_BOUNDS:
        return "Memory Pointer Out Of Tape Bounds";
    case ERR_IP_OUT_OF_BOUNDS:
        return "Invalid Instruction Offset Or Program Complete";
    case ERR_NO_ERROR:
        return "No Error Instruction Executed";
    case ERR_HALT:
        return "Program Over";
      break;
    }
}


void BvmDestroy(Bvm *m){
    free(m->program);
}