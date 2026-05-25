#include "eval/eval.h"
#include "util/util.h"

void benchmark_kmindist() {
    
    const int sample = 100000;
    State board = initial_state();
    
    volatile double sink;

    Nanoseconds start = current_time();
    for (int i = 0; i < sample; i++) {
        sink = kmindist(&board);
    }
    Nanoseconds end = current_time();

    double interval = (double) (end - start) / (double) sample;

    printf(
        "kmindist: %.2fns/op (%d iterations)\n",
        interval,
        sample
    );
}
