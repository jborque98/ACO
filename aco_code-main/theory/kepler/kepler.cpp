#include <iostream>
#include <fstream>
#include <cmath>
#include <omp.h>
#include <iomanip>

const int N_steps = 10;
const double n_orbits = 5.0;
const double dt     = n_orbits*365*24*60*60 / N_steps;  

const double G      = 6.67430e-11;
const double M_sun  = 1.989e30;
const double AU     = 1.496e11;

struct Vector3D {
    double x,y,z;
    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(double x_,double y_,double z_): x(x_), y(y_), z(z_) {}
    double norma() const { return std::sqrt(x*x+y*y+z*z); }
    Vector3D operator+(const Vector3D& v) const { return Vector3D(x+v.x,y+v.y,z+v.z); }
    Vector3D operator-(const Vector3D& v) const { return Vector3D(x-v.x,y-v.y,z-v.z); }
    Vector3D operator*(double k) const      { return Vector3D(x*k,y*k,z*k); }
    Vector3D operator/(double k) const      { return Vector3D(x/k,y/k,z/k); }
};

Vector3D aceleracion(const Vector3D& pos) {
    double r = pos.norma();
    double r3 = r>0 ? r*r*r : 1e-10;
    return Vector3D(-G*M_sun*pos.x/r3,
                    -G*M_sun*pos.y/r3,
                    -G*M_sun*pos.z/r3);
}

void leapfrogIntegrate(const Vector3D& p0, const Vector3D& v0, int N, Vector3D pos[], Vector3D vel[]) {
    pos[0]=p0;
    vel[0]=v0;
    Vector3D vh = v0 + aceleracion(p0)*(dt/2.0);
    for(int i=0;i<N-1;++i){
        pos[i+1] = pos[i] + vh*dt;
        Vector3D a1 = aceleracion(pos[i+1]);
        vh = vh + a1*dt;
        vel[i+1] = vh - a1*(dt/2.0);
    }
}

void rk4_step(Vector3D& pos, Vector3D& vel, double dt) {
    Vector3D k1p = vel;
    Vector3D k1v = aceleracion(pos);

    Vector3D pos2 = pos + k1p*(dt/2.0);
    Vector3D vel2 = vel + k1v*(dt/2.0);
    Vector3D k2p  = vel2;
    Vector3D k2v  = aceleracion(pos2);

    Vector3D pos3 = pos + k2p*(dt/2.0);
    Vector3D vel3 = vel + k2v*(dt/2.0);
    Vector3D k3p  = vel3;
    Vector3D k3v  = aceleracion(pos3);

    Vector3D pos4 = pos + k3p*dt;
    Vector3D vel4 = vel + k3v*dt;
    Vector3D k4p  = vel4;
    Vector3D k4v  = aceleracion(pos4);

    pos = pos + (k1p + k2p*2.0 + k3p*2.0 + k4p)*(dt/6.0);
    vel = vel + (k1v + k2v*2.0 + k3v*2.0 + k4v)*(dt/6.0);
}

void RungeKutta4(const Vector3D& pos0,
                 const Vector3D& vel0,
                 int N,
                 Vector3D pos[],
                 Vector3D vel[]) {
    pos[0] = pos0;
    vel[0] = vel0;
    for (int i = 0; i < N-1; ++i) {
        pos[i+1] = pos[i];
        vel[i+1] = vel[i];
        rk4_step(pos[i+1], vel[i+1], dt);
    }
}

void save_positions(const char* filename,
                    const Vector3D pos[],
                    int N)
{
    std::ofstream fout(filename);
    if (!fout) return;
    fout << std::scientific << std::setprecision(6);
    for (int i = 0; i < N; ++i) {
        double t_i = i * dt;
        fout << t_i << " "
             << pos[i].x << " "
             << pos[i].y << " "
             << pos[i].z << "\n";
    }
}


int main() {
    Vector3D pos0(AU,0.0,0.0);
    Vector3D vel0(0.0,29.78e3,0.0);
    Vector3D posRK[N_steps], velRK[N_steps], posLF[N_steps], velLF[N_steps];

    RungeKutta4(pos0, vel0, N_steps, posRK, velRK);
    leapfrogIntegrate(pos0,vel0,N_steps,posLF,velLF);

    save_positions("posiciones.txt", posRK, N_steps);
    save_positions("posiciones_LF.txt", posLF, N_steps);


    std::cout << "Final position (RK): (" 
              << posRK[N_steps-1].x << "," 
              << posRK[N_steps-1].y << "," 
              << posRK[N_steps-1].z << ")\n";
    std::cout << "Final position (LF): (" 
              << posLF[N_steps-1].x << "," 
              << posLF[N_steps-1].y << "," 
              << posLF[N_steps-1].z << ")\n";
    std::cout << "Total time elapsed: " 
              << (N_steps * dt) / (365.0 * 24 * 60 * 60) << " years\n";
    return 0;
}
