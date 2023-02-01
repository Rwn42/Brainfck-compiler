#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


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

typedef struct Bvm{
    CommandToken *program;
    int program_length;

    char tape[1024];
    int head;
} Bvm;

void BvmDestroy(Bvm *m){
    free(m->program);
}


int main(int argc, char **argv){
    if(argc <= 1)
    {
        printf("No Input File Specified\n");
        exit(1);
    }

    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("Unable To Open File: %s\n", strerror(errno));
        exit(1);
    }

    fseek(fp, 0,SEEK_END);
    long n = ftell(fp);
    fseek(fp, 0, SEEK_SET);

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
                printf("Syntax Error: Unrecognized Character %c", ch);
                exit(1);
        }   
    }

    fclose(fp);

    // for(int i = 0; i < tokens_added; ++i){
    //     printf("%d\n", tokens[i]);
    // }
    
    Bvm m = {tokens, tokens_added, {0}, 0};
    BvmDestroy(&m);
}