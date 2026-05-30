#include "search.h"

#include "../eval/eval.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

//
// Types
//

typedef struct {
	EvalFunc eval;
	Nanoseconds deadline;
	bool timed_out;
} AlphaBetaContext;

typedef struct {
	bool completed;
	double score;
} SearchResult;

//
// Helper functions
//

bool out_of_time(AlphaBetaContext* ctx) {
    return current_time() >= ctx->deadline;
}

// Returns -1 if Black is the next player to move, and +1 if White is.
double color(State* state) {
    if (state->player == WHITE) {
        return +1.0;
    } else {
        return -1.0;
    }
}

//
// Negamax implementation
//

SearchResult depth_limited_negamax(
    AlphaBetaContext* ctx,
    State* state,
    uint8_t depth,
    double alpha,
    double beta
) {
    if (out_of_time(ctx)) {
        ctx->timed_out = true;

        return (SearchResult){
            .completed = false,
            .score = 0.0,
        };
    }

    if (depth == 0) {
        return (SearchResult){
            .completed = true,
            .score = color(state) * (ctx->eval)(state),
        };
    }

    State children[MAX_CHILDREN];
    uint16_t child_count = get_children(children, state);

    if (child_count == 0) {
        return (SearchResult){
            .completed = true,
            .score = color(state) * (ctx->eval)(state),
        };
    }
    
    double best_score = -__DBL_MAX__;
    for (uint16_t i = 0; i < child_count; i++) {
        State* child = children + i;

        SearchResult result = depth_limited_negamax(
            ctx,
            child,
            depth - 1,
            -beta,
            -alpha
        );

        if (!result.completed) {
            return result;
        }

        double score = -result.score;

        if (score > best_score) {
            best_score = score;
        }

        if (score > alpha) {
            alpha = score;
        }

        if (alpha >= beta) {
            break;
        }
    }

    return (SearchResult){
        .completed = true,
        .score = best_score,
    };
}

// Conducts a simple minimax search with alpha-beta pruning. The given
// heuristic function is used for evaluating leaf nodes. No move-ordering is
// done. Returns the preferred child state and the greatest depth completed.
AlphaBetaResult alpha_beta(
    State* root,
	EvalFunc eval,
	Nanoseconds time_limit
) {
    Nanoseconds start_time = current_time();

    AlphaBetaContext ctx = {
        .eval = eval,
        .deadline = current_time() + time_limit,
        .timed_out = false,
    };

    AlphaBetaResult result = {};

    // Iterative deepening.
    uint8_t max_depth = 100 - count(&root->occ);
    for (uint8_t depth = 1; depth <= max_depth; depth++) {
        if (out_of_time(&ctx)) {
            break;
        }

        State children[MAX_CHILDREN];
        uint16_t child_count = get_children(children, root);

        if (child_count == 0) {
            break;
        }

        double best_score = -__DBL_MAX__;
        int best_index = -1;
        bool completed_iteration = true;

        double alpha = -__DBL_MAX__;
        double beta = __DBL_MAX__;

		for (uint16_t i = 0; i < child_count; i++) {
			State* child = children + i;

			SearchResult result = depth_limited_negamax(
				&ctx,
				child,
				depth - 1,
				-beta,
				-alpha
			);

			if (!result.completed) {
				completed_iteration = false;
				break;
			}

			double score = -result.score;

			if (score > best_score) {
				best_score = score;
				best_index = (int)i;
			}

			if (score > alpha) {
				alpha = score;
			}
		}

        if (completed_iteration && best_index >= 0) {
            result.greatest_completed_depth = depth;
            result.preferred_child = children[best_index];
            printf(
                "Completed depth %d (%llus)...\n", 
                depth,
                (current_time() - start_time) / 1000000000ULL
            );
        }

        if (!completed_iteration) {
            break;
        }
    }

    return result;
}
