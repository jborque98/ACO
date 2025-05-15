#include "WisdomHolman.hpp"
#include <cmath>
#include <algorithm>  // std::max

// Producto escalar
static double dot(const Vector3D& a, const Vector3D& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

void WisdomHolman::keplerDrift(SolarSystem& sys, int i, double dt) {
    Body& sun = sys.bodies[0];
    Body& bi  = sys.bodies[i];

    // Vectores relativos
    Vector3D r0 = bi.pos - sun.pos;
    Vector3D v0 = bi.vel - sun.vel;
    double mu   = G * (sun.mass + bi.mass);

    double r0n  = r0.norma();
    double v0n2 = dot(v0, v0);

    // Energía específica y semieje mayor a
    double energy = 0.5*v0n2 - mu/r0n;
    if (energy >= 0) {
        energy = -1e-8 * mu / r0n;
    }
    double a = -mu / (2 * energy);

    // Vector excentricidad robusto
    Vector3D h     = r0.cross(v0);
    Vector3D e_vec = (v0.cross(h))*(1.0/mu) - r0*(1.0/r0n);
    double e       = e_vec.norma();

    // Anomalía media M = n·dt, reducido módulo 2π
    double n  = std::sqrt(mu/(a*a*a));
    double M  = std::fmod(n*dt, 2*M_PI);

    // Newton–Raphson para E
    double E = M;
    for (int it = 0; it < 30; ++it) {
        double f   = E - e*std::sin(E) - M;
        double fp  = 1 - e*std::cos(E);
        double dE  = f / fp;
        E -= dE;
        if (std::abs(dE) < 1e-12) break;
    }

    // Calculamos f, g, ḟ, ġ
    double cosE  = std::cos(E);
    double sinE  = std::sin(E);
    double f_coef = 1 - (a/r0n) * (1 - cosE);
    double g_coef = dt + (1.0/n) * (sinE - E);
    double rnorm  = a * (1 - e*cosE);
    double fdot   = -std::sqrt(mu*a)/(r0n*rnorm) * sinE;
    double gdot   = 1 - (a/rnorm) * (1 - cosE);

    // **Aquí** actualizamos usando las variables correctas
    bi.pos = sun.pos + r0*f_coef + v0*g_coef;
    bi.vel = sun.vel + r0*fdot   + v0*gdot;
}

WisdomHolman::~WisdomHolman() {
    // definición vacía, pero NECESARIA para emitir la vtable
}

void WisdomHolman::step(SolarSystem& sys, double dt) {
    int N = sys.bodies.size();
    // medio drift
    for (int i = 1; i < N; ++i)
        keplerDrift(sys, i, dt * 0.5);
    // kick
    sys.compute_accelerations();
    for (int i = 1; i < N; ++i)
        sys.bodies[i].vel = sys.bodies[i].vel + sys.bodies[i].accel * dt;
    // segundo medio drift
    for (int i = 1; i < N; ++i)
        keplerDrift(sys, i, dt * 0.5);
}