#include <stdio.h>
#include <emscripten.h>
#include "state/state.h"

int main() {
	
	StateSlice* s = state_slice_create(10);
	printf("len: %d, cap: %d\n", s->length, s->capacity);

	for (int i = 0; i < 4000; i++) {
		state_slice_append(s, (State){});
	}

	printf("len: %d, cap: %d\n", s->length, s->capacity);

	return 0;
}
