#pragma once
#include <cmath>

struct Vector3D {
    double x, y, z;
    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(double x_, double y_, double z_): x(x_), y(y_), z(z_) {}
    double norma() const { return std::sqrt(x*x + y*y + z*z); }
    Vector3D operator+(const Vector3D& v) const { return Vector3D(x+v.x, y+v.y, z+v.z); }
    Vector3D operator-(const Vector3D& v) const { return Vector3D(x-v.x, y-v.y, z-v.z); }
    Vector3D operator*(double k) const      { return Vector3D(x*k,   y*k,   z*k  ); }
    Vector3D operator/(double k) const      { return Vector3D(x/k,   y/k,   z/k  ); }

    // Producto vectorial
    Vector3D cross(const Vector3D& v) const {
      return Vector3D(
        y*v.z - z*v.y,
        z*v.x - x*v.z,
        x*v.y - y*v.x
      );
    }
};
