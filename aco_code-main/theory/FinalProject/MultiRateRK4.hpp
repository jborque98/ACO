#pragma once
#include "Integrator.hpp"
#include "Constants.hpp"
#include <vector>

/// Integrador Multirate basado en RK4:
/// - nSub subpasos pequeños para interiores (r < threshold_AU) usando RK4.
/// - Un paso grande para exteriores usando RK4.
struct MultiRateRK4 : Integrator {
    int    nSub;        ///< número de subpasos
    double threshold;   ///< umbral en metros

    MultiRateRK4(int substeps, double thr_AU)
      : nSub(substeps), threshold(thr_AU * AU) {}

    void step(SolarSystem& sys, double DT) override;
};
