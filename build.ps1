
emcc "src/main.c" -o "build/edi.js" `
    "-std=c23" `
    "-Wall" `
    "-Wextra" `
    "-Wpedantic" `
    "-Wconversion" `
    "-Wsign-conversion" `
    "-Wshadow" `
    "-Wundef" `
    "-Wdouble-promotion" `
    "-Wformat=2" `
    "-Wcast-align" `
    "-Wstrict-prototypes" `
    "-Wmissing-prototypes" `
    "-Wimplicit-fallthrough" `
    "-Wnull-dereference" `
    "-Wwrite-strings" `
    "-Wuninitialized" `
    "-Wredundant-decls" `
    "-Wswitch-enum" `
    "-Wfloat-equal" `
    "-Wvla" `
    "-Werror" `
    "-g3" `
    "-O1" `
    "-fsanitize=address,undefined" `
    "-fno-omit-frame-pointer";