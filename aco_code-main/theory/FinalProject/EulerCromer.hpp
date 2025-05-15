#pragma once
#include "Integrator.hpp"

struct EulerCromer : Integrator {
    void step(SolarSystem& sys, double dt) override;
};