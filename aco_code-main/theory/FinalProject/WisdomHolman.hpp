// WisdomHolman.hpp
#pragma once
#include "Integrator.hpp"
#include "Constants.hpp"
#include "SolarSystem.hpp"

struct WisdomHolman : Integrator {
    ~WisdomHolman() override;                // 1) Destructor declarado
    void step(SolarSystem& sys, double dt) override;  // 2) step declarado

private:
    void keplerDrift(SolarSystem& sys, int i, double dt);
};