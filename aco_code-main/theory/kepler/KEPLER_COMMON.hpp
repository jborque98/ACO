#ifndef KEPLER_COMMON_HPP
#define KEPLER_COMMON_HPP

#include <cmath>

// Parámetros de la simulación
static const int    N_steps  = 1000;
static const double n_orbits = 5.0;
static const double dt       = n_orbits*365*24*60*60 / N_steps;  

// Constantes físicas
static const double G     = 6.67430e-11;
static const double M_sun = 1.989e30;
static const double AU    = 1.496e11;

// Vector en 3D y norma
struct Vector3D {
    double x,y,z;
    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(double x_, double y_, double z_): x(x_), y(y_), z(z_) {}
    double norma() const { return std::sqrt(x*x + y*y + z*z); }
    Vector3D operator+(const Vector3D& v)   const { return Vector3D(x+v.x, y+v.y, z+v.z); }
    Vector3D operator-(const Vector3D& v)   const { return Vector3D(x-v.x, y-v.y, z-v.z); }
    Vector3D operator*(double k)            const { return Vector3D(x*k,   y*k,     z*k    ); }
    Vector3D operator/(double k)            const { return Vector3D(x/k,   y/k,     z/k    ); }
};

// Aceleración gravitatoria debida al Sol
inline Vector3D aceleracion(const Vector3D& pos) {
    double r  = pos.norma();
    double r3 = (r>0 ? r*r*r : 1e-10);
    return Vector3D(
      -G*M_sun * pos.x / r3,
      -G*M_sun * pos.y / r3,
      -G*M_sun * pos.z / r3
    );
}

#endif // KEPLER_COMMON_HPP
