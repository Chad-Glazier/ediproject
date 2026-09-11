#include "../edi.h"
#include <stdint.h>
#include <stdio.h>

//
// This file implements some very basic benchmarks to check the performance of
// some of the more important functions. This is mainly meant to help detect
// certain subtler bugs that can be noticed by significant performance
// increases or decreases.
//

void benchmark_kmindist()
{
    const int sample = 100000;
    State board = initial_state();

    volatile double sink;

    Nanoseconds start = current_time();
    for (int i = 0; i < sample; i++) {
        sink = kmindist(&board);
    }
    Nanoseconds end = current_time();

    double interval = (double)(end - start) / (double)sample;

    printf("kmindist:     %.2fns/op (%d iterations)\n", interval, sample);
}

void benchmark_get_children()
{
    const int sample = 100000;
    State board = initial_state();
    State children[MAX_CHILDREN];

    volatile uint16_t sink;

    Nanoseconds start = current_time();
    for (int i = 0; i < sample; i++) {
        sink = get_children(children, &board);
    }
    Nanoseconds end = current_time();

    double interval = (double)(end - start) / (double)sample;

    printf("get_children: %.2fns/op (%d iterations)\n", interval, sample);
}

void benchmark_alpha_beta()
{
    State board = initial_state();

    alpha_beta(&board, kmindist, (Nanoseconds) 30000000000ULL);
}

//
// Entrypoint.
//

int main()
{
    edi_init();

    benchmark_kmindist();
    benchmark_get_children();
    benchmark_alpha_beta();

    return 0;
}
