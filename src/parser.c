#include "include/parser.h"
#include "include/common.h"

typedef struct{
    int ips[NESTING_MAX];
    int sp;
}BlockStack;

void stackPush(BlockStack* b, int val){
    if(b->sp == NESTING_MAX){
        printf("ERROR: Nested Block Limit Reached To Increase The Limit Edit NESTING_MAX in common.h");
        exit(1);
    }
    b->ips[b->sp++] = val;
}

int stackPop(BlockStack *b){
    if(b->sp == 0){
        printf("ERROR: No Starting [ for ending ].");
        exit(1);
    }
    return b->ips[--b->sp];
}

ProgramData BfInstructionsFromFile(const char* filepath){

    FILE* fp = fopen(filepath, "r");

    if(fp == NULL)
    {
        printf("Unable To Open File: %s\n", strerror(errno));
        exit(1);
    }

    fseek(fp, 0,SEEK_END);
    long n = ftell(fp);
    fseek(fp, 0, SEEK_SET);


    //LEXICAL ANALYSIS
    CommandToken *tokens = malloc(n * sizeof(GETC));

    int tokens_added = 0;

    for(int ch = fgetc(fp); ch != EOF; ch = fgetc(fp))
    {
        switch(ch){
            case '+':
                tokens[tokens_added++] = INC;
                break;
            case  '-':
                tokens[tokens_added++] = DEC;
                break;
            case  '>':
                tokens[tokens_added++] = HEADR;
                break;
            case '<':
                tokens[tokens_added++] = HEADL;
                break;
            case '.':
                tokens[tokens_added++] = PUTC;
                break;
            case  ',':
                tokens[tokens_added++] = GETC;
                break;  
            case  '[':
                tokens[tokens_added++] = START_LOOP;
                break;
            case ']':
                tokens[tokens_added++] = END_LOOP;
                break;
            case '\n':
                break;
            default:
                if(isspace(ch)){
                    break;
                }
                printf("Syntax Error: Unrecognized Character %c", ch);
                exit(1);
        }   
    }
    fclose(fp);

    //PARSING (pre-resolving loop ends basically)
    Inst* program = malloc(tokens_added * sizeof(struct Inst));

    BlockStack block_stack = {.sp = 0, .ips = {0}};

    for (int i = 0; i < tokens_added; ++i)
    {
        CommandToken tk = tokens[i];
        if(tk != START_LOOP  && tk != END_LOOP)
        {
            program[i] = (Inst){.operation = tk, .operand=0};
        }
        else if(tk == START_LOOP)
        {
            stackPush(&block_stack, i);
            program[i] = (Inst){.operation = tk, .operand=-1};
        }
        else
        {
            int start_loc = stackPop(&block_stack);
            program[start_loc].operand = i;
            program[i] = (Inst){.operation = tk, .operand=start_loc};
        }
    }
    if(block_stack.sp > 0){
        printf("ERROR: Unclosed Block In Program\n");
        exit(1);
    }

    free(tokens);

    return (ProgramData){program, tokens_added};
}

