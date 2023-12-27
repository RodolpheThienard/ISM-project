#ifndef UTILS_H
#define UTILS_H

// includes

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

// typedef
typedef double f64;
typedef int32_t i32;
typedef u_int64_t u64;
typedef u_int8_t u8;
typedef u_int32_t u32;

typedef struct
{
  f64 *x;
  f64 *y;
  f64 *z;
} particules_t;

// Macros

#define ALLOC(X, n)                                                           \
  do                                                                          \
    {                                                                         \
      X = malloc (sizeof (*X) * n);                                           \
      if (!X)                                                                 \
        {                                                                     \
          perror ("malloc");                                                  \
          exit (1);                                                           \
        }                                                                     \
      memset (X, 0, sizeof (*X) * n);                                         \
    }                                                                         \
  while (0)

#define SQUARE(X) X *X
#define CUBE(X) X *X *X

// Fixed values
#define SIZE 1000
#define EPSILON 0.2
#define R 3.0
/* Creation of 27 sym from {-l, -l, -l} to {l, l, l}.
   Can Have 3 values {-l, 0, l} */
#define N_SYM 27
#define L 30
#define R_CUT 10.0

// Functions

particules_t parser (FILE *);
particules_t periodic_location (particules_t p, f64 coef_x, f64 coef_y,
                                f64 coef_z);
void free_particules_t (particules_t p);
void print_particules (particules_t);
void print_matrix (f64 *, u64, u64);
void print_matrix_scientist (f64 *, u64, u64);
#endif
