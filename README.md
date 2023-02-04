# Brainf**k Native Compiler
A simple brainf**k compiler (non-optimizing) that compiles to x86-64 assembly. I have never
used assembly before let me know if there is any aggregious mistakes.

**NOTE: Currently on linux is supported for the native compilation.**

## Todo
- [x] support for , in native compiler
- [ ] port interpreter to windows
- [ ] port compiler to windows
- [ ] compiler optimizations

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

## Performance
both clang (for interpreter and compile time) and nasm (for native speed) is using O3 optimizations for this test.
It should be noted the interpreter is checking for out of bounds memory accesses and has the time for parsing the bf file including in its runtime. (neither program was attempted to be optimized on my end as of now).

| Program | Interpreter (s) | Compile Time (s) | Native Speed (s) |
|-|-|-|-|
|mandlebrot.bf | 45.62 | 0.30 | 4.88 |

