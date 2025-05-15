#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <omp.h> 


const double GAMMA = 7.0/5.0;
const int NPART = 2000; 
const int NSPH  = 25; 
const double T_END  = 0.05; 
const int NSTEPS    = 500; 
const int OUT_EVERY = 100;   
const double MASS   = 1.0;   

struct Particle {
    double x;
    double v;
    double rho;
    double e;
    double h;
    double P;

    double v_coeff;
    double rho_coeff;
    double e_coeff;
};

inline double W(double r, double h) {
    double q = fabs(r) / h;
    double sigma = 2.0 / (3.0 * h);
    if (q <= 1.0)      return sigma * (1 - 1.5*q*q + 0.75*q*q*q);
    else if (q <= 2.0) return sigma * 0.25 * pow(2 - q, 3);
    else               return 0.0;
}

inline double dWdr(double r, double h) {
    double q = fabs(r) / h;
    double sigma = 2.0 / (3.0 * h);
    double sign = (r >= 0 ? 1.0 : -1.0);
    if (q <= 1.0)      return sigma * sign * (-3*q + 2.25*q*q) / h;
    else if (q <= 2.0) return sigma * sign * (-0.75*pow(2-q,2)) / h;
    else               return 0.0;
}

void setSmoothingLengths(std::vector<Particle>& P) {
    size_t N = P.size();
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
        std::vector<double> dist(N);
        for (size_t j = 0; j < N; ++j) {
            dist[j] = fabs(P[i].x - P[j].x);
        }
        std::nth_element(dist.begin(), dist.begin() + NSPH, dist.end());
        P[i].h = dist[NSPH];
    }
}

void computeCoefficients(std::vector<Particle>& P) {
    size_t N = P.size();

#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
        P[i].P = (GAMMA - 1.0) * P[i].rho * P[i].e;
        P[i].v_coeff = P[i].rho_coeff = P[i].e_coeff = 0.0;
    }

#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
        double xi = P[i].x;
        double vi = P[i].v;
        double rhoi = P[i].rho;
        double Pi = P[i].P;
        double hi = P[i].h;
        double v_coef = 0.0;
        double rho_coef = 0.0;
        double e_coef = 0.0;
        for (size_t j = 0; j < N; ++j) {
            if (i == j) continue;
            double dx = xi - P[j].x;
            double hmax = std::max(hi, P[j].h);
            if (fabs(dx) > 2*hmax) continue;
            double dw = dWdr(dx, hmax);
            double fac = MASS * (Pi/(rhoi*rhoi)
                              + P[j].P/(P[j].rho*P[j].rho));
            rho_coef += MASS * (vi - P[j].v) * dw;
            v_coef   -= fac * dw;
            e_coef   += 0.5 * fac * (vi - P[j].v) * dw;
        }
        P[i].rho_coeff = rho_coef;
        P[i].v_coeff   = v_coef;
        P[i].e_coeff   = e_coef;
    }
}

void integrate(std::vector<Particle>& P, double dt) {
    size_t N = P.size();
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
        P[i].x   += P[i].v * dt;
        P[i].v   += P[i].v_coeff * dt;
        P[i].rho += P[i].rho_coeff * dt;
        P[i].e   += P[i].e_coeff * dt;
    }
}

int main() {
    std::vector<Particle> P(NPART);
    double dx = 1.0/(NPART - 1);

#pragma omp parallel for
    for (int i = 0; i < NPART; ++i) {
        P[i].x   = i * dx;
        P[i].v   = 0.0;
        P[i].rho = MASS / dx;
        P[i].e   = (i == NPART/2) ? 1.0 : 1e-5;
        P[i].h   = 2 * dx;
    }
    double dt = T_END / NSTEPS;

    for (int step = 0; step <= NSTEPS; ++step) {
        setSmoothingLengths(P);
        computeCoefficients(P);
        integrate(P, dt);

        if (step % OUT_EVERY == 0) {
            char filename[64];
            std::sprintf(filename, "perfil_step%04d.dat", step);
            std::ofstream out(filename);
            out << std::fixed << std::setprecision(6);
            for (auto& p : P) {
                out << p.x << " " << p.rho << "\n";
            }
            out.close();
            std::cout << "Escrito " << filename << "\n";
        }
    }
    return 0;
}