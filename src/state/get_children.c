#include <string.h>

#include "state.h"

// Defines the maximum number of children that a parent state can have.
const uint16_t MAX_CHILDREN = 3000;

// Computes all possible child states for a given parent, writing them into the
// specified array. The number of computed children is returned.
uint16_t get_children(State child_array[MAX_CHILDREN], State* parent)
{
    uint16_t i = 0;

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
                    child_array[i].occ = parent->occ;
                    child_array[i].player = BLACK;
                    child_array[i].move = (Move) {
                        .from = from,
                        .to = to,
                        .arrow = arrow,
                    };
                    for (int j = 0; j < 4; j++) {
                        child_array[i].white[j] = parent->white[j];
                        child_array[i].black[j] = parent->black[j];
                    }
                    i++;

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
                    // Add the arrow to the board (again, in-place on the
                    // parent board).
                    flag(&parent->occ, arrow);

                    // We now have all the stuff we need for the child state.
                    child_array[i].occ = parent->occ;
                    child_array[i].player = WHITE;
                    child_array[i].move = (Move) {
                        .from = from,
                        .to = to,
                        .arrow = arrow,
                    };
                    for (int j = 0; j < 4; j++) {
                        child_array[i].white[j] = parent->white[j];
                        child_array[i].black[j] = parent->black[j];
                    }
                    i++;

                    // Undo the arrow on the parent.
                    unflag(&parent->occ, arrow);
                }

                parent->black[queenIdx] = from;
                flag(&parent->occ, from);
                unflag(&parent->occ, to);
            }
        }
    }

    return i;
}
