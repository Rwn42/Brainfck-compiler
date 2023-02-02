# Brainf**k Native Compiler
The plan for this is a simple brainf**k compiler that compiles to x86-64 assembly.

**NOTE: Currently on linux is supported for the native compilation.**

## Usage
To Compile the source code: `cc src/*.c -o ./bfc` <br>

To run the native compiler simply `./bfc hello.bf > myfile.asm`<br>
nasm is required to assemble the assembly file to a native executable.

To interpret the brainf*ck file use `./bfc hello.bf run`<br>
*this is recommended to test the program for errors before native compiling. as the native compiler has no runtime checks.*


