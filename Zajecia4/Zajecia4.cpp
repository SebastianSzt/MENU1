#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double f(double x)
{
    // f(x) = x - x^(1/3) - 2
	if (x < 0)
		return x + pow(-x, 1.0 / 3.0) - 2.0;
	else
		return x - pow(x, 1.0 / 3.0) - 2.0;
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

double sieczne(double x1, double x2, double epsilon)
{
	double f1 = f(x1);
	double f2 = f(x2);

	double x0;
	double f0;

	int rozmiar = 10;
	double** tablica = new double* [2];
	tablica[0] = new double[rozmiar];
	tablica[1] = new double[rozmiar];

	int iteracje = 0;
	while ((fabs(x1 - x2) > epsilon))
	{
		if (fabs(f1 - f2) < epsilon)
			throw invalid_argument("Zle punkty startowe\n");

		x0 = x1 - f1 * (x1 - x2) / (f1 - f2);
		f0 = f(x0);

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

		tablica[0][iteracje] = x0;
		tablica[1][iteracje] = f0;

		if (fabs(f0) < epsilon) 
			break;

		x2 = x1; f2 = f1;
		x1 = x0; f1 = f0;
		
		iteracje++;
	}

	zapisDoPliku(tablica, iteracje + 1, "sieczne.txt");

	delete[] tablica[0];
	delete[] tablica[1];
	delete[] tablica;

	return x0;
}

int main()
{
	double x1 = -5, x2 = 5, epsilon = 0.00001;

	double pierwiastek;

	try
	{
		pierwiastek = sieczne(x1, x2, epsilon);
		cout << "Za pomoca metody siecznych znaleziono pierwiastek w x = " << pierwiastek << endl;
	}
	catch (invalid_argument& e)
	{
		cerr << e.what();
	}
}