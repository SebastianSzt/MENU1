#include <iostream>
#include <vector>

using namespace std;

void Zad0()
{
	//Suma szeregu i = 1 do N: 1/i
	int n;
	cout << "Podaj N: ";
	cin >> n;

	float x = 0;

	for (int i = 1; i <= n; i++)
	{
		x += (1.0 / i);
	}

	cout << "Wynik: " << x << endl;
}

void Zad1()
{
	//Napisac progaram znajdujacy pierwiastki równania kwadratowego dla dowolnych abc i wypisujacy je na ekran
	double a, b, c;
	cout << "Podaj a: ";
	cin >> a;
	cout << "Podaj b: ";
	cin >> b;
	cout << "Podaj c: ";
	cin >> c;

	double delta = (b * b) - (4 * a * c);
	double pdelta = sqrt(delta);

	if (a == 0 || b == 0 || c == 0)
	{
		cout << "To nie jest rownanie kwadratowe" << endl;
	}
	else if (delta > 0)
	{
		double x1, x2;
		x1 = (-b + pdelta) / (2 * a);
		x2 = (-b - pdelta) / (2 * a);
		cout << "Wynik: x1=" << x1 << "    x2=" << x2 << endl;
	}
	else if (delta == 0)
	{
		double x0 = -b / (2 * a);
		cout << "Wynik: x0=" << x0 << endl;
	}
	else
	{
		cout << "Brak wyniku" << endl;
	}
}

void Zad2()
{
	//Napisac program liczacy iloczyn skalarny dwoch wketorow o dowolnej (ale oczywiscie tej samej dlugosci)
    vector<int> wektorA, wektorB;

    int n;
    cout << "Podaj dlugosc wektora: ";
    cin >> n;

    cout << "Wprowadz elementy wektora A:" << endl;
    for (int i = 0; i < n; i++) 
	{
        int element;
        cin >> element;
        wektorA.push_back(element);
    }

    cout << "Wprowadz elementy wektora B:" << endl;
    for (int i = 0; i < n; i++) 
	{
        int element;
        cin >> element;
        wektorB.push_back(element);
    }

    int iloczynSkalarny = 0;
    for (int i = 0; i < n; i++) 
	{
        iloczynSkalarny += wektorA[i] * wektorB[i];
    }

    cout << "Iloczyn skalarny wektorow A i B wynosi: " << iloczynSkalarny << endl;
}

int main()
{
	//Zad0();
	//Zad1();
	//Zad2();
	
	//Alokacja tablic 
	int rozmiar1D_statyczna = 5;
    int tablica1D_statyczna[rozmiar1D_statyczna];

    int rozmiar1D_dynamiczna;
    cout << "Podaj rozmiar tablicy 1D dynamicznej: ";
    cin >> rozmiar1D_dynamiczna;
    int* dynamicznaTablica1D = new int[rozmiar1D_dynamiczna];

   	int rozmiar2D_statyczna = 3;
   	int tablica2D_statyczna[rozmiar2D_statyczna][rozmiar1D_statyczna];

   	int rozmiar2D_dynamiczna;
   	cout << "Podaj liczbe wierszy tablicy 2D dynamicznej: ";
   	cin >> rozmiar2D_dynamiczna;

   	int** dynamicznaTablica2D = new int*[rozmiar2D_dynamiczna];
   	for (int i = 0; i < rozmiar2D_dynamiczna; i++) 
	{
       	dynamicznaTablica2D[i] = new int[rozmiar1D_statyczna];
   	}

    delete[] dynamicznaTablica1D;

    for (int i = 0; i < rozmiar2D_dynamiczna; i++) 
	{
        delete[] dynamicznaTablica2D[i];
    }
    delete[] dynamicznaTablica2D;

    return 0;
}
