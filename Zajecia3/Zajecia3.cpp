#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double f(double x)
{
    // f(x) = x - x^(1/3) - 2
    return x - pow(x, 1.0 / 3.0) - 2.0;
	//return x * x * x - 2 * x * x + 4;
}

double df(double x)
{
	// Pochodna funkcji: f'(x) = 1 - 1/3x^(-2/3)
	return 1.0 - (1.0 / 3.0) * pow(x, -2.0 / 3.0);
	//return 3 * x * x - 4 * x;
}

void zapisDoPliku(double** tablica, int rozmiar, const char* nazwaPliku)
{
	ofstream plik(nazwaPliku);
	if (plik.is_open()) 
	{
		plik << "x\tf(x)\n";
		for (int i = 0; i < rozmiar; i++) 
		{
			plik << tablica[0][i] << '\t' << tablica[1][i] << '\n';
		}
		plik.close();
	}
	else 
	{
		std::cout << "Błąd: Nie można otworzyć pliku." << std::endl;
	}
}

double bisekcja(double a, double b, double epsilon)
{
	if (f(a) == 0.0)	return a;

	if (f(b) == 0.0)	return b;

	int rozmiar = 10;
	double** tablica = new double* [2];
	tablica[0] = new double[rozmiar];
	tablica[1] = new double[rozmiar];

	int iteracje = 0;
	while ((b - a) / 2.0 > epsilon)
	{
		if (iteracje >= rozmiar) 
		{
			rozmiar++;

			double** nowa_tablica = new double* [2];
			nowa_tablica[0] = new double[rozmiar];
			nowa_tablica[1] = new double[rozmiar];

			for (int i = 0; i < iteracje; i++) 
			{
				nowa_tablica[0][i] = tablica[0][i];
				nowa_tablica[1][i] = tablica[1][i];
			}

			delete[] tablica[0];
			delete[] tablica[1];
			delete[] tablica;

			tablica = nowa_tablica;
		}

		double srodek = (a + b) / 2.0;
		double fsrodek = f(srodek);

		tablica[0][iteracje] = srodek;
		tablica[1][iteracje] = f(srodek);

		if (fsrodek == 0.0)
		{
			zapisDoPliku(tablica, iteracje + 1, "bisekcja.txt");
			return srodek;
		}
			
		if (f(a) * fsrodek < 0)
			b = srodek;
		else
			a = srodek;

		iteracje++;
	}

	if (iteracje >= rozmiar)
	{
		rozmiar++;

		double** nowa_tablica = new double* [2];
		nowa_tablica[0] = new double[rozmiar];
		nowa_tablica[1] = new double[rozmiar];

		for (int i = 0; i < iteracje; i++)
		{
			nowa_tablica[0][i] = tablica[0][i];
			nowa_tablica[1][i] = tablica[1][i];
		}

		delete[] tablica[0];
		delete[] tablica[1];
		delete[] tablica;

		tablica = nowa_tablica;
	}

	double srodek = (a + b) / 2.0;
	double fsrodek = f(srodek);

	tablica[0][iteracje] = srodek;
	tablica[1][iteracje] = f(srodek);

	zapisDoPliku(tablica, iteracje + 1, "bisekcja.txt");

	return srodek;
}

double newtonRaphson(double x0, double epsilon)
{
	double x = x0;

	int rozmiar = 10;
	double** tablica = new double* [2];
	tablica[0] = new double[rozmiar];
	tablica[1] = new double[rozmiar];

	int iteracje = 0;
	tablica[0][iteracje] = x;
	tablica[1][iteracje] = f(x);

	iteracje++;
	while (fabs(tablica[1][iteracje]) > epsilon) 
	{
		if (fabs(df(x)) < epsilon)
		{
			cout << "Metoda Newtona-Raphsona nie zbiega. Pochodna bliska zeru." << endl;

			zapisDoPliku(tablica, iteracje, "newtonRaphson.txt");

			delete[] tablica[0];
			delete[] tablica[1];
			delete[] tablica;

			return 0;
		}

		if (iteracje >= rozmiar)
		{
			rozmiar++;

			double** nowa_tablica = new double* [2];
			nowa_tablica[0] = new double[rozmiar];
			nowa_tablica[1] = new double[rozmiar];

			for (int i = 0; i < iteracje; i++) 
			{
				nowa_tablica[0][i] = tablica[0][i];
				nowa_tablica[1][i] = tablica[1][i];
			}

			delete[] tablica[0];
			delete[] tablica[1];
			delete[] tablica;

			tablica = nowa_tablica;
		}

		x = x - f(x) / df(x);

		tablica[0][iteracje] = x;
		tablica[1][iteracje] = f(x);
	}

	zapisDoPliku(tablica, iteracje + 1, "newtonRaphson.txt");

	delete[] tablica[0];
	delete[] tablica[1];
	delete[] tablica;

	return x;
}


int main()
{
	double a = -10, b = 10, epsilon = 0.00001;

	double pierwiastek = bisekcja(a, b, epsilon);

	if (pierwiastek != 0)
		cout << "Za pomoca metody bisekcji znaleziono pierwiastek w x = " << pierwiastek << endl;

	double x0 = 1.0;

	pierwiastek = newtonRaphson(x0, epsilon);

	if (pierwiastek != 0)
		cout << "Za pomoca metody Newtona-Raphsona znaleziono pierwiastek w x = " << pierwiastek << endl;
}