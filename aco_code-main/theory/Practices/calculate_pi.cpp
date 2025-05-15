#include <iostream>
#include <cmath>
#include <chrono> // Usamos chrono para medir el tiempo

int main() {
    int N = 1000000; // Número de términos
    double sum = 0.0;

    auto start_time = std::chrono::high_resolution_clock::now(); // Inicio del tiempo
    for (int k = 0; k < N; k++) {
        sum += pow(-1.0 / 3.0, k) / (2 * k + 1);
    }

    double pi = sqrt(12) * sum;
    auto end_time = std::chrono::high_resolution_clock::now(); // Fin del tiempo

    std::cout << "Valor de π en serie: " << pi << std::endl;
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos." << std::endl;
    std::cin.ignore();
    std::cin.get();
    return 0;
}
