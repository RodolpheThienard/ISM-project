#include "../include/benchmark.h"

u64
rdtsc ()
{
  u64 a, d;
  __asm__ volatile("rdtsc" : "=a"(a), "=d"(d));
  return (d << 32) | a;
}
