#include <stdio.h>
#include <emscripten.h>

#include "state/state_slice.c"
#include "state/state.c"
#include "bitboard/bitboard.c"
#include "bitboard/precomputed.c"

int main() {

    // Initialization.
    bitboard_init();
	
	StateSlice* s = state_slice_create(10);
	printf("len: %d, cap: %d\n", s->len, s->cap);

	for (int i = 0; i < 4000; i++) {
		state_slice_append(s, (State){});
	}

	printf("len: %d, cap: %d\n", s->len, s->cap);

    state_slice_destroy(s);

	return 0;
}
