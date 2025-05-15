#pragma once
#include <memory>
#include "SolarSystem.hpp"
#include "Integrator.hpp"

void buildSolarSystem(SolarSystem& sys);
void runSimulation(std::unique_ptr<Integrator> integrator,
                   const SolarSystem& initial,
                   int nSteps,
                   double dt,
                   const std::string& namePrefix);
