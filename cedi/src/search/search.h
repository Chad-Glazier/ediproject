#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>

#include "../eval/eval.h"
#include "../state/state.h"
#include "../util/util.h"

typedef struct {
    State preferred_child;
    uint8_t greatest_completed_depth;
} AlphaBetaResult;

AlphaBetaResult alpha_beta(State* root, EvalFunc eval, Nanoseconds time_limit);

#endif