#include "../bitboard/bitboard.h"
#include "eval.h"

// Partitions territory between Black and White based on who can reach a given
// square faster if their queens moved the way that chess kings do, then
// calculates a score based on the sizes of the territories.
double kmindist(State* state) {

	BitBoard white_territory = {};
	BitBoard black_territory = {};

	BitBoard white_frontier = {};
	BitBoard black_frontier = {};

	for (uint8_t i = 0; i < 4; i++) {

		flag(&white_territory, state->white[i]);
		flag(&black_territory, state->black[i]);

		BitBoard white_k_neighbors = k_neighbors(&state->occ, state->white[i]);
		assign_or(&white_frontier, &white_k_neighbors);

		BitBoard black_k_neighbors = k_neighbors(&state->occ, state->black[i]);
		assign_or(&black_frontier, &black_k_neighbors);
	}

	BitBoard visited = or(&white_territory, &black_territory);

	while (not_empty(&white_frontier) || not_empty(&black_frontier)) {

		// First, we let White and Black claim their respective territory.
		// Any new territory on the White frontier that isn't on the Black
		// frontier is claimed for White, and vice versa.
		BitBoard white_claim = and_not(&white_frontier, &black_frontier);
		assign_or(&white_territory, &white_claim);

		BitBoard black_claim = and_not(&black_frontier, &white_frontier);
		assign_or(&black_territory, &black_claim);

		// Next, update the "visited" board to reflect that the new frontiers
		// have been explored.
		assign_or(&visited, &black_frontier);
        assign_or(&visited, &white_frontier);

		// Finally, we expand the frontiers, omitting any previously explored
		// territory.
		black_frontier = k_frontier(&state->occ, &black_frontier);
		assign_and_not(&black_frontier, &visited);

		white_frontier = k_frontier(&state->occ, &white_frontier);
		assign_and_not(&white_frontier, &visited);
	}

	return (double) (count(&white_territory) - count(&black_territory)) /
	       (double) (count(&visited) - 7);
}
