#include "../include/benchmark.h"
#include "../include/kernels.h"
#include "../include/utils.h"

/*
  Time elapsed for Size matrix
  100  0.01
  500  0.20
  1000 0.75
*/
i32
main (i32 argc, char *argv[])
{
#ifdef DEBUG2
#define DEBUG
  puts ("DEBUG 2 ON");
#endif
#ifdef DEBUG
  puts ("DEBUG ON");
#endif
#ifdef BENCHMARK
  puts ("BENCHMARK ON");
#endif

#ifdef BENCHMARK
  struct timespec time_begin, time_end;
  u64 rdtsc_begin, rdtsc_end;
  BENCH (&time_begin, rdtsc_begin);
#endif

  char *filename = argv[1];
  FILE *file = fopen (filename, "r");
  if (file == NULL)
    perror ("\x1B[31mErr\x1B[0m");

  particules_t particules = parser (file);

#ifdef DEBUG2
  printf ("Print Read particules\n");
  print_particules (particules);
#endif

  f64 *distance = compute_distance (particules);

#ifdef DEBUG2
  printf ("Print Compute Distance\n");
  print_matrix (distance, SIZE, SIZE);
#endif

  f64 energy = lennard_jones (distance, 0.2, 3.);

#ifdef DEBUG2
  printf ("Print Energy matrix\n");
  printf ("Total energy : %lf\n", energy);
#endif

  f64 *force_x = compute_forces (distance, particules.x, 0.2, 3.);
  f64 *force_y = compute_forces (distance, particules.y, 0.2, 3.);
  f64 *force_z = compute_forces (distance, particules.z, 0.2, 3.);
  f64 *force_xyz = forces (force_x, force_y, force_z);

#ifdef DEBUG
#ifdef DEBUG2
  printf ("Print forces \n");
  print_matrix (force_x, 1, SIZE);
#endif
  printf ("Print forces \n");
  print_matrix_scientist (force_xyz, 1, 3);
#endif

#ifdef BENCHMARK
  BENCH (&time_end, rdtsc_end);
  printf ("Time elapsed : %lf sec\nCycles : %ld cycles\n",
          (time_end.tv_sec + time_end.tv_nsec * 1e-9)
              - (time_begin.tv_sec + time_begin.tv_nsec * 1e-9),
          rdtsc_end - rdtsc_begin);
#endif
  return 0;
}
