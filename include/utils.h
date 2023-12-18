#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef double f64;
typedef int32_t i32;
typedef u_int64_t u64;
typedef u_int8_t u8;

#define ALLOC(X, Y)                                                           \
  do                                                                          \
    {                                                                         \
      Y = malloc (X);                                                         \
      memset (Y, 0, X);                                                       \
    }                                                                         \
  while (0)

#define SQUARE(X) X*X
#define CUBE(X) X*X*X

// Fixed values
#define SIZE 1000
#define EPSILON 0.2
#define R 3.0
#define N_SYM 27
#define R_CUT 10.0

typedef struct {
  f64 *x;
  f64 *y;
  f64 *z;
}particules_t;

particules_t parser(FILE*);
void print_particules(particules_t);
void print_matrix (f64 *, u64 , u64 );
void print_matrix_scientist (f64 *, u64 , u64 );
#endif
