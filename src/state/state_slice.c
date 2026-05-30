#include <stdlib.h>
#include <string.h>

#include "state.h"

// Allocates a new state slice on the heap with the specified initial capacity.
StateSlice* state_slice_create(uint16_t cap)
{
    StateSlice* s = calloc(1, sizeof(StateSlice));
    s->states = calloc(cap, sizeof(State));
    s->len = 0;
    s->cap = cap;

    return s;
}

// Frees the memory used by a state slice.
void state_slice_destroy(StateSlice* s)
{
    free(s->states);
    free(s);
}

// Appends a state to the slice.
void state_slice_append(StateSlice* s, State state)
{
    // If the slice has the capacity for a new element, then we can just add
    // it.
    if (s->len < s->cap) {
        s->states[s->len] = state;
        s->len++;
        return;
    }

    // Reallocate the backing array.
    uint32_t new_capacity = 2 * s->cap;
    State* new_states = calloc(new_capacity, sizeof(State));

    // Copy the data over and then free the original array.
    memcpy(new_states, s->states, s->len * sizeof(State));
    free(s->states);

    // Update the slice to use the new values.
    s->cap = new_capacity;
    s->states = new_states;

    // Add the new state to the slice.
    s->states[s->len] = state;
    s->len++;
}
