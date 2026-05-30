# EDI in C

This project is an implementation of the main EDI program for playing the Game of Amazons. Unlike the main [EDI package](https://github.com/Chad-Glazier/edi), this implementation omits any diagnostic tools or alternative game-playing programs. This version is intended to be built and run on a website.

## Building the Project

Dependencies:
- [Emscripten](https://emscripten.org) is used to compile this program into WebAssembly code that can be run in a browser environment.
- [GCC](https://gcc.gnu.org/) is used to compile the program's tests and benchmarks.
- [LLVM's clang-format](https://clang.llvm.org/docs/ClangFormat.html) is used for formatting the source code.

There are a few scripts set up for building the project from PowerShell. However, since they are basically just calls to `emcc` and `gcc`, they should be trivial to translate to other shells.
- [build.ps1](./build.ps1) uses Emscripten to produce the optimized WebAssembly build.
- [debug.ps1](./debug.ps1) uses Emscripten to compile the program's tests to WebAssembly with a bunch of debugging flags set.
- [run.ps1](./run.ps1) uses GCC to compile the project's main program to an executable and then runs it.
- [test.ps1](./test.ps1) uses GCC to compile the project's tests and then runs them.
- [benchmark.ps1](./benchmark.ps1) uses GCC to compile the project's benchmarks and then runs them.

Apart from building the project, there are also the following scripts:
- [format.ps1](./format.ps1) formats the source code with `clang-format`.

## Using the Program

If you have a WebAssembly build, you can access functions declared in the project from JavaScript through the `Module` object. Functions are accessed like `Module._cFuncName` where `cFuncName` is the name of the global in the C code (note that the `_` prefix is added when accessing it). 

> **NOTE:** Emscripten will eliminate dead code and LLVM will aggressively inline functions. Both of these behaviors can prevent global C objects from appearing in the JavaScript `Module` object. If you want to skip these behaviors and force Emscripten to export a function, you need to use the `EMSCRIPTEN_KEEPALIVE` macro. For example,

```c
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void some_c_func() 
{
	// ...
}
```

At the time of writing, the only functions you should assume will be exported to JavaScript are those written in [main.c](./src/cmd/main.c) with the `EMSCRIPTEN_KEEPALIVE` macro.

### Using the C Library

The core C library can be imported with the [`edi.h`](./src/edi.h) file. Some variables in the program must be precomputed, so you must always run `edi_init()` once before using any of its functions. 
