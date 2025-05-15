#include "Leapfrog.hpp"
#include <vector>

void Leapfrog::step(SolarSystem& sys, double dt) {
    sys.compute_accelerations();
    size_t N = sys.bodies.size();
    std::vector<Vector3D> old_acc(N);
    for (size_t i = 0; i < N; ++i)
        old_acc[i] = sys.bodies[i].accel;

    // Posiciones
    for (size_t i = 0; i < N; ++i) {
        auto& b = sys.bodies[i];
        b.pos = b.pos + b.vel * dt + old_acc[i] * (0.5 * dt * dt);
    }

    // Recalcula aceleraciones en nueva posición
    sys.compute_accelerations();

    // Velocidades
    for (size_t i = 0; i < N; ++i) {
        auto& b = sys.bodies[i];
        b.vel = b.vel + (old_acc[i] + b.accel) * (0.5 * dt);
    }
}
