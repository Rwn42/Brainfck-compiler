#include <stdio.h>
#include <stdlib.h>
#include "include/parser.h"
#include "include/interpreter.h"


int main(int argc, char **argv){
    if(argc <= 1)
    {
        printf("No Input File Specified\n");
        exit(1);
    }

    ProgramData pd = BfInstructionsFromFile(argv[1]);

    Bvm m = {.program_length=pd.length, .program=pd.program, .ip=0, .head=0, .tape={0}};

    while(1){
        BvmError result = BvmExecute(&m);
        if(result == ERR_HALT) return 0;
        if(result != ERR_NO_ERROR){
            printf("ERROR: %s\n", BvmStrError(result));
            exit(1);
        }
    }
    BvmDestroy(&m);

}