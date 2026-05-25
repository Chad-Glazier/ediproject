// #include <emscripten.h>
#include <stdio.h>
#include <time.h>

#include "util/time.c"

#include "bitboard/bitboard.c"
#include "bitboard/precomputed.c"

#include "state/get_children.c"
#include "state/neighbors.c"
#include "state/state.c"
#include "state/state_slice.c"

#include "eval/kmindist.c"

#include "search/alpha_beta.c"

// #include "interface.c"
#include "benchmark.c"

int main() {

	bitboard_init();
    // interface_init();

    benchmark_kmindist();

    // State board = initial_state();

    // for (int i = 0; i < 100; i++) {
    //     if (i % 2 == 0) {
    //         flag(&board.occ, i);
    //     }
    // }

    // AlphaBetaResult result = alpha_beta(
    //     &board, kmindist, 120ULL * 1000000000ULL);
    // printf("Greatest depth completed: %d\n", result.greatest_completed_depth);

    // printf(
    //     "Recommended move: %2d -> %2d, X %2d\n", 
    //     result.preferred_child.move.from,
    //     result.preferred_child.move.to,
    //     result.preferred_child.move.arrow   
    // );

	return 0;
}
