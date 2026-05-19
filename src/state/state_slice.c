#include "state.h"
#include <stdlib.h>
#include <string.h>

// Allocates a new state slice on the heap with the specified initial capacity.
StateSlice* state_slice_create(uint16_t capacity) {
	
	StateSlice* s = calloc(1, sizeof(StateSlice));
	s->states = calloc(capacity, sizeof(State));
	s->length = 0;
	s->capacity = capacity;

	return s;
}

// Frees the memory used by a state slice.
void state_slice_destroy(StateSlice* s) {
	free(s->states);
	free(s);
}

// Appends a state to the slice.
void state_slice_append(StateSlice* s, State state) {
	
	// If the slice has the capacity for a new element, then we can just add 
	// it.
	if (s->length < s->capacity) {
		s->states[s->length] = state;
		s->length++;
		return;
	}

	// Reallocate the backing array.
	uint32_t new_capacity = 2 * s->capacity;
	State* new_states = calloc(new_capacity, sizeof(State));

	// Copy the data over and then free the original array.
	memcpy(new_states, s->states, s->length * sizeof(State));
	free(s->states);

	// Update the slice to use the new values.
	s->capacity = new_capacity;
	s->states = new_states;

	// Add the new state to the slice.
	s->states[s->length] = state;
	s->length++;
}
