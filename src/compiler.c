#include "./include/compiler.h"

void writeHeaderLinux(FILE* fp){
    fprintf(fp, "BITS 64\n");
    fprintf(fp, "%%define SYS_EXIT 60\n");
    fprintf(fp, "%%define SYS_WRITE 1\n");
    fprintf(fp, "%%define STDOUT 1\n");
    fprintf(fp, "%%define ENTRY_POINT _start\n");
    fprintf(fp, "global _start\n");
    fprintf(fp, "section .text\n");
    fprintf(fp, "_start:\n");
    fprintf(fp, "mov r12, 0\n");
    fprintf(fp, "lea r14, tape\n");
}


void writeFooterLinux(FILE* fp){
    fprintf(fp, "print:\n");
    fprintf(fp, "   mov rax, SYS_WRITE\n");
    fprintf(fp, "   mov rdi, STDOUT\n");
    fprintf(fp, "   mov rcx, r12\n");
    fprintf(fp, "   imul rcx, 8\n");
    fprintf(fp, "   add rcx, r14\n");
    fprintf(fp, "   mov rsi, rcx\n");
    fprintf(fp, "   mov rdx, 8\n");
    fprintf(fp, "   syscall\n");
    fprintf(fp, "   ret\n");
    fprintf(fp, "exit: \n");
    fprintf(fp, "   mov rax, SYS_EXIT\n");
    fprintf(fp, "   xor rdi, rdi\n");
    fprintf(fp, "   syscall\n");
    fprintf(fp, "section .data\n");
    fprintf(fp, "tape: TIMES %d dd 0 \n", TAPE_MAX);
}

void compileLinux(const char* output_path, ProgramData pd){

    FILE* fp = fopen("out.asm", "w");

    printf("[INFO]: Compiling Into Assembly\n");

    writeHeaderLinux(fp);

    for(int i = 0; i < pd.length; i++){
        Inst inst = pd.program[i];
        switch(inst.operation){
            case INC:
                fprintf(fp, "   inc dword [r14+r12*8]\n");
                break;
            case DEC:
                fprintf(fp, "   dec dword [r14+r12*8]\n");
                break;
            case HEADL:
                fprintf(fp, "   dec r12\n");
                break;
            case HEADR:
                fprintf(fp, "   inc r12\n");
                break;
            case START_LOOP:
                fprintf(fp, "loop_%d:\n", i);
                fprintf(fp, "   mov rax, [r14+r12*8]\n");
                fprintf(fp, "   cmp rax, 0\n");
                fprintf(fp, "   je loop_%d\n", inst.operand);
                break;
            case END_LOOP:
                fprintf(fp, "   mov rax, [r14+r12*8]\n");
                fprintf(fp, "   cmp rax, 0\n");
                fprintf(fp, "   jne loop_%d\n", inst.operand);
                fprintf(fp, "loop_%d:\n", i);
                break;
            case GETC:
                break;
            case PUTC:
                fprintf(fp, "call print\n");
                break;
            } 
    }
    fprintf(fp, "call exit\n");

    writeFooterLinux(fp);
   

    fclose(fp);
    free(pd.program);

    printf("[INFO]: Assembling File\n");

    FILE* nasm_process = popen("nasm -felf64 -O3 out.asm -o out.o", "r");
    pclose(nasm_process);

    printf("[INFO]: Linking Final Executable\n");

    char* command = malloc((strlen(output_path)+25) * sizeof(char));
    sprintf(command, "ld out.o -o %s", output_path);
    FILE* ld_process = popen(command, "r");
    pclose(ld_process);

    remove("out.o");
    remove("out.asm");
}