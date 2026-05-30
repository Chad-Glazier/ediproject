#include "state.h"

// Returns a bitboard where each neighbor of a given position is flagged, where
// two squares p and q are neighbors if and only if a chess king could move
// from p to q (accounting for squares that are already occupied by arrows or
// queens).
BitBoard k_neighbors(BitBoard* occupancy, Position position)
{
    return and_not(king_adjacent(position), occupancy);
}

// Returns the frontier of a given territory. A territory is a set of positions
// on the board, and the frontier of a territory is defined to be the set of
// positions that are adjacent to some position in the territory, excluding any
// positions that are already in the territory. Two positions p and q are
// adjacent if and only if a chess king could move from p to q in a single
// move, accounting for any arrows or queens that could obstruct such a move.
BitBoard k_frontier(BitBoard* occupancy, BitBoard* territory)
{
    BitBoard frontier = { };

    BitBoard iter = *territory;
    for (Position p = next(&iter); p != NULL_POS; p = next(&iter)) {
        BitBoard neighbors = k_neighbors(occupancy, p);
        assign_or(&frontier, &neighbors);
    }

    return and_not(&frontier, territory);
}

// Returns a bitboard where each neighbor of a given position is flagged, where
// two squares p and q are neighbors if and only if a chess queen could move
// from p to q (accounting for squares that are already occupied by arrows or
// queens).
BitBoard q_neighbors(BitBoard* occupancy, Position position)
{
    BitBoard neighbors = { };

    // Iterate over the forward directions.
    for (Direction d = W; d < E; d++) {
        BitBoard* ray = exclusive_ray(position, d);
        BitBoard blockers = and(ray, occupancy);

        Position nearest_blocker = msb(&blockers); // the direction is forward
        if (nearest_blocker == NULL_POS) {
            assign_or(&neighbors, ray);
            continue;
        }

        BitBoard blocked_ray = xor(ray, inclusive_ray(nearest_blocker, d));
        assign_or(&neighbors, &blocked_ray);
    }

    // Iterate over the backward directions.
    for (Direction d = E; d <= SW; d++) {
        BitBoard* ray = exclusive_ray(position, d);
        BitBoard blockers = and(ray, occupancy);

        Position nearest_blocker = lsb(&blockers); // the direction is backward
        if (nearest_blocker == NULL_POS) {
            assign_or(&neighbors, ray);
            continue;
        }

        BitBoard blocked_ray = xor(ray, inclusive_ray(nearest_blocker, d));
        assign_or(&neighbors, &blocked_ray);
    }

    return neighbors;
}

// Returns the frontier of a given territory. A territory is a set of positions
// on the board, and the frontier of a territory is defined to be the set of
// positions that are adjacent to some position in the territory, excluding any
// positions that are already in the territory. Two positions p and q are
// adjacent if and only if a chess queen could move from p to q in a single
// move, accounting for any arrows or queens that could obstruct such a move.
BitBoard q_frontier(BitBoard* occupancy, BitBoard* territory)
{
    BitBoard frontier = { };

    BitBoard iter = *territory;
    for (Position p = next(&iter); p != NULL_POS; p = next(&iter)) {
        BitBoard neighbors = q_neighbors(occupancy, p);
        assign_or(&frontier, &neighbors);
    }

    return and_not(&frontier, territory);
}
