#include "state.h"

const PlayerColor WHITE = 0; // Represents the player on White.
const PlayerColor BLACK = 1; // Represents the player on Black.

// Returns a new board state representing the starting position.
State initial_state(void) {

    State s = {
        .player = WHITE,
        .white = { 30,  3,  6, 39 },
        .black = { 60, 93, 96, 69 },
    };

    for (uint8_t i = 0; i < 4; i++) {
        flag(&s.occ, s.white[i]);
        flag(&s.occ, s.black[i]);
    }

    return s;
}
