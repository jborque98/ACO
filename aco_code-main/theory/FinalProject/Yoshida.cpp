#include "Yoshida.hpp"
#include "Constants.hpp"
#include <array>

// Coeficientes de Forest–Ruth / Yoshida 4º orden
// α = 1/(2-2^(1/3)), β = -2^(1/3)*α
static constexpr double α = 1.0/(2.0 - std::cbrt(2.0));
static constexpr double β = -std::cbrt(2.0)*α;

// Dividimos en sub-coeficientes:
static constexpr std::array<double,4> a = {
    +α/2.0,
    +(β+α)/2.0,
    +(β+α)/2.0,
    +α/2.0
};
static constexpr std::array<double,3> b = {
    +α,
    +β,
    +α
};

void Yoshida::step(SolarSystem& sys, double dt) {
    // 4 drifts (posiciones) y 3 kicks (velocidades)
    // Drift: r += v * (a[i]*dt)
    // Kick:  compute_accelerations(); v += a * (b[j]*dt)
    // i runs 0..3, j runs 0..2 in interleaved fashion.
    for (int i = 0; i < 4; ++i) {
        // Drift
        double tau = a[i] * dt;
        for (auto& body : sys.bodies) {
            body.pos = body.pos + body.vel * tau;
        }
        if (i < 3) {
            // Kick
            double chi = b[i] * dt;
            sys.compute_accelerations();
            for (auto& body : sys.bodies) {
                body.vel = body.vel + body.accel * chi;
            }
        }
    }
}
