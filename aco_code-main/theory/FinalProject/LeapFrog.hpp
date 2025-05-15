#pragma once
#include "Integrator.hpp"

struct Leapfrog : Integrator {
    void step(SolarSystem& sys, double dt) override;
};
