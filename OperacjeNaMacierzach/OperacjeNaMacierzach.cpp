#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int LiczbaWierszy = 0;
int LiczbaKolumn = 0;

class myError
{
public:
	myError(const string& komunikat) : komunikat_(komunikat) {}

	const char* what() const noexcept
	{
		return komunikat_.c_str();
	}

private:
	string komunikat_;
};

template <typename T>
T** StworzMacierz(int liczbaWierszy, int liczbaKolumn)
{
	T** macierz = new T * [liczbaWierszy];
	for (int i = 0; i < liczbaWierszy; i++)
		macierz[i] = new T[liczbaKolumn];

	return macierz;
}

template <typename T>
T** WczytajZPliku(const char* nazwaPliku)
{
	try
	{
		fstream plik(nazwaPliku);

		if (!plik.is_open())
		{
			throw myError("Nie udalo sie otworzyc pliku.");
		}

		string linia;

		while (getline(plik, linia))
		{
			if (linia.empty())
				continue;

			if (linia.find('=') != string::npos)
			{
				if (linia.find('[') == string::npos || linia.find(']') == string::npos || linia.find(',') == string::npos)
				{
					throw myError("Bledny format definicji macierzy.");
					plik.close();
				}
				string rozmiar = linia.substr(linia.find('[') + 1, linia.find(']') - linia.find('[') - 1);
				istringstream strumien(rozmiar);
				char separator;
				if (!(strumien >> LiczbaWierszy >> separator >> LiczbaKolumn) || separator != ',') {
					throw myError("Bledny format rozmiaru macierzy.");
					plik.close();
				}

				if (LiczbaWierszy == 0 || LiczbaKolumn == 0)
				{
					throw myError("Bledny rozmiar macierzy.");
					plik.close();
				}
			}
		}

		T** macierz = StworzMacierz<T>(LiczbaWierszy, LiczbaKolumn);

		plik.close();
		plik.open(nazwaPliku);

		while (getline(plik, linia))
		{
			if (linia.find('=') != string::npos)
			{
				for (int i = 0; i < LiczbaWierszy; i++)
				{
					getline(plik, linia);

					if (linia.empty())
					{
						throw myError("Niepoprawny zapis.");
						plik.close();
					}

					istringstream strumien(linia);

					for (int j = 0; j < LiczbaKolumn; j++)
					{
						if (!(strumien >> macierz[i][j]))
						{
							throw myError("Bledny format elementow macierzy.");
							plik.close();
						}
					}
				}
			}
		}

		return macierz;
	}
	catch (const myError& e)
	{
		throw myError("Odczyt z pliku: " + string(e.what()));
	}
	catch (...)
	{
		throw exception("Odczyt z pliku");
	}
}

template <typename T>
void ZapisDoPliku(T** macierz, int liczbaWierszy, int liczbaKolumn, const char* nazwaPliku)
{
	try
	{
		ofstream plik(nazwaPliku);

		if (!plik.is_open())
		{
			throw myError("Nie udało się otworzyć pliku do zapisu");
			plik.close();
		}

		plik << "=[" << liczbaWierszy << "," << liczbaKolumn << "]" << endl;

		for (int i = 0; i < liczbaWierszy; i++)
		{
			for (int j = 0; j < liczbaKolumn; j++)
			{
				plik << macierz[i][j] << " ";
			}
			plik << endl;
		}

		plik.close();
	}
	catch (const myError& e)
	{
		throw myError("Zapis do pliku: " + string(e.what()));
	}
	catch (...)
	{
		throw exception("Zapis do pliku");
	}
}

template <typename T>
void WypiszMacierz(T** macierz, int liczbaWierszy, int liczbaKolumn)
{
	for (int i = 0; i < liczbaWierszy; i++)
	{
		for (int j = 0; j < liczbaKolumn; j++)
			cout << fixed << setprecision(2) << macierz[i][j] << "\t";
		cout << endl;
	}
	cout << endl;
}

