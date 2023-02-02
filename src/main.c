#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/parser.h"
#include "include/interpreter.h"
#include "include/compiler.h"

void interpret(ProgramData pd);

int main(int argc, char **argv){
    if(argc <= 1)
    {
        printf("No Input File Specified\n");
        exit(1);
    }

    ProgramData pd = BfInstructionsFromFile(argv[1]);

    char* mode = "compile";
    if(argc >= 3){
        const char* subcommand = argv[2];
        if(strcmp(subcommand, "run") == 0)
        {
            mode = "run";
        }
        else if(strcmp(subcommand, "compile") == 0);
        else printf("ERROR: Unknown Subcommand %s", subcommand);
    }

    if(strcmp(mode, "run") == 0) interpret(pd);
    free(pd.program);

}

void interpret(ProgramData pd)
{
    Bvm m = {.program_length=pd.length, .program=pd.program, .ip=0, .head=0, .tape={0}};

    while(1){
        BvmError result = BvmExecute(&m);
        if(result == ERR_HALT) exit(0);
        if(result != ERR_NO_ERROR){
            printf("ERROR: %s\n", BvmStrError(result));
            exit(1);
        }
    }
    BvmDestroy(&m);
}