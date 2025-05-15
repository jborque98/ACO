#pragma once
#include "Integrator.hpp"

struct Euler : Integrator {
    void step(SolarSystem& sys, double dt) override;
};
