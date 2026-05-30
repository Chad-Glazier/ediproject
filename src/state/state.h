#ifndef STATE_H
#define STATE_H

#include <stdint.h>

#include "../bitboard/bitboard.h"

// Represents a player color.
typedef uint8_t PlayerColor;

extern const PlayerColor WHITE;
extern const PlayerColor BLACK;

// Represents a player move.
typedef struct {
    Position from; // The original position of the queen being moved.
    Position to; // The new position of the queen that was moved.
    Position arrow; // The position where the arrow was fired.
} Move;

// Represents an Amazons game state.
typedef struct {
    BitBoard occ; // The occupancy board.
    Position white[4]; // The positions of the White queens.
    Position black[4]; // The positions of the Black queens.
    PlayerColor player; // The player who can make the next move.
    Move move; // The most recent move made.
} State;

// Represents a slice of game states.
typedef struct {
    State* states;
    uint16_t len;
    uint16_t cap;
} StateSlice;

StateSlice* state_slice_create(uint16_t capacity);
void state_slice_destroy(StateSlice* s);
void state_slice_append(StateSlice* s, State state);

BitBoard k_neighbors(BitBoard* occupancy, Position position);
BitBoard k_frontier(BitBoard* occupancy, BitBoard* territory);
BitBoard q_neighbors(BitBoard* occupancy, Position position);
BitBoard q_frontier(BitBoard* occupancy, BitBoard* territory);

extern const uint16_t MAX_CHILDREN;
uint16_t get_children(State child_array[MAX_CHILDREN], State* parent);

State initial_state(void);

#endif
