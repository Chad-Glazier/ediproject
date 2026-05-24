#ifndef EVAL_H
#define EVAL_H

#include "../state/state.h"

// A function that evaluates a board state and returns a score that reflects
// the quality of the position. Positive values indicate favorability for
// White, negative values are favorable for Black, and 0 marks a neutral
// position.
typedef double (*EvalFunc)(State* state);

double kmindist(State* state);

#endif
