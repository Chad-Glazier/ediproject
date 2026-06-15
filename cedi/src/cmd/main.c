#include "../edi.h"
#include <stdio.h>

int main()
{
    edi_init();
    printf("EDI initialization complete.\n");
    return 0;
}

//
// Below, we define the functions that are exposed to the JavaScript code.
//
