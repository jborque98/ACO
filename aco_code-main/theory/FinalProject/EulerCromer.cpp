#include "EulerCromer.hpp"

void EulerCromer::step(SolarSystem& sys, double dt) {
    sys.compute_accelerations();
    for (auto& b : sys.bodies) {
        b.vel = b.vel + b.accel * dt;
        b.pos = b.pos + b.vel   * dt;
    }
}