#include <iostream>
#include <iomanip>
#include <time.h>

#define M_PI 3.14159265358979323846

using namespace std;

double F(double x)
{
    //Funkcja f(x) = sin(x)
    return sin(x);
}

double MetodaProstokatow(double a, double b, int n)
{
    double calka = 0.0;
    double x = (b - a) / n;

    for (int i = 1; i <= n; i++)
    {
        double h = a + (i * x);
        calka += F(h);
    }

    calka *= x;

    return calka;
}

double MetodaTrapezow(double a, double b, int n)
{
    double calka = 0.0;
    double x = (b - a) / n;

    for (int i = 0; i < n; i++)
    {
        double h1 = a + (i * x);
        double h2 = a + ((i + 1) * x);
        calka += (F(h1) + F(h2)) / 2;
    }

    calka = calka * x;

    return calka;
}

double MetodaSimpsona(double a, double b, int n)
{
    double x = (b - a) / n;

    double pos = 0.0, sumaX = 0.0, sumaT = 0.0, calka = 0.0;

    for (int i = 1; i <= n; i++)
    {
        pos = a + (i * x);
        if (i < n) sumaX += F(pos);
        sumaT += F(pos - (x / 2));
    }

    calka = x / 6 * (F(a) + F(b) + 2 * sumaX + 4 * sumaT);

    return calka;
}

double MetodaMonteCarlo1(double a, double b, int n)
{
    double calka = 0.0;
    double x = b - a;

    srand(time(NULL));

    double p_x, p_y;

    double k = 0;
    for (int i = 0; i < n; i++)
    {
        p_x = (double)rand() / (double)(RAND_MAX + 1) * x;
        p_y = (double)rand() / (double)(RAND_MAX + 1) * 2 - 1;

        if (abs(p_y) < abs(F(a + p_x)))
            k++;
    }

    calka = k / n * 2 * x;

    return calka;
}

double MetodaMonteCarlo2(double a, double b, int n)
{
    double calka = 0.0;
    double x = b - a;

    srand(time(NULL));

    for (int i = 1; i <= n; i++)
        calka += F(a + ((double)rand() / (double)(RAND_MAX + 1) * x));
    calka = x * calka / n;

    return calka;
}

int main()
{
    double a = 0.0;
    double b = M_PI;
    int n = 1000;

    cout << "Zakres: od " << a << " do " << b << endl;
    cout << "Liczba przedzialow: " << n << endl << endl;

    double wynik = MetodaProstokatow(a, b, n);
    cout << "Calka z sin(x) za pomoca metody prostokatow wynosi: " << fixed << setprecision(10) << wynik << endl;

    wynik = MetodaTrapezow(a, b, n);
    cout << "Calka z sin(x) za pomoca metody trapezow wynosi: " << fixed << setprecision(10) << wynik << endl;

    wynik = MetodaSimpsona(a, b, n);
    cout << "Calka z sin(x) za pomoca metody simpsona wynosi: " << fixed << setprecision(10) << wynik << endl;

    wynik = MetodaMonteCarlo1(a, b, n);
    cout << "Calka z sin(x) za pomoca metody monte carlo 1 wynosi: " << fixed << setprecision(10) << wynik << endl;

    wynik = MetodaMonteCarlo2(a, b, n);
    cout << "Calka z sin(x) za pomoca metody monte carlo 2 wynosi: " << fixed << setprecision(10) << wynik << endl;
}