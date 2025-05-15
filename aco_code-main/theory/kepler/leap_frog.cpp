#include "leap_frog.hpp"

void leapfrogIntegrate(const Vector3D& p0,
                       const Vector3D& v0,
                       int N,
                       Vector3D pos[],
                       Vector3D vel[]) {
    pos[0] = p0;
    vel[0] = v0;
    // paso medio de velocidad
    Vector3D vh = v0 + aceleracion(p0)*(dt/2.0);

    for (int i = 0; i < N-1; ++i) {
        pos[i+1] = pos[i] + vh*dt;
        Vector3D a1 = aceleracion(pos[i+1]);
        vh = vh + a1*dt;
        vel[i+1] = vh - a1*(dt/2.0);
    }
}
