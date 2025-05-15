#include "rk4.hpp"

// Un paso de RK4 para un solo cuerpo
static void rk4_step(Vector3D& pos, Vector3D& vel, double dt) {
    Vector3D k1p = vel;
    Vector3D k1v = aceleracion(pos);

    Vector3D pos2 = pos + k1p*(dt/2.0);
    Vector3D vel2 = vel + k1v*(dt/2.0);
    Vector3D k2p  = vel2;
    Vector3D k2v  = aceleracion(pos2);

    Vector3D pos3 = pos + k2p*(dt/2.0);
    Vector3D vel3 = vel + k2v*(dt/2.0);
    Vector3D k3p  = vel3;
    Vector3D k3v  = aceleracion(pos3);

    Vector3D pos4 = pos + k3p*dt;
    Vector3D vel4 = vel + k3v*dt;
    Vector3D k4p  = vel4;
    Vector3D k4v  = aceleracion(pos4);

    pos = pos + (k1p + k2p*2.0 + k3p*2.0 + k4p)*(dt/6.0);
    vel = vel + (k1v + k2v*2.0 + k3v*2.0 + k4v)*(dt/6.0);
}

// Integración completa con RK4
void rk4Integrate(const Vector3D& p0,
                  const Vector3D& v0,
                  int N,
                  Vector3D pos[],
                  Vector3D vel[]) {
    pos[0] = p0;
    vel[0] = v0;
    for (int i = 0; i < N-1; ++i) {
        pos[i+1] = pos[i];
        vel[i+1] = vel[i];
        rk4_step(pos[i+1], vel[i+1], dt);
    }
}
