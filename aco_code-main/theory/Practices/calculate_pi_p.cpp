#include <iostream>
#include <cmath>
#include <omp.h>

int main() {
    int N = 10000000; // Número de términos
    double sum = 0.0;

    double start_time = omp_get_wtime(); // Inicio del tiempo

    #pragma omp parallel for reduction(+:sum)
    for (int k = 0; k < N; k++) {
        sum += pow(-1.0 / 3.0, k) / (2 * k + 1);
    }

    double pi = sqrt(12) * sum;
    double end_time = omp_get_wtime(); // Fin del tiempo

    std::cout << "Valor de π con OpenMP: " << pi << std::endl;
    std::cout << "Tiempo de ejecución: " << (end_time - start_time) << " segundos." << std::endl;
    std::cout << "Presione ENTER para salir...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}


