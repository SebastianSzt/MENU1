#include <iostream>
#include <cmath>
#include <iomanip>

#define M_PI 3.14159265358979323846

using namespace std;

double F(double x)
{
    //Funkcja f(x) = xsin(x)
    return x * sin(x);
}

void DwupunktowaWPrzod(double x, double h)
{
    double fx = F(x);
    double fx_plus_h = F(x + h);
    double wynik = (fx_plus_h - fx) / h;
    cout << "f'(x) dla h=" << fixed << setprecision(7) << h << "    \t" << "Wynik=" << fixed << setprecision(20) << wynik << endl;
}

void DwupunktowaWTyl(double x, double h)
{
    double fx = F(x);
    double fx_minus_h = F(x - h);
    double wynik = (fx - fx_minus_h) / h;
    cout << "f'(x) dla h=" << fixed << setprecision(7) << h << "    \t" << "Wynik=" << fixed << setprecision(20) << wynik << endl;
}

void DwupunktowaCentralna(double x, double h)
{
    double fx = F(x);
    double fx_plus_h = F(x + h);
    double fx_minus_h = F(x - h);
    double wynik = (fx_plus_h - fx_minus_h) / 2 * h;
    cout << "f'(x) dla h=" << fixed << setprecision(7) << h << "    \t" << "Wynik=" << fixed << setprecision(20) << wynik << endl;
}

void RozniceCentralne(double x, double h)
{
    double fx = F(x);
    double fx_plus_h = F(x + h);
    double fx_minus_h = F(x - h);
    double wynik = (fx_plus_h - (2 * fx) + fx_minus_h) / pow(h, 2);
    cout << "f''(x) dla h=" << fixed << setprecision(7) << h << "    \t" << "Wynik=" << fixed << setprecision(20) << wynik << endl;
}

void TrzypunktowaWPrzod(double x, double h)
{
    double fx = F(x);
    double fx_plus_h = F(x + h);
    double fx_plus_2h = F(x + 2 * h);
    double wynik = (-3 * fx + 4 * fx_plus_h - fx_plus_2h) / (2 * h);
    cout << "f'(x) dla h=" << fixed << setprecision(7) << h << "    \t" << "Wynik=" << fixed << setprecision(20) << wynik << endl;
}

void TrzypunktowaWTyl(double x, double h)
{
    double fx_minus_2h = F(x - 2 * h);
    double fx_minus_h = F(x - h);
    double fx = F(x);
    double wynik = (3 * fx - 4 * fx_minus_h + fx_minus_2h) / (2 * h);
    cout << "f'(x) dla h=" << fixed << setprecision(7) << h << "    \t" << "Wynik=" << fixed << setprecision(20) << wynik << endl;
}

void Piatopunktowa(double x, double h)
{
    double fx_minus_2h = F(x - 2 * h);
    double fx_minus_h = F(x - h);
    double fx_plus_h = F(x + h);
    double fx_plus_2h = F(x + 2 * h);
    double wynik = (fx_minus_2h - 8 * fx_minus_h + 8 * fx_plus_h - fx_plus_2h) / (12 * h);
    cout << "f'(x) dla h=" << fixed << setprecision(7) << h << "    \t" << "Wynik=" << fixed << setprecision(20) << wynik << endl;
}

int main()
{
    // Policzyć pochodną funkcji f(x) = xsin(x) w punkcie x = pi korzystając z metody dwupunktowej "w przód" i "w tył"
    // o ile roznia sie wyniki jezeli przyjmiemy h = 1, 0.1, 0.001, 0.0001, 0.00001, ...?
    //f'(x) = (f(x+h) - f(x))/h

    double x = M_PI;

    cout << endl << "####################################" << endl << "Wzor dwupunktowy w przod" << endl << "####################################" << endl << endl;
    DwupunktowaWPrzod(x, 1);
    DwupunktowaWPrzod(x, 0.1);
    DwupunktowaWPrzod(x, 0.01);
    DwupunktowaWPrzod(x, 0.001);
    DwupunktowaWPrzod(x, 0.0001);
    DwupunktowaWPrzod(x, 0.00001);
    DwupunktowaWPrzod(x, 0.000001);
    DwupunktowaWPrzod(x, 0.0000001);

    cout << endl << "####################################" << endl << "Wzor dwupunktowy w tyl" << endl << "####################################" << endl << endl;

    DwupunktowaWTyl(x, 1);
    DwupunktowaWTyl(x, 0.1);
    DwupunktowaWTyl(x, 0.01);
    DwupunktowaWTyl(x, 0.001);
    DwupunktowaWTyl(x, 0.0001);
    DwupunktowaWTyl(x, 0.00001);
    DwupunktowaWTyl(x, 0.000001);
    DwupunktowaWTyl(x, 0.0000001);

    cout << endl << "####################################" << endl << "Wzor dwupunktowy centralny" << endl << "####################################" << endl << endl;
    DwupunktowaCentralna(x, 1);
    DwupunktowaCentralna(x, 0.1);
    DwupunktowaCentralna(x, 0.01);
    DwupunktowaCentralna(x, 0.001);
    DwupunktowaCentralna(x, 0.0001);
    DwupunktowaCentralna(x, 0.00001);
    DwupunktowaCentralna(x, 0.000001);
    DwupunktowaCentralna(x, 0.0000001);

    cout << endl << "####################################" << endl << "Wzor roznice centralne" << endl << "####################################" << endl << endl;
    RozniceCentralne(x, 1);
    RozniceCentralne(x, 0.1);
    RozniceCentralne(x, 0.01);
    RozniceCentralne(x, 0.001);
    RozniceCentralne(x, 0.0001);
    RozniceCentralne(x, 0.00001);
    RozniceCentralne(x, 0.000001);
    RozniceCentralne(x, 0.0000001);

    //znalezc trzy funkcje ciekawe do liczenia pochodnej patrzec na dokladnosc

    cout << endl << "####################################" << endl << "Wzor trzypunktowy w przod" << endl << "####################################" << endl << endl;
    TrzypunktowaWPrzod(x, 1);
    TrzypunktowaWPrzod(x, 0.1);
    TrzypunktowaWPrzod(x, 0.01);
    TrzypunktowaWPrzod(x, 0.001);
    TrzypunktowaWPrzod(x, 0.0001);
    TrzypunktowaWPrzod(x, 0.00001);
    TrzypunktowaWPrzod(x, 0.000001);
    TrzypunktowaWPrzod(x, 0.0000001);

    cout << endl << "####################################" << endl << "Wzor trzypunktowy w tyl" << endl << "####################################" << endl << endl;
    TrzypunktowaWTyl(x, 1);
    TrzypunktowaWTyl(x, 0.1);
    TrzypunktowaWTyl(x, 0.01);
    TrzypunktowaWTyl(x, 0.001);
    TrzypunktowaWTyl(x, 0.0001);
    TrzypunktowaWTyl(x, 0.00001);
    TrzypunktowaWTyl(x, 0.000001);
    TrzypunktowaWTyl(x, 0.0000001);

    cout << endl << "####################################" << endl << "Wzor pieciopunktowy" << endl << "####################################" << endl << endl;
    Piatopunktowa(x, 1);
    Piatopunktowa(x, 0.1);
    Piatopunktowa(x, 0.01);
    Piatopunktowa(x, 0.001);
    Piatopunktowa(x, 0.0001);
    Piatopunktowa(x, 0.00001);
    Piatopunktowa(x, 0.000001);
    Piatopunktowa(x, 0.0000001);
}
