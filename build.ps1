
# We use a 4 MiB stack limit. Each array of child states demands, with the
# current implementation, at least MAX_CHILDREN * sizeof(State) bytes of stack 
# memory. At the time of writing, this is 96000B or ~0.1MiB. If I'm conceptual-
# izing the program correctly, there should only be one such array per ply of
# search depth. A limit of 4 MiB therefore allows for a maximum depth of 43.
# This is beyond what should be possible for any computer to actually reach,
# but it's better to be safe than sorry.

emcc `
    -std=c23 `
    -O3 `
    -sSTACK_SIZE=4194304 `
    .\src\main.c `
    -o build/edi.js
