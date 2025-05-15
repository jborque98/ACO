#include "Euler.hpp"

void Euler::step(SolarSystem& sys, double dt) {
    sys.compute_accelerations();
    for (auto& b : sys.bodies) {
        b.pos = b.pos + b.vel   * dt;
        b.vel = b.vel + b.accel * dt;
    }
}
