#include "MultiRateRK4.hpp"
#include "SolarSystem.hpp"
#include <cmath>

static void rk4_step_single(SolarSystem& sys, int i, double dt) {
    Vector3D p0 = sys.bodies[i].pos;
    Vector3D v0 = sys.bodies[i].vel;

    // k1
    sys.compute_accelerations();
    Vector3D k1p = v0;
    Vector3D k1v = sys.bodies[i].accel;

    // k2
    sys.bodies[i].pos = p0 + k1p * (dt*0.5);
    sys.bodies[i].vel = v0 + k1v * (dt*0.5);
    sys.compute_accelerations();
    Vector3D k2p = sys.bodies[i].vel;
    Vector3D k2v = sys.bodies[i].accel;

    // k3
    sys.bodies[i].pos = p0 + k2p * (dt*0.5);
    sys.bodies[i].vel = v0 + k2v * (dt*0.5);
    sys.compute_accelerations();
    Vector3D k3p = sys.bodies[i].vel;
    Vector3D k3v = sys.bodies[i].accel;

    // k4
    sys.bodies[i].pos = p0 + k3p * dt;
    sys.bodies[i].vel = v0 + k3v * dt;
    sys.compute_accelerations();
    Vector3D k4p = sys.bodies[i].vel;
    Vector3D k4v = sys.bodies[i].accel;

    // restaurar estado original y actualizar
    sys.bodies[i].pos = p0 + (k1p + k2p*2.0 + k3p*2.0 + k4p)*(dt/6.0);
    sys.bodies[i].vel = v0 + (k1v + k2v*2.0 + k3v*2.0 + k4v)*(dt/6.0);
}

void MultiRateRK4::step(SolarSystem& sys, double DT) {
    double dt_sub = DT / nSub;
    std::vector<int> interior, exterior;
    for (int i = 0; i < (int)sys.bodies.size(); ++i) {
        if (sys.bodies[i].pos.norma() < threshold)
            interior.push_back(i);
        else
            exterior.push_back(i);
    }
    for (int k = 0; k < nSub; ++k) {
        for (int i : interior) {
            rk4_step_single(sys, i, dt_sub);
        }
    }

    for (int i : exterior) {
        rk4_step_single(sys, i, DT);
    }
}
