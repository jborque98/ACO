#pragma once
#include "SolarSystem.hpp"

struct Integrator {
    virtual ~Integrator() = default;
    virtual void step(SolarSystem& sys, double dt) = 0;
};
