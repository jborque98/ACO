#pragma once
#include "Integrator.hpp"

struct RK4 : Integrator {
    void step(SolarSystem& sys, double dt) override;
};
