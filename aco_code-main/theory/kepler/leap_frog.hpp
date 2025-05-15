#ifndef LEAPFROG_HPP
#define LEAPFROG_HPP

#include "KEPLER_COMMON.hpp"

// Leapfrog (Verlet) completo: integra posición y velocidad en arrays
void leapfrogIntegrate(const Vector3D& p0,
                       const Vector3D& v0,
                       int N,
                       Vector3D pos[],
                       Vector3D vel[]);

#endif // LEAPFROG_HPP
