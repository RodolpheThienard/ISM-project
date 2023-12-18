#ifndef KERNELS_H
#define KERNELS_H

#include "utils.h"

f64 lennard_jones (f64*, f64 , f64);
f64 * compute_distance (particules_t );
f64 lennard_jones_period (f64 *distance, f64 epsilon, f64 r, u8 period);
f64 * compute_forces (f64 *distance, f64 *particule, f64 epsilon, f64 r);
f64 * forces (f64 *x, f64 *y, f64 *z);
#endif
