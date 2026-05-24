#include <emscripten.h>
#include <stdio.h>
#include <time.h>

#include "bitboard/bitboard.c"
#include "bitboard/precomputed.c"

#include "state/get_children.c"
#include "state/neighbors.c"
#include "state/state.c"
#include "state/state_slice.c"

#include "eval/kmindist.c"

#include "search/alpha_beta.c"

#include "interface.c"

int main() {

	bitboard_init();
    interface_init();
	
	return 0;
}
