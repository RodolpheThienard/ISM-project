#ifndef BENCHMARK_H
#define BENCHMARK_H
#include "utils.h"

#define BENCH(X, Y)                                                           \
  clock_gettime (CLOCK_MONOTONIC_RAW, X);                                     \
  Y = rdtsc ();

u64 rdtsc();
#endif
