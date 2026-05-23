#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdbool.h>
#include <stdint.h>

// Represents a position on the 10x10 Amazons board with an index from 0 to 99.
// We use row-major ordering, so you can get the row index with position / 10
// and the column with position % 10.
typedef uint8_t Position;

// Represents a null position. I.e., for functions that return a position,
// the null position should be returned if no valid position exists.
extern const Position NULL_POS;

// Represents a board where each position index (0-99, since Amazons is played
// on a 10x10 board) is either 0 or 1, which we refer to as "unflagged" and
// "flagged," respectively.
typedef struct {
	uint64_t lo;
	uint64_t hi;
} BitBoard;

void flag(BitBoard* bb, Position pos);
void unflag(BitBoard* bb, Position pos);
bool flagged(BitBoard* bb, Position pos);
bool empty(BitBoard* bb);
bool not_empty(BitBoard* bb);
Position next(BitBoard* bb);

int count(BitBoard* bb);
Position lsb(BitBoard* bb);
Position msb(BitBoard* bb);

BitBoard or (BitBoard * a, BitBoard* b);
BitBoard xor (BitBoard * a, BitBoard* b);
BitBoard and (BitBoard * a, BitBoard* b);
BitBoard and_not(BitBoard* a, BitBoard* b);
BitBoard not(BitBoard * a);

void assign_or(BitBoard* a, BitBoard b);
void assign_xor(BitBoard* a, BitBoard* b);
void assign_and(BitBoard* a, BitBoard* b);
void assign_and_not(BitBoard* a, BitBoard* b);
void assign_not(BitBoard* a);

// Represents a one of the eight cardinal/intercardinal directions.
typedef uint8_t Direction;

extern const Direction W;
extern const Direction NW;
extern const Direction N;
extern const Direction NE;
extern const Direction E;
extern const Direction SE;
extern const Direction S;
extern const Direction SW;

void bitboard_init();

BitBoard* king_adjacent(Position pos);
BitBoard* exclusive_ray(Position pos, Direction dir);
BitBoard* inclusive_ray(Position pos, Direction dir);

#endif
