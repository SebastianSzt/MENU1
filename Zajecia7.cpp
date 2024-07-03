#include <iostream>
#include <vector>

using namespace std;

double Lagrange(vector<double> x, vector<double> y, double x0, int n)
{
    double result = 0;
    for (int i = 0; i < n; i++) 
    {
        double term = y[i];
        for (int j = 0; j < n; j++) 
        {
            if (j != i)
                term = term * (x0 - x[j]) / double(x[i] - x[j]);
        }
        result += term;
    }
    return result;
}

int main()
{
	//Mamy pewna tajemnicza funkcje Nie znamy jej wzoru ale znamy jej wartosci w kilku punktach (wezlach):
	//xw = {1.0, 2.0, 3.0, 5.0, 6.0, 8.0}
	//yw = {1.02, 1.073, 1.144, 1.248, 1.231, 0.97}
	//chcemy przyblizyc wartosci tajemnicznej funkcji za pomoca wielomianow Lagrange'a w punkcie x = 4.0
	//Jakie beda roznice w wyznaczonym y jezeli zastosujemy kolejno 1,2,3,4,5,6 wezlow?

    vector<double> xw = {1.0, 2.0, 3.0, 5.0, 6.0, 8.0};
    vector<double> yw = {1.02, 1.073, 1.144, 1.248, 1.231, 0.97};
    double x0 = 4.0;

    for (int i = 1; i <= 6; i++) 
    {
        double y0 = Lagrange(xw, yw, x0, i);
        cout << "Dla " << i << " wezlow: " << y0 << endl;
    }
}