template <typename T>
T** StworzMacierzZerowa(int liczbaWierszy, int liczbaKolumn)
{
	T** macierz = StworzMacierz<T>(liczbaWierszy, liczbaKolumn);

	//clock_t start = clock();

	for (int i = 0; i < liczbaWierszy; i++)
		memset(macierz[i], 0, liczbaKolumn * sizeof(T));

	//clock_t end = clock();
	//double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	//cout << "--------- " << cpu_time_used << " ---------" << endl;

	return macierz;
}

template <typename T>
T** StworzMacierzJednostkowa(int liczbaWierszy, int liczbaKolumn)
{
	T** macierz = StworzMacierzZerowa<T>(liczbaWierszy, liczbaKolumn);

	int dl;
	if (liczbaWierszy <= liczbaKolumn)
		dl = liczbaWierszy;
	else
		dl = liczbaKolumn;

	for (int i = 0; i < dl; i++)
		macierz[i][i] = 1;

	return macierz;
}

template <typename T>
T** MinorZMacierzy(T** macierz, int liczbaWierszy, int liczbaKolumn, int wierszUsuwany, int kolumnaUsuwana)
{
	try
	{
		if (wierszUsuwany < 0 || wierszUsuwany >= liczbaWierszy)
			throw myError("Wiersz do usuniecia jest spoza zakresu");

		if (kolumnaUsuwana < 0 || kolumnaUsuwana >= liczbaKolumn)
			throw myError("Kolumna do usuniecia jest spoza zakresu");

		T** minor = StworzMacierz<T>(liczbaWierszy - 1, liczbaKolumn - 1);

		int rowIndex = 0;
		for (int i = 0; i < liczbaWierszy; ++i)
		{
			if (i == wierszUsuwany)
				continue;

			int colIndex = 0;
			for (int j = 0; j < liczbaKolumn; ++j)
			{
				if (j == kolumnaUsuwana)
					continue;

				minor[rowIndex][colIndex] = macierz[i][j];
				colIndex++;
			}

			rowIndex++;
		}

		return minor;
	}
	catch (const myError& e)
	{
		throw myError("Wyznaczanie minora z macierzy: " + string(e.what()));
	}
	catch (...)
	{
		throw exception("Wyznaczanie minora z macierzy");
	}
}

template <typename T>
T** SumaMacierzy(T** macierzA, T** macierzB, int liczbaWierszy, int liczbaKolumn)
{
	try
	{
		T** suma = StworzMacierz<T>(liczbaWierszy, liczbaKolumn);

		for (int i = 0; i < liczbaWierszy; i++)
		{
			for (int j = 0; j < liczbaKolumn; j++)
			{
				suma[i][j] = macierzA[i][j] + macierzB[i][j];
			}
		}

		return suma;
	}
	catch (...)
	{
		throw exception("Sumowanie macierzy");
	}
}

template <typename T>
T** IloczynMacierzy(T** macierzA, int liczbaWierszyMacierzyA, int liczbaKolumnMacierzyA, T** macierzB, int liczbaWierszyMacierzyB, int liczbaKolumnMacierzyB)
{
	try
	{
		if (liczbaKolumnMacierzyA != liczbaWierszyMacierzyB)
			throw myError("Liczba wierszy i kolumn rozni sie");

		T** iloczyn = StworzMacierz<T>(liczbaWierszyMacierzyA, liczbaKolumnMacierzyB);

		for (int i = 0; i < liczbaWierszyMacierzyA; i++)
		{
			for (int j = 0; j < liczbaKolumnMacierzyB; j++)
			{
				iloczyn[i][j] = 0;
				for (int k = 0; k < liczbaWierszyMacierzyA; ++k)
					iloczyn[i][j] += macierzA[i][k] * macierzB[k][j];
			}
		}

		return iloczyn;
	}
	catch (const myError& e)
	{
		throw myError("Iloczyn macierzy: " + string(e.what()));
	}
	catch (...)
	{
		throw exception("Iloczyn macierzy");
	}
}

