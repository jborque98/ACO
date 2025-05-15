#include "SolarSystem.hpp"
#include "Constants.hpp"
#include <cmath>
#include <omp.h>

void SolarSystem::add_body(const std::string& name,
                           double mass,
                           const Vector3D& pos,
                           const Vector3D& vel) {
    bodies.push_back({name, mass, pos, vel, Vector3D()});
}

void SolarSystem::compute_accelerations() {
    size_t N = bodies.size();
    // Reset aceleraciones
    for (auto& b : bodies) {
        b.accel = Vector3D();
    }
    // Cálculo par a par
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < N; ++i) {
        Vector3D a_i;
        for (size_t j = 0; j < N; ++j) {
            if (i == j) continue;
            Vector3D dr = bodies[j].pos - bodies[i].pos;
            double inv_r3 = 1.0 / (std::pow(dr.norma(), 3) + 1e-30);
            a_i = a_i + dr * (G * bodies[j].mass * inv_r3);
        }
        bodies[i].accel = a_i;
    }
}

double SolarSystem::total_energy() const {
    double E = 0.0;
    size_t N = bodies.size();
    // Energía cinética
    for (const auto& b : bodies) {
        E += 0.5 * b.mass * b.vel.norma() * b.vel.norma();
    }
    // Energía potencial (cada par una sola vez)
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i + 1; j < N; ++j) {
            Vector3D dr = bodies[j].pos - bodies[i].pos;
            E -= G * bodies[i].mass * bodies[j].mass / dr.norma();
        }
    }
    return E;
} 
Vector3D SolarSystem::total_angular_momentum() const {
    Vector3D L(0,0,0);
    for (const auto& b : bodies) {
        // L_i = m_i * (r_i × v_i)
        L = L + b.pos.cross(b.vel) * b.mass;
    }
    return L;
}
