#include "../include/kernels.h"
#include <math.h>

f64 *
compute_distance (particules_t particules)
{
  f64 *distance;
  ALLOC (sizeof (f64) * SIZE * SIZE, distance);

  for (u64 i = 0; i < SIZE; i++)
    {
      for (u64 j = 0; j < SIZE; j++)
        {
          distance[i * SIZE + j] = (particules.x[i] - particules.x[j])
                                       * (particules.x[i] - particules.x[j])
                                   + (particules.y[i] - particules.y[j])
                                         * (particules.y[i] - particules.y[j])
                                   + (particules.z[i] - particules.z[j])
                                         * (particules.z[i] - particules.z[j]);
        }
    }

  return distance;
}

f64
lennard_jones (f64 *distance, f64 epsilon, f64 r)
{
  f64 u = 0.;
  f64 epsilon_4 = 4 * epsilon;
  for (u64 i = 0; i < SIZE; i++)
    {
      for (u64 j = i + 1; j < SIZE; j++)
        {
          f64 dist = r * r / distance[i * SIZE + j];
          f64 dist_3 = CUBE (dist);
          u += epsilon_4 * dist_3 * (dist_3 - 2);
        }
    }
  return u;
}

f64 *
compute_forces (f64 *distance, f64 *particule, f64 epsilon, f64 r)
{
  f64 *vector;
  ALLOC (sizeof (f64) * SIZE * SIZE, vector);
  f64 epsilon_4 = -48 * epsilon;
  for (u64 i = 0; i < SIZE; i++)
    for (u64 j = i + 1; j < SIZE; j++)
      {
        f64 dist = r * r / distance[i * SIZE + j];
        f64 dist_3 = CUBE (dist);
        f64 dist_4 = SQUARE (SQUARE (dist));
        f64 force
            = epsilon_4 * dist_4 * (dist_3 - 1) * particule[i] - particule[j];
        vector[i * SIZE + j] = force;
        vector[j * SIZE + i] = -force;
      }
  return vector;
}

f64 *
forces (f64 *x, f64 *y, f64 *z)
{
  f64 *forces;
  ALLOC (sizeof (f64) * 3, forces);
  for (u64 i = 0; i < SIZE; i++)
    for (u64 j = 0; j < SIZE; j++)
      {
        forces[0] += x[i * SIZE + j];
        forces[1] += y[i * SIZE + j];
        forces[2] += z[i * SIZE + j];
      }
  return forces;
}