template <typename T>
T** MnozenieniePrzezSkalarMacierzy(T** macierz, int liczbaWierszy, int liczbaKolumn, double skalar)
{
	try
	{
		T** macierzSkalar = StworzMacierz<T>(liczbaWierszy, liczbaKolumn);

		for (int i = 0; i < liczbaWierszy; i++)
		{
			for (int j = 0; j < liczbaKolumn; j++)
			{
				macierzSkalar[i][j] = macierz[i][j] * skalar;
			}
		}

		return macierzSkalar;
	}
	catch (...)
	{
		throw exception("Iloczyn macierzy");
	}
}

template <typename T>
T** TransponowanieMacierzy(T** macierz, int liczbaWierszy, int liczbaKolumn)
{
	try
	{
		T** macierzTransponowana = StworzMacierz<T>(liczbaKolumn, liczbaWierszy);

		for (int i = 0; i < liczbaWierszy; i++)
			for (int j = 0; j < liczbaKolumn; j++)
				macierzTransponowana[j][i] = macierz[i][j];

		return macierzTransponowana;
	}
	catch (...)
	{
		throw exception("Iloczyn macierzy");
	}
}

template <typename T>
double WyznacznikMacierzySarrus(T** macierz, int liczbaWierszy, int liczbaKolumn)
{
	try
	{
		if (liczbaWierszy != liczbaKolumn)
			throw myError("Liczba wierszy i kolumn rozni sie");

		if (liczbaWierszy < 1 || liczbaWierszy > 3)
			throw myError("Macierz jest za mala lub za duza");

		double wyznacznik = 0;

		if (liczbaWierszy == 1)
			return macierz[0][0];

		if (liczbaWierszy == 2)
			return macierz[0][0] * macierz[1][1] - macierz[0][1] * macierz[1][0];

		if (liczbaWierszy == 3)
		{
			wyznacznik = macierz[0][0] * macierz[1][1] * macierz[2][2] + macierz[0][1] * macierz[1][2] * macierz[2][0] + macierz[0][2] * macierz[1][0] * macierz[2][1];
			wyznacznik -= macierz[0][2] * macierz[1][1] * macierz[2][0] + macierz[0][1] * macierz[1][0] * macierz[2][2] + macierz[0][0] * macierz[1][2] * macierz[2][1];
			return wyznacznik;
		}
	}
	catch (const myError& e)
	{
		throw myError("Wyznacznik z reguly Sarrusa: " + string(e.what()));
	}
	catch (...)
	{
		throw exception("Wyznacznik z reguly Sarrusa");
	}
}

template <typename T>
double WyznacznikMacierzyLaplace(T** macierz, int liczbaWierszy, int liczbaKolumn)
{
	try
	{
		if (liczbaWierszy != liczbaKolumn)
			throw myError("Liczba wierszy i kolumn rozni sie");

		if (liczbaKolumn < 1)
			throw myError("Macierz jest za mala");

		double wyznacznik = 0;

		if (liczbaWierszy == 1)
			return macierz[0][0];

		for (int i = 0; i < liczbaWierszy; ++i)
		{
			T** minor = MinorZMacierzy<T>(macierz, liczbaWierszy, liczbaKolumn, i, 0);

			int sign = (i % 2 == 0) ? 1 : -1;
			wyznacznik += sign * macierz[i][0] * WyznacznikMacierzySarrus(minor, liczbaWierszy - 1, liczbaKolumn - 1);

			for (int j = 0; j < liczbaWierszy - 1; ++j)
				delete[] minor[j];
			delete[] minor;
		}

		return wyznacznik;
	}
	catch (const myError& e)
	{
		throw myError("Wyznacznik z metody Laplace'a: " + string(e.what()));
	}
	catch (...)
	{
		throw exception("Wyznacznik z metody Laplace'a");
	}
}

