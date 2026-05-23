#include "bitboard.h"
#include <stdint.h>
#include <stdbool.h>

const Position NULL_POS = 100;

// Flags a position in the bitboard.
void flag(BitBoard* bb, Position pos) {
	if (pos < 64) {
		bb->lo |= 1ULL << pos;
	} else {
		bb->hi |= 1ULL << (pos - 64);
	}
}

// Unflags a position in the bitboard.
void unflag(BitBoard* bb, Position pos) {
	if (pos < 64) {
		bb->lo &= ~(1ULL << pos);
	} else {
		bb->hi &= ~(1ULL << (pos - 64));
	}
}

// Returns true if the position in the board is flagged and false otherwise.
bool flagged(BitBoard* bb, Position pos) {
	if (pos < 64) {
		return (bb->lo & (1ULL << pos)) != 0;
	} else {
		return (bb->hi & (1ULL << (pos - 64))) != 0;
	}
}

// Returns true if and only if the bitboard has no flags.
bool empty(BitBoard* bb) {
	return (bb->hi | bb->lo) == 0;
}

// Returns true if and only if the bitboard has at least one flag.
bool not_empty(BitBoard* bb) {
	return (bb->hi | bb->lo) != 0;
}

// Returns the greatest position index on the board and unflags it. Since these
// boards are represented in row-major order, greater indices are closer to the
// bottom-right corner.
Position next(BitBoard* bb) {
	if (bb->hi != 0) {
		Position pos = __builtin_ctzll(bb->hi) + 64;
		bb->hi &= bb->hi - 1;
		return pos;
	}
	if (bb->lo != 0) {
		Position pos = __builtin_ctzll(bb->lo);
		bb->lo &= bb->lo - 1;
		return pos;
	}
	return NULL_POS;
}

// Returns the number of flagged positions on the board.
int count(BitBoard* bb) {
	return __builtin_popcountll(bb->lo) + __builtin_popcountll(bb->hi);
}

// Returns the greatest flagged position index on the board. If the
// board is empty, then the null position (NULL_POS) is returned.
Position lsb(BitBoard* bb) {
	if (bb->lo != 0) {
		return __builtin_ctzll(bb->lo);
	}
	if (bb->hi != 0) {
		return __builtin_ctzll(bb->hi) + 64;
	}
	return NULL_POS;
}

// Returns the position index of the most-significant bit in the board. If the
// board is empty, then the null position (NULL_POS) is returned .
Position msb(BitBoard* bb) {
	if (bb->hi != 0) {
		return 127 - __builtin_clzll(bb->hi);
	}
	if (bb->lo != 0) {
		return 63 - __builtin_clzll(bb->lo);
	}
	return NULL_POS;
}

// Performs a bitwise OR operation (a | b) and returns the result.
BitBoard or(BitBoard* a, BitBoard* b) {
	BitBoard r = {
		.lo = a->lo | b->lo,
		.hi = a->hi | b->hi,
	};
	return r;
}

// Performs a bitwise OR operation (a | b) and assigns the result to a.
void assign_or(BitBoard* a, BitBoard b) {
	a->lo |= b.lo;
	a->hi |= b.hi;
}

// Performs a bitwise XOR operation (a ^ b) and returns the result.
BitBoard xor(BitBoard* a, BitBoard* b) {
	BitBoard r = {
		.lo = a->lo ^ b->lo,
		.hi = a->hi ^ b->hi,
	};
	return r;
}

// Performs a bitwise XOR operation (a ^ b) and assigns the result to a.
void assign_xor(BitBoard* a, BitBoard* b) {
	a->lo ^= b->lo;
	a->hi ^= b->hi;
}

// Performs a bitwise AND operation (a & b) and returns the result.
BitBoard and(BitBoard* a, BitBoard* b) {
	BitBoard r = {
		.lo = a->lo & b->lo,
		.hi = a->hi & b->hi,
	};
	return r;
}

// Performs a bitwise AND operation (a & b) and assigns the result to a.
void assign_and(BitBoard* a, BitBoard* b) {
	a->lo &= b->lo;
	a->hi &= b->hi;
}

// Performs a bitwise AND-NOT operation (a &^ b) and returns the result.
BitBoard and_not(BitBoard* a, BitBoard* b) {
	BitBoard r = {
		.lo = a->lo & (~b->lo),
		.hi = a->hi & (~b->hi),
	};
	return r;
}

// Performs a bitwise AND-NOT operation (a &^ b) and assigns the result to a.
void assign_and_not(BitBoard* a, BitBoard* b) {
	a->lo &= ~b->lo;
	a->hi &= ~b->hi;
}

// Performs a bitwise NOT operation (a ^ b) and returns the result.
BitBoard not(BitBoard* a) {
	BitBoard r = {
		.lo = ~a->lo,
		.hi = ~a->hi,
	};
	return r;
}

// Performs a bitwise NOT operation (a ^ b) and assigns the result to a.
void assign_not(BitBoard* a) {
	a->lo = ~a->lo;
	a->hi = ~a->hi;
}

// Convert row/column coordinates to a position index.
Position position(int row, int col) {
    return row * 10 + col;
}

