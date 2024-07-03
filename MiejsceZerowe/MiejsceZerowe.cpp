#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double F(double x)
{
	// f(x) = x - x^(1/3) - 2
	return x - cbrt(x) - 2.0;
}

double DF(double x)
{
	// Pochodna funkcji: f'(x) = 1 - 1/3x^(-2/3)
	return 1.0 - (1.0 / 3.0) * pow(x, -2.0 / 3.0);
}

void ZapisDoPliku(double** tablica, int rozmiarTablicy, const char* nazwaPliku)
{
	ofstream plik(nazwaPliku);
	if (plik.is_open())
	{
		plik << "x\tf(x)\n";
		for (int i = 0; i < rozmiarTablicy; i++)
			plik << tablica[0][i] << '\t' << tablica[1][i] << '\n';

		plik.close();
	}
	else
		throw runtime_error("Blad: Nie mozna otworzyc pliku.");

	delete[] tablica[0];
	delete[] tablica[1];
	delete[] tablica;
}

void PoszerzTablice(double**& tablica, int& rozmiarTablicy)
{
	rozmiarTablicy++;

	double** nowa_tablica = new double* [2];
	nowa_tablica[0] = new double[rozmiarTablicy];
	nowa_tablica[1] = new double[rozmiarTablicy];

	for (int i = 0; i < rozmiarTablicy - 1; i++)
	{
		nowa_tablica[0][i] = tablica[0][i];
		nowa_tablica[1][i] = tablica[1][i];
	}

	delete[] tablica[0];
	delete[] tablica[1];
	delete[] tablica;

	tablica = nowa_tablica;
}

double Bisekcja(double a, double b, double epsilon, int rozmiarTablicy)
{
	if (rozmiarTablicy < 1)
		throw invalid_argument("Rozmiar tablicy musi byc wiekszy od zera.");

	double fa = F(a);
	double fb = F(b);

	if (fa == 0.0) return a;
	if (fb == 0.0) return b;

	if (fa * fb > 0)
	{
		throw invalid_argument("Brak zmiany znaku funkcji w przedziale poczatkowym.");
	}

	double** tablica = new double* [2];
	tablica[0] = new double[rozmiarTablicy];
	tablica[1] = new double[rozmiarTablicy];

	double srodek;
	double fsrodek;
	int iteracja = 0;

	do
	{
		srodek = (a + b) / 2.0;
		fsrodek = F(srodek);

		if (iteracja >= rozmiarTablicy)
			PoszerzTablice(tablica, rozmiarTablicy);

		tablica[0][iteracja] = srodek;
		tablica[1][iteracja] = F(srodek);

		if (fsrodek == 0.0)
		{
			ZapisDoPliku(tablica, iteracja, "bisekcja.txt");
			return srodek;
		}
		else if (F(a) * fsrodek < 0)
			b = srodek;
		else
			a = srodek;

		iteracja++;
	} while (fabs(b - a) > epsilon && iteracja < 100);

	ZapisDoPliku(tablica, iteracja, "bisekcja.txt");

	return srodek;
}

double NewtonRaphson(double x0, double epsilon, int rozmiarTablicy)
{
	double** tablica = new double* [2];
	tablica[0] = new double[rozmiarTablicy];
	tablica[1] = new double[rozmiarTablicy];

	double x1;
	double fx;
	double fxprime;
	int iteracja = 0;

	do 
	{
		fx = F(x0);
		fxprime = DF(x0);

		if (fabs(fxprime) < epsilon)
			throw runtime_error("Metoda Newtona-Raphsona nie zbiega. Pochodna bliska zeru.");

		x1 = x0 - fx / fxprime;

		if (iteracja >= rozmiarTablicy)
			PoszerzTablice(tablica, rozmiarTablicy);

		tablica[0][iteracja] = x1;
		tablica[1][iteracja] = F(x1);

		if (fabs(fx) < epsilon) 
		{
			ZapisDoPliku(tablica, iteracja, "newtonRaphson.txt");
			return x1;
		}

		x0 = x1;

		iteracja++;
	} while (iteracja < 100);

	if (iteracja >= rozmiarTablicy)
		PoszerzTablice(tablica, rozmiarTablicy);

	tablica[0][iteracja] = x0;
	tablica[1][iteracja] = F(x0);

	ZapisDoPliku(tablica, iteracja + 1, "newtonRaphson.txt");

	return x0;
}

double Sieczne(double x0, double x1, double epsilon, int rozmiarTablicy)
{
	double** tablica = new double* [2];
	tablica[0] = new double[rozmiarTablicy];
	tablica[1] = new double[rozmiarTablicy];

	double fx0;
	double fx1;
	double x2;
	int iteracja = 0;

	do 
	{
		fx0 = F(x0);
		fx1 = F(x1);
		
		if (fabs(fx1 - fx0) < epsilon) 
			throw runtime_error("Blad: Dzielenie przez (f(x1) - f(x0)) bliskie zeru. Metoda Siecznych nie moze byc zastosowana.");

		x2 = x1 - fx1 * ((x1 - x0) / (fx1 - fx0));
		
		if (iteracja >= rozmiarTablicy)
			PoszerzTablice(tablica, rozmiarTablicy);

		tablica[0][iteracja] = x2;
		tablica[1][iteracja] = F(x2);

		if (fabs(fx1) < epsilon) 
		{
			ZapisDoPliku(tablica, iteracja, "sieczne.txt");
			return x2;
		}

		x0 = x1;
		x1 = x2;

		iteracja++;
	} while (iteracja < 100);

	if (iteracja >= rozmiarTablicy)
		PoszerzTablice(tablica, rozmiarTablicy);

	tablica[0][iteracja] = x1;
	tablica[1][iteracja] = F(x1);

	ZapisDoPliku(tablica, iteracja + 1, "sieczne.txt");

	return x1;
}

int main()
{
	double epsilon = 0.00001;
	int rozmiarTablicy = 10;
	double miejsceZerowe;

	try
	{
		miejsceZerowe = Bisekcja(-10, 10, epsilon, rozmiarTablicy);
		cout << "Miejsce zerowe wyznaczone za pomoca metody bisekcji: " << miejsceZerowe << endl;
		miejsceZerowe = NewtonRaphson(1.0, epsilon, rozmiarTablicy);
		cout << "Miejsce zerowe wyznaczone za pomoca metody Newtona-Raphsona: " << miejsceZerowe << endl;
		miejsceZerowe = Sieczne(-5, 5, epsilon, rozmiarTablicy);
		cout << "Miejsce zerowe wyznaczone za pomoca metody siecznych: " << miejsceZerowe << endl;
	}
	catch (const exception& e)
	{
		cerr << "Wyjatek: " << e.what() << endl;
	}
}
