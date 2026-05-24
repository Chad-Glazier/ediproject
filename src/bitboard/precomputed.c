#include "bitboard.h"

const Direction W = 0;  // West
const Direction NW = 1; // Northwest
const Direction N = 2;  // North
const Direction NE = 3; // Northeast
const Direction E = 4;  // East
const Direction SE = 5; // Southeast
const Direction S = 6;  // South
const Direction SW = 7; // Southwest

static BitBoard king_adjacent_boards[100];
static BitBoard exclusive_ray_boards[100][8];
static BitBoard inclusive_ray_boards[100][8];

// Returns a bitboard where each position is flagged if and only if a Chess
// king could move from pos to that position in a single move.
BitBoard* king_adjacent(Position pos) {
    return &king_adjacent_boards[pos];
}

// Returns a bitboard where each position is flagged if and only if it lies 
// on a ray projected from pos in the direction dir, excluding pos.
BitBoard* exclusive_ray(Position pos, Direction dir) {
    return &exclusive_ray_boards[pos][dir];
}

// Returns a bitboard where each position is flagged if and only if it lies 
// on a ray projected from pos in the direction dir, including pos.
BitBoard* inclusive_ray(Position pos, Direction dir) {
    return &inclusive_ray_boards[pos][dir];
}

static BitBoard compute_king_adjacent_board(Position pos) {
	BitBoard b = {};
    int row = pos / 10;
    int col = pos % 10;

	if (row != 9) {
        
        flag(&b, position(row + 1, col));

		if (col != 9) {
			flag(&b, position(row+1, col+1));
		}

		if (col != 0) {
			flag(&b, position(row+1, col-1));
		}
	}

	if (row != 0) {
		flag(&b, position(row-1, col));

		if (col != 9) {
			flag(&b, position(row-1, col+1));
		}

		if (col != 0) {
			flag(&b, position(row-1, col-1));
		}
	}

	if (col != 9) {
		flag(&b, position(row, col+1));
	}

	if (col != 0) {
		flag(&b, position(row, col-1));
	}

	return b;
}

static BitBoard compute_exclusive_ray_board(Position pos, Direction dir) {
	BitBoard b = {};
    int row = pos / 10;
    int col = pos % 10;

	// Rows are indexed from the top to the bottom. So, to move "north," we
	// would need to decrement the row index.

	// Column indices are indexed left-to-right, so incrementing the column
	// index is the same as moving "east."

	while (1) {
		switch (dir) {
		case N:
			row--;
            break;
		case NE:
			row--;
			col++;
            break;
		case E:
			col++;
            break;
		case SE:
			row++;
			col++;
            break;
		case S:
			row++;
            break;
		case SW:
			row++;
			col--;
            break;
		case W:
			col--;
            break;
		case NW:
			row--;
			col--;
            break;
		}
		if (row >= 10 || row < 0 || col >= 10 || col < 0) {
			break;
		}

		flag(&b, position(row, col));
	}

	return b;
}

static BitBoard compute_inclusive_ray_board(Position pos, Direction dir) {
    BitBoard b = compute_exclusive_ray_board(pos, dir);
    flag(&b, pos);
    return b;
}

// Initializes the precomputed bitboards. This should only be called once, and
// it must be called before anything else.
void bitboard_init(void) {
    for (Position p = 0; p < 100; p++) {
        king_adjacent_boards[p] = compute_king_adjacent_board(p);
        for (Direction d = 0; d < 8; d++) {
            exclusive_ray_boards[p][d] = compute_exclusive_ray_board(p, d);
            inclusive_ray_boards[p][d] = compute_inclusive_ray_board(p, d);
        }
    }
}
