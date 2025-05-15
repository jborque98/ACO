#pragma once

#include <string>       // <<-- ¡MUY IMPORTANTE!
#include "Vector3D.hpp"

struct Body {
    std::string name;
    double      mass;
    Vector3D    pos;
    Vector3D    vel;
    Vector3D    accel;
};

