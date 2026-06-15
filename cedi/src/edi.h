#ifndef EDI_H
#define EDI_H

#include "bitboard/bitboard.c"
#include "bitboard/precomputed.c"
#include "eval/kmindist.c"
#include "search/alpha_beta.c"
#include "state/get_children.c"
#include "state/neighbors.c"
#include "state/state.c"
#include "state/state_slice.c"
#include "util/time.c"

// Runs necessary setup functions before EDI can be used.
void edi_init(void)
{
    bitboard_init();
}

#endif
