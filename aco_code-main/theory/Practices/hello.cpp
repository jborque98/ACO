#include <iostream>
using namespace std;

// Prototipos de función
int sumas(int, int);
double sumas2(double, double);

int main() {
    int a, b;
    double c, d;

    a = 10;
    b = 20;
    c = 15.5;
    d = 12.6;

    std::cout << "La suma de a y b es: " << sumas(a, b) << endl;
    std::cout << "La suma de c y d es: " << sumas2(c, d) << endl;
    std::cout << "Hello world!" << endl;
    std::cout << "Presione ENTER para salir...";
    std::cin.ignore();
    std::cin.get();


    return 0;
}

// Implementación de funciones
int sumas(int x, int y) {
    return x + y;
}

double sumas2(double x, double y)
{
    return x + y;
}




