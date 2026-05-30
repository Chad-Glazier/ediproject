# EDI in C

This project is an implementation of the main EDI program for playing the Game of Amazons. Unlike the main [EDI package](https://github.com/Chad-Glazier/edi), this implementation omits any diagnostic tools or alternative game-playing programs. This version is intended to be built and run on a website.

## Building the Project

We use [Emscripten](https://emscripten.org) to compile this program into WebAssembly code that can be run in a browser environment. The following notes assume that you have an Emscripten environment properly set up.

There are a few commands already set up for building the project from PowerShell. However, since they are basically just calls to `emcc`, they should be trivial to translate to other shells.
- [build.ps1](./build.ps1) produces the optimized WebAssembly build and outputs it in [`build/`](./build/).
- [debug.ps1](./debug.ps1) compiles the program in a similar way but with a bunch of debugging flags set. This version is an order of magnitude slower and it should only be used for debugging.
- [run.ps1](./run.ps1) uses GCC to compile the project to an executable, runs it, and then deletes the binary.

Apart from building the project, there are also the following scripts:
- [lint.ps1](./lint.ps1) lints the source code with `clang-tidy`.
- [format.ps1](./format.ps1) formats the source code with `clang-format`.

## Using the Program

To access functions declared in the project from JavaScript, you can use `Module._cFuncName` where `cFuncName` is the name of the global in the C code (note that the `_` prefix is added when accessing it). 

> **NOTE:** Emscripten will eliminate dead code, and LLVM will aggressively inline functions. Both of these behaviors can prevent global C objects from appearing in the JavaScript `Module` object. If you want to skip these behaviors and force Emscripten to export a function, you need to use the `EMSCRIPTEN_KEEPALIVE` macro. For example,

```c
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void some_c_func() {
	// ...
}
```
