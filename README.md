# Brainf**k Native Compiler
The plan for this is a simple brainf**k compiler that compiles to x86-64 assembly. I have never
used assembly before let me know if there is any aggregious mistakes.

**NOTE: Currently on linux is supported for the native compilation.**

## Prerequisites
The native (linux) compiler depends on [nasm](https://www.nasm.us/) and ld.

## Usage
```console
$ git clone https://github.com/Rwn42/Brainfck-compiler
$ cc src/*.c -o bfc
$ ./bfc my_file.bf <compile/run> <optional: output_path>
```
run will use the interpreter compile will turn the file to native code. compile is the default option.

**NOTE: The Interpreter uses the signed char as the defualt type whereas the compiler uses 64 bit integers.**

## Configuration
The `common.h` headerfile contains some useful configuration options for the interpreter and compiler.
1. TAPE_MAX (controls the size of the tape default 1024)
2. NESTING_MAX (controls maximum allowed nesting at one time default 256)
3. ALLOW_OVERFLOW (default 1, if set to 0 the interpreter will dis-allow overflows)
**NOTE: Compiler always allows overflows as of right now**
