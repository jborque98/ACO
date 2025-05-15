#pragma once
#include "Integrator.hpp"

/// Integrador simétrico de orden 4 (Yoshida/Forest–Ruth)
struct Yoshida : Integrator {
    void step(SolarSystem& sys, double dt) override;
};
