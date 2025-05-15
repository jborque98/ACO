#ifndef RK4_HPP
#define RK4_HPP

#include "KEPLER_COMMON.hpp"

// Integrador de 4º orden: lanza posiciones y velocidades en arrays de tamaño N.
void rk4Integrate(const Vector3D& p0,
                  const Vector3D& v0,
                  int N,
                  Vector3D pos[],
                  Vector3D vel[]);

#endif // RK4_HPP