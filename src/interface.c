//
// This file defines the functions that are used to let the JavaScript code
// interact with the C code.
//
#include "state/state.h"
#include <emscripten.h>

State global_board;

void interface_init(void) { global_board = initial_state(); }

EMSCRIPTEN_KEEPALIVE
const int SQUARE_EMPTY = 0;
EMSCRIPTEN_KEEPALIVE
const int SQUARE_ARROW = 1;
EMSCRIPTEN_KEEPALIVE
const int SQUARE_WHITE = 2;
EMSCRIPTEN_KEEPALIVE
const int SQUARE_BLACK = 3;

EMSCRIPTEN_KEEPALIVE
int get_status(Position p) {
    if (!flagged(&global_board.occ, p)) {
        return SQUARE_EMPTY;
    }

	for (int i = 0; i < 4; i++) {
		if (global_board.black[i] == p) {
			return SQUARE_BLACK;
			break;
		}
        if (global_board.white[i] == p) {
            return SQUARE_WHITE;
            break;
        }
	}

    return SQUARE_ARROW;
}

EMSCRIPTEN_KEEPALIVE
int reset_board(Position p, int new_status) {
    global_board = initial_state();
}


