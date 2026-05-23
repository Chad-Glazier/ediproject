#ifndef STATE_H
#define STATE_H

#include "../bitboard/bitboard.h"
#include <stdint.h>

// Represents a player color.
typedef uint8_t PlayerColor;

extern const PlayerColor WHITE;
extern const PlayerColor BLACK;

// Represents a player move.
typedef struct {
	Position from;  // The original position of the queen being moved.
	Position to;    // The new position of the queen that was moved.
	Position arrow; // The position where the arrow was fired.
} Move;

// Represents an Amazons game state.
typedef struct {
	BitBoard occ;       // The occupancy board.
	Position white[4];  // The positions of the White queens.
	Position black[4];  // The positions of the Black queens.
	Move move;          // The most recent move made.
	PlayerColor player; // The player who can make the next move.
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

#endif
