// #include <emscripten.h>
#include <stdio.h>
#include <time.h>

#include "bitboard/bitboard.c"
#include "bitboard/precomputed.c"
#include "eval/kmindist.c"
#include "search/alpha_beta.c"
#include "state/get_children.c"
#include "state/neighbors.c"
#include "state/state.c"
#include "state/state_slice.c"
#include "util/time.c"

// #include "interface.c"
#include "benchmark.c"

int main()
{
    bitboard_init();
    // interface_init();

    // Report certain values.
    printf("sizeof(State) is %zuB\n", sizeof(State));

    // Run benchmarks
    benchmark_kmindist();
    benchmark_get_children();

    State board = initial_state();

    // Check that `get_children` is working.
    State children[MAX_CHILDREN];
    uint16_t child_count = get_children(children, &board);
    printf("get_children on an initial board yields %d children.\n", child_count);

    uint64_t seconds = 10;
    printf("Running %ds search...\n", seconds);
    AlphaBetaResult result = alpha_beta(&board, kmindist, seconds * 1000000000ULL);
    printf("Greatest depth completed: %d\n", result.greatest_completed_depth);

    printf("Recommended move: %2d -> %2d, X %2d\n",
        result.preferred_child.move.from, result.preferred_child.move.to,
        result.preferred_child.move.arrow);

    return 0;
}
