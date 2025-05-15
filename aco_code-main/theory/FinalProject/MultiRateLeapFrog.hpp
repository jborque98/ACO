#pragma once
#include "Integrator.hpp"
#include "Constants.hpp"
#include <vector>

/// Integrador Multirate usando esquema Verlet/Leapfrog:
/// - nSub subpasos pequeños para cuerpos interiores (r < threshold_AU).
/// - Un paso grande para cuerpos exteriores.
struct MultiRateLeapfrog : Integrator {
    int    nSub;          ///< número de subpasos
    double threshold;     ///< umbral en metros (distancia al Sol)

    /// @param substeps número de subpasos interiores
    /// @param thr_AU   umbral en UA
    MultiRateLeapfrog(int substeps, double thr_AU)
      : nSub(substeps), threshold(thr_AU * AU) {}

    void step(SolarSystem& sys, double DT) override;
};
