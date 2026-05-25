#include "state.h"
#include <string.h>

// Returns an unordered slice of all possible subsequent board states. When
// modeling the game as a state tree, this function returns the children of a
// given state.
StateSlice* get_children(State* parent) {

    // TODO: This implementation could be simplified by using pointers to the
    // active queens/players instead of the giant if-else block.

	StateSlice* children = state_slice_create(200);

	if (parent->player == WHITE) {

		// Iterate over all possible "from" positions. There should be one per
		// queen.
		for (uint8_t queenIdx = 0; queenIdx < 4; queenIdx++) {
			Position from = parent->white[queenIdx];

			// Iterate over the possible "to" positions (i.e., where each queen
			// can move to.)
			BitBoard neighbors = q_neighbors(&parent->occ, from);
			for (Position to = next(&neighbors); to != NULL_POS;
			     to = next(&neighbors)) {

				// Move the queen from "from" to "to". We do this in-place on
				// the parent board, so we'll have to remember to rever these
				// changes before the next iteration.
				parent->white[queenIdx] = to;
				unflag(&parent->occ, from);
				flag(&parent->occ, to);

				// Iterate over the possible locations where the new arrow
				// could be fired.
				BitBoard targets = q_neighbors(&parent->occ, to);
				for (Position arrow = next(&targets); arrow != NULL_POS;
				     arrow = next(&targets)) {

                    // Add the arrow to the board (again, in-place on the
                    // parent board).
					flag(&parent->occ, arrow);

                    // We now have all the stuff we need for the child state.
					State child = {
					    .occ = parent->occ,
					    .player = BLACK,
					    .move =
					        {
					            .from = from,
					            .to = to,
					            .arrow = arrow,
					        },
					};
                    memcpy(
                        &child.white, 
                        parent->white, 
                        sizeof(parent->white[0]) * 4
                    );
                    memcpy(
                        &child.black, 
                        parent->black, 
                        sizeof(parent->black[0]) * 4
                    );
					state_slice_append(children, child);

                    // Undo the arrow on the parent.
					unflag(&parent->occ, arrow);
				}

                // Move the queen back.
                parent->white[queenIdx] = from;
				flag(&parent->occ, from);
				unflag(&parent->occ, to);
			}
		}
	} else {

        // Identical steps but for moving Black instead of White.

		for (uint8_t queenIdx = 0; queenIdx < 4; queenIdx++) {
			Position from = parent->black[queenIdx];

			BitBoard neighbors = q_neighbors(&parent->occ, from);
			for (Position to = next(&neighbors); to != NULL_POS;
			     to = next(&neighbors)) {

				parent->black[queenIdx] = to;
				unflag(&parent->occ, from);
				flag(&parent->occ, to);

				BitBoard targets = q_neighbors(&parent->occ, to);
				for (Position arrow = next(&targets); arrow != NULL_POS;
				     arrow = next(&targets)) {

					flag(&parent->occ, arrow);

					State child = {
					    .occ = parent->occ,
					    .player = WHITE,
					    .move =
					        {
					            .from = from,
					            .to = to,
					            .arrow = arrow,
					        },
					};
                    memcpy(
                        &child.white, 
                        parent->white, 
                        sizeof(parent->white[0]) * 4
                    );
                    memcpy(
                        &child.black, 
                        parent->black, 
                        sizeof(parent->black[0]) * 4
                    );
					state_slice_append(children, child);

					unflag(&parent->occ, arrow);
				}

                parent->black[queenIdx] = from;
				flag(&parent->occ, from);
				unflag(&parent->occ, to);
			}
		}
	}

    return children;
}
