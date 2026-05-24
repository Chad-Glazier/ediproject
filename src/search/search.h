#ifndef SEARCH_H
#define SEARCH_H

#include "../eval/eval.h"
#include "../state/state.h"
#include <stdint.h>

typedef struct {
    State preferred_child;
    uint8_t greatest_completed_depth;
} AlphaBetaResult;

typedef uint64_t Nanoseconds;

AlphaBetaResult alpha_beta(State* root, EvalFunc eval, Nanoseconds time_limit);

#endif