#include "RK4.hpp"
#include <vector>

void RK4::step(SolarSystem& sys, double dt) {
    size_t N = sys.bodies.size();
    std::vector<Vector3D> p0(N), v0(N);
    for (size_t i = 0; i < N; ++i) {
        p0[i] = sys.bodies[i].pos;
        v0[i] = sys.bodies[i].vel;
    }

    // k1
    sys.compute_accelerations();
    std::vector<Vector3D> k1_p(N), k1_v(N);
    for (size_t i = 0; i < N; ++i) {
        k1_p[i] = v0[i];
        k1_v[i] = sys.bodies[i].accel;
    }

    // k2
    SolarSystem temp = sys;
    for (size_t i = 0; i < N; ++i) {
        temp.bodies[i].pos = p0[i] + k1_p[i] * (dt * 0.5);
        temp.bodies[i].vel = v0[i] + k1_v[i] * (dt * 0.5);
    }
    temp.compute_accelerations();
    std::vector<Vector3D> k2_p(N), k2_v(N);
    for (size_t i = 0; i < N; ++i) {
        k2_p[i] = temp.bodies[i].vel;
        k2_v[i] = temp.bodies[i].accel;
    }

    // k3
    temp = sys;
    for (size_t i = 0; i < N; ++i) {
        temp.bodies[i].pos = p0[i] + k2_p[i] * (dt * 0.5);
        temp.bodies[i].vel = v0[i] + k2_v[i] * (dt * 0.5);
    }
    temp.compute_accelerations();
    std::vector<Vector3D> k3_p(N), k3_v(N);
    for (size_t i = 0; i < N; ++i) {
        k3_p[i] = temp.bodies[i].vel;
        k3_v[i] = temp.bodies[i].accel;
    }

    // k4
    temp = sys;
    for (size_t i = 0; i < N; ++i) {
        temp.bodies[i].pos = p0[i] + k3_p[i] * dt;
        temp.bodies[i].vel = v0[i] + k3_v[i] * dt;
    }
    temp.compute_accelerations();
    std::vector<Vector3D> k4_p(N), k4_v(N);
    for (size_t i = 0; i < N; ++i) {
        k4_p[i] = temp.bodies[i].vel;
        k4_v[i] = temp.bodies[i].accel;
    }

    // Actualiza posición y velocidad
    for (size_t i = 0; i < N; ++i) {
        sys.bodies[i].pos = p0[i] + 
          (k1_p[i] + k2_p[i]*2.0 + k3_p[i]*2.0 + k4_p[i]) * (dt/6.0);
        sys.bodies[i].vel = v0[i] + 
          (k1_v[i] + k2_v[i]*2.0 + k3_v[i]*2.0 + k4_v[i]) * (dt/6.0);
    }
}