template <typename T>
double WyznacznikMacierzyDolittle(T** macierz, int liczbaWierszy, int liczbaKolumn)
{
	try
	{
		if (liczbaWierszy != liczbaKolumn)
			throw myError("Macierz nie jest kwadratowa");

		double** macierzL = StworzMacierzZerowa<double>(liczbaWierszy, liczbaKolumn);
		double** macierzU = StworzMacierzZerowa<double>(liczbaWierszy, liczbaKolumn);

		for (int i = 0; i < liczbaWierszy; i++)
		{
			for (int j = i; j < liczbaKolumn; j++)
			{
				double suma = 0;
				for (int k = 0; k < i; k++)
					suma += (macierzL[i][k] * macierzU[k][j]);
				macierzU[i][j] = (double)macierz[i][j] - suma;
			}

			for (int j = i; j < liczbaWierszy; j++)
			{
				if (i == j)
					macierzL[i][i] = 1;
				else
				{
					double suma = 0;
					for (int k = 0; k < i; k++)
						suma += (macierzL[j][k] * macierzU[k][i]);
					macierzL[j][i] = ((double)macierz[j][i] - suma) / macierzU[i][i];
				}
			}
		}

		cout << "Macierz L macierzy:" << endl;
		WypiszMacierz(macierzL, liczbaWierszy, liczbaKolumn);

		cout << "Macierz U macierzy:" << endl;
		WypiszMacierz(macierzU, liczbaWierszy, liczbaKolumn);

		double wyznacznik = 1;
		for (int i = 0; i < liczbaWierszy; i++)
			wyznacznik *= macierzU[i][i];

		for (int i = 0; i < liczbaWierszy; i++)
		{
			delete[] macierzL[i];
			delete[] macierzU[i];
		}
		delete[] macierzL;
		delete[] macierzU;

		return wyznacznik;
	}
	catch (const myError& e)
	{
		throw myError("Wyznacznik z metody Dolittle: " + string(e.what()));
	}
	catch (...)
	{
		throw exception("Wyznacznik z metody Dolittle");
	}
}

template <typename T>
double WyznacznikMacierzyNormalizacja(T** macierz, int liczbaWierszy, int liczbaKolumn)
{
	try
	{
		if (liczbaWierszy != liczbaKolumn)
			throw myError("Macierz nie jest kwadratowa");

		double** macierzTMP = StworzMacierzZerowa<double>(liczbaWierszy, liczbaKolumn);

		for (int i = 0; i < liczbaWierszy; i++)
			for (int j = 0; j < liczbaKolumn; j++)
				macierzTMP[i][j] = (double)macierz[i][j];

		double dzielnik;

		for (int k = 0; k < liczbaKolumn - 1; k++)
		{
			dzielnik = macierzTMP[k][k];
			if (dzielnik > -0.000000001 && dzielnik < 0.000000001)
				throw myError("Blad w obliczeniach");

			for (int i = k + 1; i < liczbaWierszy; i++)
				macierzTMP[i][k] = macierzTMP[i][k] / dzielnik;

			for (int i = k + 1; i < liczbaWierszy; i++)
				for (int j = k + 1; j < liczbaKolumn; j++)
					macierzTMP[i][j] = macierzTMP[i][j] - macierzTMP[i][k] * macierzTMP[k][j];
		}

		cout << "Macierz L macierzy:" << endl;
		for (int i = 0; i < liczbaWierszy; i++)
		{
			for (int j = 0; j < liczbaKolumn; j++)
			{
				if (i > j)
					cout << fixed << setprecision(2) << macierzTMP[i][j] << "\t";
				else if (i == j)
					cout << fixed << setprecision(2) << 1.0 << "\t";
				else
					cout << fixed << setprecision(2) << 0.0 << "\t";
			}
			cout << endl;
		}
		cout << endl;

		cout << "Macierz U macierzy:" << endl;
		for (int i = 0; i < liczbaWierszy; i++)
		{
			for (int j = 0; j < liczbaKolumn; j++)
			{
				if (i <= j)
					cout << fixed << setprecision(2) << macierzTMP[i][j] << "\t";
				else
					cout << fixed << setprecision(2) << 0.0 << "\t";
			}
			cout << endl;
		}
		cout << endl;

		double wyznacznik = 1;
		for (int i = 0; i < liczbaWierszy; i++)
			wyznacznik *= macierzTMP[i][i];

		for (int i = 0; i < liczbaWierszy; i++)
			delete[] macierzTMP[i];
		delete[] macierzTMP;

		return wyznacznik;
	}
	catch (const myError& e)
	{
		throw myError("Wyznacznik z metody normalizacji: " + string(e.what()));
	}
	catch (...)
	{
		throw exception("Wyznacznik z metody normalizacji");
	}
}

