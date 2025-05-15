#include "MultiRateLeapfrog.hpp"
#include <cmath>

void MultiRateLeapfrog::step(SolarSystem& sys, double DT) {
    const double dt_sub = DT / nSub;

    // 1) Identifica interiores/exteriores
    std::vector<int> interior, exterior;
    for (int i = 0; i < (int)sys.bodies.size(); ++i) {
        if (sys.bodies[i].pos.norma() < threshold)
            interior.push_back(i);
        else
            exterior.push_back(i);
    }

    // 2) nSub subpasos de Leapfrog para interiores
    for (int k = 0; k < nSub; ++k) {
        // a) calcula aceleraciones completas
        sys.compute_accelerations();
        // b) medio paso de velocidad para interiores
        std::vector< Vector3D > v_half(sys.bodies.size());
        for (int i : interior) {
            v_half[i] = sys.bodies[i].vel + sys.bodies[i].accel * (dt_sub*0.5);
        }
        // c) paso completo de posición
        for (int i : interior) {
            sys.bodies[i].pos = sys.bodies[i].pos + v_half[i] * dt_sub;
        }
        // d) recalcula aceleraciones tras mover interiores
        sys.compute_accelerations();
        // e) completa medio paso de velocidad
        for (int i : interior) {
            sys.bodies[i].vel = v_half[i] + sys.bodies[i].accel * (dt_sub*0.5);
        }
    }

    // 3) Un paso grande de Leapfrog para exteriores
    sys.compute_accelerations();
    // velocidad completa y posición completa con DT
    for (int i : exterior) {
        auto& b = sys.bodies[i];
        b.vel = b.vel + b.accel * DT;
        b.pos = b.pos + b.vel   * DT;
    }
}
