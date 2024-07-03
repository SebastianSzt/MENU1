#include <iostream>
#include <vector>
#include <fstream>
#include "gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>

// Function to calculate dx/dt
double f(double t, double x, double v) {
    return v;
}

// Function to calculate dv/dt
double g(double t, double x, double v, double B, double w) {
    return -2 * B * v - w * w * x;
}

// Euler's method
void euler(double x0, double v0, double B, double w, double dt, int n) {
    double t = 0.0;
    double x = x0;
    double v = v0;

    std::ofstream eulerData("eulerData.txt");

    for (int i = 0; i < n; i++) {
        eulerData << t << " " << x << "\n";

        double dx = dt * f(t, x, v);
        double dv = dt * g(t, x, v, B, w);

        x += dx;
        v += dv;
        t += dt;
    }

    eulerData.close();
}

// Runge-Kutta 4 method
void rungeKutta(double x0, double v0, double B, double w, double dt, int n) {
    double t = 0.0;
    double x = x0;
    double v = v0;

    std::ofstream rkData("rkData.txt");

    for (int i = 0; i < n; i++) {
        rkData << t << " " << x << "\n";

        double k1x = dt * f(t, x, v);
        double k1v = dt * g(t, x, v, B, w);

        double k2x = dt * f(t + dt / 2, x + k1x / 2, v + k1v / 2);
        double k2v = dt * g(t + dt / 2, x + k1x / 2, v + k1v / 2, B, w);

        double k3x = dt * f(t + dt / 2, x + k2x / 2, v + k2v / 2);
        double k3v = dt * g(t + dt / 2, x + k2x / 2, v + k2v / 2, B, w);

        double k4x = dt * f(t + dt, x + k3x, v + k3v);
        double k4v = dt * g(t + dt, x + k3x, v + k3v, B, w);

        x += (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
        v += (k1v + 2 * k2v + 2 * k3v + k4v) / 6;
        t += dt;
    }

    rkData.close();
}

int main() {
    double B = 1.8;
    double w = 10;
    double x0 = 1;
    double v0 = 0;
    double dt = 0.01;
    int n = 1000; // number of steps

    euler(x0, v0, B, w, dt, n);
    rungeKutta(x0, v0, B, w, dt, n);

    // Plot data using gnuplot
    Gnuplot gp;
    gp << "set xlabel 'Time'\n";
    gp << "set ylabel 'x'\n";
    gp << "plot 'eulerData.txt' with lines title 'Euler', 'rkData.txt' with lines title 'Runge-Kutta'\n";
    gp << "set term png\n";
    gp << "set output 'plot.png'\n";
    gp << "replot\n";

    return 0;
}