int main()
{
	try
	{
		/*int** macierzA = WczytajZPliku<int>("macierzA.txt");
		int liczbaWierszyMacierzyA = LiczbaWierszy;
		int liczbaKolumnMacierzyA = LiczbaKolumn;
		WypiszMacierz(macierzA, LiczbaWierszy, LiczbaKolumn);

		int** macierzB = WczytajZPliku<int>("macierzB.txt");
		int liczbaWierszyMacierzyB = LiczbaWierszy;
		int liczbaKolumnMacierzyB = LiczbaKolumn;
		WypiszMacierz(macierzB, LiczbaWierszy, LiczbaKolumn);

		int** sumaMacierzy = SumaMacierzy<int>(macierzA, macierzB, LiczbaWierszy, LiczbaKolumn);
		WypiszMacierz(sumaMacierzy, LiczbaWierszy, LiczbaKolumn);

		int** skalarMacierzy = MnozenieniePrzezSkalarMacierzy<int>(macierzA, LiczbaWierszy, LiczbaKolumn, 3);
		WypiszMacierz(skalarMacierzy, LiczbaWierszy, LiczbaKolumn);

		int** transponowanieMacierzy = TransponowanieMacierzy<int>(macierzA, LiczbaWierszy, LiczbaKolumn);
		WypiszMacierz(transponowanieMacierzy, LiczbaWierszy, LiczbaKolumn);

		int** iloczynMacierzy = IloczynMacierzy<int>(macierzA, LiczbaWierszy, LiczbaKolumn, macierzB, LiczbaWierszy, LiczbaKolumn);
		WypiszMacierz(iloczynMacierzy, LiczbaWierszy, LiczbaKolumn);

		for (int i = 0; i < liczbaWierszyMacierzyA; i++)
			delete[] macierzA[i];
		delete[] macierzA;

		for (int i = 0; i < liczbaWierszyMacierzyB; i++)
			delete[] macierzB[i];
		delete[] macierzB;
		*/

		int** macierzA = WczytajZPliku<int>("macierzA.txt");
		int liczbaWierszyMacierzyA = LiczbaWierszy;
		int liczbaKolumnMacierzyA = LiczbaKolumn;

		cout << "Macierz A:" << endl;
		WypiszMacierz(macierzA, liczbaWierszyMacierzyA, liczbaKolumnMacierzyA);

		double wyznacznik = WyznacznikMacierzyNormalizacja<int>(macierzA, liczbaWierszyMacierzyA, liczbaKolumnMacierzyA);
		cout << "Wyznacznik macierzy A: " << fixed << setprecision(2) << wyznacznik << endl;

		for (int i = 0; i < liczbaWierszyMacierzyA; i++)
			delete[] macierzA[i];
		delete[] macierzA;
	}
	catch (const myError& e)
	{
		cerr << "Wystapil blad: " << e.what() << endl;
	}
	catch (const exception& e)
	{
		cerr << "Wystapil nieoczekiwany blad w: " << e.what() << endl;
	}
}