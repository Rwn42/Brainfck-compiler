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

    printf("[INFO]: Parsing File\n");
    ProgramData pd = BfInstructionsFromFile(argv[1]);

    if(argc < 3)
    {
        printf("ERROR: Please Provide A Subcommand After Input FIle: run or compile\n");
        exit(1);
    }

    const char* subcommand = argv[2];

    if(strcmp(subcommand, "run") == 0)
    {   
        printf("[INFO]: Starting Interpreter\n");
        interpret(pd);
        exit(1);
    }
    else if(strcmp(subcommand, "compile") == 0);
    else printf("ERROR: Unknown Subcommand %s\n", subcommand);

    if(argc >= 4){
        compileLinux(argv[3], pd);
    }else{
        compileLinux("output", pd);
    }

    printf("[INFO]: Compilation Succeeded\n");
}

void interpret(ProgramData pd)
{
    Bvm m = {.program_length=pd.length, .program=pd.program, .ip=0, .head=0, .tape={0}};

    while(1){
        BvmError result = BvmExecute(&m);
        if(result == ERR_HALT) break;
        if(result != ERR_NO_ERROR){
            printf("ERROR: %s\n", BvmStrError(result));
            exit(1);
        }
    }
    BvmDestroy(&m);
}