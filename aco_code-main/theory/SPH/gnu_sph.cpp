// gnu_sph.cpp
// Compilar: g++ -O3 -o gnu_sph gnu_sph.cpp
// Uso: ./gnu_sph  -> genera 'sph_density.png' con los perfiles de densidad

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

int main() {
    // Lista de archivos generados por la simulación
    std::vector<std::string> files = {
        "data_files/perfil_step0000.dat",
        "data_files/perfil_step0100.dat",
        "data_files/perfil_step0200.dat",
        "data_files/perfil_step0300.dat",
        "data_files/perfil_step0400.dat",
        "data_files/perfil_step0500.dat"
    };

    // Abrimos un pipe a gnuplot en modo persistente
    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        std::cerr << "Error al abrir gnuplot. Asegúrate de tener instalado gnuplot.\n";
        return 1;
    }

    // Configuración de la salida gráfica
    fprintf(gp,
        "set terminal pngcairo size 800,600 enhanced font 'Arial,10'\n"
        "set output 'sph_density.png'\n"
        "set xlabel 'x'\n"
        "set ylabel 'rho'\n"
        "set title 'SPH 1D: Perfiles de densidad'\n"
        "set key left top\n"                // <— aquí añadimos \n
        "set xrange [0.45:0.55]\n"
        "plot ");

    // Construcción de la línea de plot para cada archivo
    for (size_t i = 0; i < files.size(); ++i) {
        std::string step = files[i].substr(22, 4);
        fprintf(gp,
            "'%s' using 1:2 with lines title 'step %s'%s",
            files[i].c_str(), step.c_str(),
            (i + 1 < files.size() ? ", " : ";\n"));
    }

    // Forzamos la escritura y cerramos
    fflush(gp);
    pclose(gp);

    std::cout << "Generado archivo 'sph_density.png' con los perfiles.\n";
    return 0;
}
