#include <iostream>
#include <fstream>
#include <iomanip>
#include "KEPLER_COMMON.hpp"
#include "rk4.hpp"
#include "leap_frog.hpp"

void save_positions(const char* filename,
                    const Vector3D pos[],
                    int N) {
    std::ofstream fout(filename);
    if (!fout) {
        std::cerr << "Error al abrir " << filename << "\n";
        return;
    }
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
    Vector3D pos0(AU, 0.0, 0.0);
    Vector3D vel0(0.0, 29.78e3, 0.0);

    Vector3D posRK[N_steps], velRK[N_steps];
    Vector3D posLF[N_steps], velLF[N_steps];

    // Integración RK4
    rk4Integrate(pos0, vel0, N_steps, posRK, velRK);
    save_positions("posiciones_RK4.txt", posRK, N_steps);

    // Integración Leapfrog
    leapfrogIntegrate(pos0, vel0, N_steps, posLF, velLF);
    save_positions("posiciones_LF.txt", posLF, N_steps);

    std::cout << "Final position (RK4): ("
              << posRK[N_steps-1].x << ", "
              << posRK[N_steps-1].y << ", "
              << posRK[N_steps-1].z << ")\n";

    std::cout << "Final position (Leapfrog): ("
              << posLF[N_steps-1].x << ", "
              << posLF[N_steps-1].y << ", "
              << posLF[N_steps-1].z << ")\n";

    std::cout << "Total time elapsed: "
              << (N_steps * dt) / (365.0 * 24 * 60 * 60)
              << " years\n";
    std::cout << "Numer of steps: " << N_steps << "\n";
    std::cout << "Time step: " << dt << " seconds\n";

    return 0;
}
