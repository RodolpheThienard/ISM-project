#include "../include/kernels.h"

f64 *
compute_distance (particules_t particules)
{
  f64 *distance;
  ALLOC (distance, SIZE * SIZE);

  for (u64 i = 0; i < SIZE; i++)
    {
      for (u64 j = 0; j < SIZE; j++)
        {
          distance[i * SIZE + j]
              = SQUARE ((particules.x[i] - particules.x[j]))
                + SQUARE ((particules.y[i] - particules.y[j]))
                + SQUARE ((particules.z[i] - particules.z[j]));
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
          f64 dist = SQUARE (r) / distance[i * SIZE + j];
          f64 dist_3 = CUBE (dist);
          u += epsilon_4 * dist_3 * (dist_3 - 2);
        }
    }
  return u;
}

// TODO ENERGY not right ISM3.PDF
f64
lennard_jones_period (f64 *distance, f64 epsilon, f64 r, u8 period)
{
  f64 u = 0.;
  f64 epsilon_4 = 4 * epsilon;
  for (u8 l = 0; l < period; l++)
    for (u64 i = 0; i < SIZE; i++)
      {
        for (u64 j = i + 1; j < SIZE; j++)
          {
            f64 rij = distance[i * SIZE + j];
            if (rij < R_CUT)
              break;
            f64 dist = SQUARE (r) / rij;
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
  ALLOC (vector, SIZE * SIZE);
  f64 epsilon_4 = -48 * epsilon;
  for (u64 i = 0; i < SIZE; i++)
    for (u64 j = i + 1; j < SIZE; j++)
      {
        f64 dist = SQUARE (r) / distance[i * SIZE + j];
        f64 dist_6 = CUBE (dist);
        f64 dist_8 = SQUARE (SQUARE (dist));
        f64 force = epsilon_4 * dist_8 * (dist_6 - 1)
                    * (particule[i] - particule[j]);
        vector[i * SIZE + j] = force;
        vector[j * SIZE + i] = -force;
      }
  return vector;
}

f64 *
forces (f64 *x, f64 *y, f64 *z)
{
  f64 *forces;
  ALLOC (forces, 3);
  for (u64 i = 0; i < SIZE; i++)
    for (u64 j = 0; j < SIZE; j++)
      {
        forces[0] += x[i * SIZE + j];
        forces[1] += y[i * SIZE + j];
        forces[2] += z[i * SIZE + j];
      }
  return forces;
}

f64
cinetic_energy (particules_t p, f64 m, size_t n)
{
  f64 coef = 1. / 2 * CONVERSION_FORCE;
  f64 sum = 0.;
  for (size_t i = 0; i < n; i++)
    {
      f64 tmp = (p.x[i] * p.x[i] * p.y[i] * p.y[i] * p.z[i] * p.z[i]) / m;
      sum += tmp;
    }

  return sum * coef;
}

/* NDL= 3xN_PARTICULES_TOTAL - 3 */
f64
cinetic_temperature (f64 energy)
{
  return (1. / (CONSTANTE_R * NDL)) * energy;
}

cinetic_t
cinetic (particules_t p, f64 m, size_t n)
{

  f64 energy = cinetic_energy (p, m, n);
  f64 temperature = cinetic_temperature (energy);
  cinetic_t cinetic = { energy, temperature };
  return cinetic;
}

/* TODO
   cinétic moment
f64 *
startup_dim (f64 *dim)
{
  for (u32 i = 0; i < SIZE; i++)
    {
      f64 c = (f64)rand_r (&i);
      f64 s = (f64)rand_r (&i);
      dim[i] = ;
    }
}

void
startup ()
{
}
*/

/* Compute Temperature at m_step */
void
berendsen_thermostat (particules_t p, particules_t default_p, size_t m_step)
{
  // T = (default_p.x * GAMMA * T0) / p.x + 1;
}
