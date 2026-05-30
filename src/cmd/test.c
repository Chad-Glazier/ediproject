#include "../edi.h"
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>

//
// Helpers.
//

typedef bool (*TestFunc)(void);

void run_test(char* name, TestFunc test)
{
    bool pass = (*test)();
    if (pass) {
        printf("PASS ");
    } else {
        printf("FAIL ");
    }
    printf("%s\n", name);
}

//
// Tests.
//

bool test_get_children_initial(void)
{

    State board = initial_state();

    State children[MAX_CHILDREN];
    uint16_t child_count = get_children(children, &board);
    return child_count == 2176;
}

//
// Entrypoint.
//

int main()
{
    edi_init();

    run_test("get_children on initial board returns 2176", test_get_children_initial);

    return 0;
}
