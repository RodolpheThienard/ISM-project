#include "../include/utils.h"

particules_t
parser (FILE *file)
{
  f64 *x, *y, *z;
  ALLOC (sizeof (f64) * SIZE, x);
  ALLOC (sizeof (f64) * SIZE, y);
  ALLOC (sizeof (f64) * SIZE, z);

  particules_t particules = { x, y, z };

  i32 trash = 0;
  fscanf (file, "%d %d", &trash, &trash);

  for (u64 i = 0; i < SIZE; i++)
    fscanf (file, "%d %lf %lf %lf", &trash, particules.x + i, particules.y + i,
            particules.z + i);

  return particules;
}

void
print_particules (particules_t particules)
{
  for (u64 i = 0; i < SIZE; i++)
    printf ("%lf, %lf %lf \n", particules.x[i], particules.y[i],
            particules.z[i]);
}

void
print_matrix (f64 *matrix, u64 size_m, u64 size_n)
{
  for (u64 i = 0; i < size_m; i++)
    {
      for (u64 j = 0; j < size_n; j++)
        printf ("%lf ", matrix[i * size_m + j]);
      printf ("\n");
    }
}

void
print_matrix_scientist (f64 *matrix, u64 size_m, u64 size_n)
{
  for (u64 i = 0; i < size_m; i++)
    {
      for (u64 j = 0; j < size_n; j++)
        printf ("%le ", matrix[i * size_m + j]);
      printf ("\n");
    }
}
