# EDI in C

This project is an implementation of the main EDI program for playing the Game of Amazons. Unlike the main [EDI package](https://github.com/Chad-Glazier/edi), this implementation omits any diagnostic tools or alternative game-playing programs. This version is intended to be built and run on a website.

## Building the Project

We use [Emscripten](https://emscripten.org) to compile this program into WebAssembly code that can be run in a browser environment. The following notes assume that you have an Emscripten environment properly set up.

To build the project for debugging, run

```sh
emcc src/main.c -o build/edi.js
```

To build an aggressively optimized version suitable for production, run

```sh
emcc -O3 src/main.c -o build/edi.js
```

To access functions declared in the project from JavaScript, you can use `Module._cFuncName` where `cFuncName` is the name of the global in the C code (note that the `_` prefix is added when accessing it). 

> **NOTE:** Emscripten will eliminate dead code, and LLVM will aggressively inline functions. Both of these behaviors can prevent global C objects from appearing in the JavaScript `Module` object. If you want to skip these behaviors and force Emscripten to export a function, you need to use the `EMSCRIPTEN_KEEPALIVE` macro. For example,

```c
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void some_c_func() {
	// ...
}
```
