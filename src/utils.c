#include "../include/utils.h"

particules_t
parser (FILE *file)
{
  f64 *x, *y, *z;
  ALLOC (x, SIZE);
  ALLOC (y, SIZE);
  ALLOC (z, SIZE);

  particules_t particules = { x, y, z };

  i32 trash = 0;
  fscanf (file, "%d %d", &trash, &trash);

  for (u64 i = 0; i < SIZE; i++)
    fscanf (file, "%d %lf %lf %lf", &trash, particules.x + i, particules.y + i,
            particules.z + i);

  return particules;
}

particules_t
periodic_location (particules_t p, f64 coef_x, f64 coef_y, f64 coef_z)
{
  f64 *x, *y, *z;
  ALLOC (x, SIZE);
  ALLOC (y, SIZE);
  ALLOC (z, SIZE);

  for (size_t i = 0; i < SIZE; i++)
    {
      x[i] = p.x[i] + coef_x;
      y[i] = p.y[i] + coef_y;
      z[i] = p.z[i] + coef_z;
    }

  particules_t p_out = { x, y, z };
  return p_out;
}

void
free_particules_t (particules_t p)
{
  free (p.x);
  free (p.y);
  free (p.z);
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
