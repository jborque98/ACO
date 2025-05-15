#pragma once
#include <vector>
#include "Body.hpp"

class SolarSystem {
public:
    std::vector<Body> bodies;

    void add_body(const std::string& name,
                  double mass,
                  const Vector3D& pos,
                  const Vector3D& vel);

    void compute_accelerations();
    double total_energy() const;
    Vector3D total_angular_momentum() const;
};
