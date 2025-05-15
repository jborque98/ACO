#include <iostream>     // For console output
#include <fstream>      // For file output
#include <complex>      // For handling complex numbers
#include <omp.h>        // For parallel processing with OpenMP

// Define the resolution and the max number of iterations
const int NPOINTS_PER_DIMENSION = 2000;
const int NMAXITERATIONS = 500;

// Define the limit for the intervals
const double CMIN_REAL = -2.0;
const double CMAX_REAL = 0.5;
const double CMIN_IMAG = -1.1;
const double CMAX_IMAG = 1.1;

// This function determines if a complex number c belongs to the Mandelbrot set or not.
// It returns true if the sequence zn+1 = zn^2 + c does NOT diverge after NMAXITERATIONS, therefore we can select the points for the plot.
bool not_diverge(std::complex<double> c) {
    std::complex<double> z = 0;
    for (int i = 0; i < NMAXITERATIONS; i++) {
        z = z * z + c;
        if (std::abs(z) > 2.0) {
            return false; // Diverged
        }
    }
    return true; // Did not diverge
}

// This function writes to a file the points that did not diverge, so we will be able to plot them.
// It receives the real and imaginary coordinate arrays and the divergence flag array.
void write_mandelbrot(double *c_real, double *c_imag, int *notdiverge) {
    std::ofstream fout("mandelbrot.txt"); // Output file
    int N = NPOINTS_PER_DIMENSION;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (notdiverge[i + j * N]) { // 1D index for 2D access
                fout << c_real[i] << " " << c_imag[j] << "\n";
            }
        }
    }
    fout.close();
}

int main() {
    int N = NPOINTS_PER_DIMENSION;

    // Dynamically allocate memory for the real and imaginary axis and the divergence mask
    double* c_real = new double[N];
    double* c_imag = new double[N];
    int* notdiverged = new int[N * N];

    // Fill in the real and imaginary coordinate arrays
    for (int i = 0; i < N; ++i) {
        c_real[i] = CMIN_REAL + i * (CMAX_REAL - CMIN_REAL) / (N - 1);
        c_imag[i] = CMIN_IMAG + i * (CMAX_IMAG - CMIN_IMAG) / (N - 1);
    }

    // Check divergence for each point in parallel using OpenMP 
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::complex<double> c(c_real[i], c_imag[j]);
            notdiverged[i + j * N] = not_diverge(c);
        }
    }

    // Save the result to file
    write_mandelbrot(c_real, c_imag, notdiverged);

    delete[] c_real;
    delete[] c_imag;
    delete[] notdiverged;

    std::cout << "File 'mandelbrot.txt' has been created.\n";
    return 0;
}
