#include "Main.hpp"
#include "Euler.hpp"
#include "EulerCromer.hpp"
#include "Leapfrog.hpp"
#include "RK4.hpp"
#include "Constants.hpp"
#include "MultiRateLeapfrog.hpp"
#include "MultiRateRK4.hpp"
#include "Yoshida.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>   


void buildSolarSystem(SolarSystem& sys) {
    // Sol
    sys.add_body("Sun", 1.989e30, Vector3D(0,0,0), Vector3D(0,0,0));
    // Mercurio
    sys.add_body("Mercury", 3.3011e23, Vector3D(0.387*AU,0,0), Vector3D(0,47.36e3,0));
    // Venus
    sys.add_body("Venus", 4.8675e24, Vector3D(0.723*AU,0,0), Vector3D(0,35.02e3,0));
    // Tierra
    sys.add_body("Earth", 5.9724e24, Vector3D(1.0*AU,0,0), Vector3D(0,29.78e3,0));
    // Luna (relativa a la Tierra)
    {
      auto& earth = sys.bodies.back();
      sys.add_body("Moon", 7.342e22,
                   earth.pos + Vector3D(384400e3,0,0),
                   earth.vel + Vector3D(0,1022,0));
    }
    // Marte
    sys.add_body("Mars", 6.4171e23, Vector3D(1.524*AU,0,0), Vector3D(0,24.077e3,0));
    // Júpiter
    sys.add_body("Jupiter", 1.8982e27, Vector3D(5.203*AU,0,0), Vector3D(0,13.07e3,0));
    // Saturno
    sys.add_body("Saturn", 5.6834e26, Vector3D(9.537*AU,0,0), Vector3D(0,9.69e3,0));
    // Urano
    sys.add_body("Uranus", 8.6810e25, Vector3D(19.191*AU,0,0), Vector3D(0,6.80e3,0));
    // Neptuno
    sys.add_body("Neptune",1.02413e26, Vector3D(30.07*AU,0,0), Vector3D(0,5.43e3,0));
}

void save_snapshot(const SolarSystem& sys, std::ofstream& fout, double t) {
    // Calcula energía y momento angular del sistema
    double E = sys.total_energy();
    Vector3D Lvec = sys.total_angular_momentum();
    double Lmag = Lvec.norma();

    // Vuelca un snapshot de cada cuerpo, añadiendo E y L al final
    for (const auto& b : sys.bodies) {
        fout << b.name << "," 
             << t      << ","
             << b.pos.x << "," << b.pos.y << "," << b.pos.z << ","
             << b.vel.x << "," << b.vel.y << "," << b.vel.z << ","
             << E      << "," << Lmag    << "\n";
    }
}


void runSimulation(std::unique_ptr<Integrator> integrator,
                   const SolarSystem& initial,
                   int nSteps,
                   double dt,
                   const std::string& namePrefix) {
    SolarSystem sys = initial;
    std::string fname = namePrefix + ".csv";
    std::ofstream fout(fname);
    fout << "name,t,x,y,z,vx,vy,vz,E,L\n";


    double t = 0.0;
    save_snapshot(sys, fout, t);

    for (int i = 0; i < nSteps; ++i) {
        integrator->step(sys, dt);
        t += dt;
        save_snapshot(sys, fout, t);    // SIN if
    }
    std::cout << "Finished '" << namePrefix << "'. Output: " << fname << "\n";
}

int main(int argc, char* argv[]) {
    // Valores por defecto
    int    nSteps     = 1000;
    double totalYears = 2.5;

    // Simple parser de línea de comandos
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("--steps=", 0) == 0) {
            nSteps = std::stoi(arg.substr(8));
        }
        else if (arg.rfind("--years=", 0) == 0) {
            totalYears = std::stod(arg.substr(8));
        }
    }

    // Calcula dt de forma independiente
    const double sec_per_year = 365.0 * 24.0 * 3600.0;
    double dt = totalYears * sec_per_year / nSteps;

    std::cout << "Integrando " << totalYears << " años en "
              << nSteps << " pasos -> dt = " << dt << " s\n";

    SolarSystem initial;
    buildSolarSystem(initial);



    // Prepara métodos
    std::vector<std::pair<std::string, std::unique_ptr<Integrator>>> methods;
    methods.emplace_back("Euler",       std::make_unique<Euler>());
    methods.emplace_back("EulerCromer", std::make_unique<EulerCromer>());
    methods.emplace_back("Leapfrog",    std::make_unique<Leapfrog>());
    methods.emplace_back("RK4",         std::make_unique<RK4>());
    methods.emplace_back("MultiLF",     std::make_unique<MultiRateLeapfrog>(5, 6.0));
    methods.emplace_back("MultiRK4",    std::make_unique<MultiRateRK4>(5, 6.0));
    methods.emplace_back("Yoshida", std::make_unique<Yoshida>());
    



    // Ejecuta cada método
    for (auto& m : methods) {
        runSimulation(std::move(m.second),
                      initial,
                      nSteps,
                      dt,
                      m.first);
    }

    return 0;
}