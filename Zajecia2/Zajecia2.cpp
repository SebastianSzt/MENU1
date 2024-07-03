#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void IloczynSkalarny(double* wektor1, double* wektor2, int dlugosc)
{
    double IloczynSkalarny = 0;
    for (int i = 0; i < dlugosc; i++)
    {
        IloczynSkalarny += wektor1[i] * wektor2[i];
    }

    cout << "Iloczyn skalarny wektorow A i B wynosi: " << IloczynSkalarny << endl;
}

void DaneRecznie()
{
    int dlugosc;
    cout << "Podaj dlugosc wektora: ";
    cin >> dlugosc;

    double* wektor1 = new double[dlugosc];
    double* wektor2 = new double[dlugosc];

    int wybor;
    cout << "1. Losowo" << endl << "2. Reczne wprowadzanie" << endl;
    cin >> wybor;

    if (wybor == 1)
    {
        srand(time(NULL));
        cout << "Elementy wektora nr 1: ";
        for (int i = 0; i < dlugosc; i++)
        {
            wektor1[i] = (double)(rand() % 10);
            wektor1[i] += (double)(rand()) / RAND_MAX * 0.9999999;
            cout << wektor1[i] << " ";
        }
        cout << endl;

        cout << "Elementy wektora nr 2: ";
        for (int i = 0; i < dlugosc; i++)
        {
            wektor2[i] = (double)(rand() % 10);
            wektor2[i] += (double)(rand()) / RAND_MAX * 0.9999999;
            cout << wektor2[i] << " ";
        }
        cout << endl;
    }
    else if (wybor == 2)
    {
        cout << "Wprowadz elementy wektora nr 1:" << endl;
        for (int i = 0; i < dlugosc; i++)
        {
            double element;
            cin >> element;
            wektor1[i] = element;
        }

        cout << "Wprowadz elementy wektora nr 2:" << endl;
        for (int i = 0; i < dlugosc; i++)
        {
            double element;
            cin >> element;
            wektor2[i] = element;
        }
    }
    else
    {
        cout << "Niepoprawny wybor" << endl;
        return;
    }

    IloczynSkalarny(wektor1, wektor2, dlugosc);

    delete[] wektor1;
    delete[] wektor2;
}

void DaneZPliku()
{
    string nazwaPliku;
    cout << "Podaj nazwe pliku: ";
    cin >> nazwaPliku;

    fstream plik(nazwaPliku);

    if (!plik.is_open()) 
    {
        cout << "Nie udalo sie otworzyc pliku." << endl;
        return;
    }

    int linie = 0;
    int dlugosc = 0;
    int tmp = 0;
    string linia;

    while (getline(plik, linia) && dlugosc == tmp) 
    {
        linie++;
        tmp = 0;
        istringstream strumien(linia);
        double liczba;
        while (strumien >> liczba)
            tmp++;
        if (dlugosc == 0)
            dlugosc = tmp;
    }

    if (dlugosc == 0)
    {
        cout << "Plik jest pusty." << endl;
        plik.close();
        return;
    }
    else if (linie != 2)
    {
        cout << "Plik zawiera niepoprawna ilosc linii." << endl;
        plik.close();
        return;
    }
    else if (dlugosc != tmp)
    {
        cout << "Wektory maja rozne dlugosci." << endl;
        plik.close();
        return;
    }

    double* wektor1 = new double[dlugosc];
    double* wektor2 = new double[dlugosc];

    plik.close();
    
    plik.open(nazwaPliku);

    if (getline(plik, linia)) 
    {
        cout << "Elementy wektora nr 1: ";
        istringstream strumien(linia);
        for (int i = 0; i < dlugosc; i++)
        {
            strumien >> wektor1[i];
            cout << wektor1[i] << " ";
        }
        cout << endl;
    }

    if (getline(plik, linia)) 
    {
        cout << "Elementy wektora nr 2: ";
        istringstream strumien(linia);
        for (int i = 0; i < dlugosc; i++)
        {
            strumien >> wektor2[i];
            cout << wektor2[i] << " ";
        }
        cout << endl;
    }

    plik.close();

    IloczynSkalarny(wektor1, wektor2, dlugosc);

    delete[] wektor1;
    delete[] wektor2;
}

//Napisac program liczacy iloczyn skalarny dwoch wketorow o dowolnej (ale oczywiscie tej samej dlugosci)
void Zad3()
{
    cout << "###########################################" << endl;
    cout << "Liczenie iloczynu skalarnego dwoch wektorow" << endl;
    cout << "###########################################" << endl << endl;
    
    cout << "Czy dane pochodza z pliku? [T/N]: ";
    string dane;
    cin >> dane;
    if (dane == "T")
        DaneZPliku();
    else if (dane == "N")
        DaneRecznie();
    else
        cout << "Niepoprawna odpowiedz." << endl;
}

void sumaMacierzy(double** macierzA, double** macierzB, int liczbaWierszy, int liczbaKolumn)
{
    double** suma = new double* [liczbaWierszy];
    for (int i = 0; i < liczbaWierszy; i++)
    {
        suma[i] = new double[liczbaKolumn];
    }

    for (int i = 0; i < liczbaWierszy; i++)
    {
        for (int j = 0; j < liczbaKolumn; j++)
        {
            suma[i][j] = macierzA[i][j] + macierzB[i][j];
        }
    }

    cout << "Wynik sumy macierzy:" << endl;
    for (int i = 0; i < liczbaWierszy; i++)
    {
        for (int j = 0; j < liczbaKolumn; j++)
        {
            cout << suma[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < liczbaWierszy; i++)
    {
        delete[] suma[i];
    }
    delete[] suma;
}

//Napsiac program zawierajacy funkcje liczaca sume dwoch macierzy z pliku
void Zad4()
{
    cout << "############################" << endl;
    cout << "Liczenie sumy dwoch macierzy" << endl;
    cout << "############################" << endl << endl;

    string nazwaPliku;
    cout << "Podaj nazwe pliku: ";
    cin >> nazwaPliku;
    cout << endl;

    fstream plik(nazwaPliku);

    if (!plik.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku." << endl;
        return;
    }

    string linia;
    int liczbaWierszy = 0;
    int liczbaKolumn = 0;

    int ilosc = 0;

    while (getline(plik, linia))
    {
        if (linia.empty())
            continue;

        if (linia.find('=') != string::npos)
        {
            if (linia.find('[') == string::npos || linia.find(']') == string::npos || linia.find(',') == string::npos)
            {
                cout << "Bledny format definicji macierzy." << endl;
                plik.close();
                return;
            }
            string rozmiar = linia.substr(linia.find('[') + 1, linia.find(']') - linia.find('[') - 1);
            istringstream strumien(rozmiar);
            int tmpLiczbaWierszy = 0;
            int tmpLiczbaKolumn = 0;
            char separator;
            if (!(strumien >> tmpLiczbaWierszy >> separator >> tmpLiczbaKolumn) || separator != ',') {
                cout << "Bledny format rozmiaru macierzy." << endl;
                plik.close();
                return;
            }
            else
                ilosc++;

            if (tmpLiczbaWierszy == 0 || tmpLiczbaKolumn == 0)
            {
                cout << "Bledny rozmiar macierzy." << endl;
                plik.close();
                return;
            }

            if (liczbaWierszy == 0 && liczbaKolumn == 0)
            {
                liczbaWierszy = tmpLiczbaWierszy;
                liczbaKolumn = tmpLiczbaKolumn;
            }

            if (tmpLiczbaWierszy != liczbaWierszy || tmpLiczbaKolumn != tmpLiczbaKolumn)
            {
                cout << "Macierze maja rozne rozmiary." << endl;
                plik.close();
                return;
            }
        }
    }
    if (ilosc != 2)
    {
        cout << "Niepoprawna ilosc macierzy." << endl;
        plik.close();
        return;
    }

    double** macierzA = new double* [liczbaWierszy];
    double** macierzB = new double* [liczbaWierszy];
    for (int i = 0; i < liczbaWierszy; i++)
    {
        macierzA[i] = new double[liczbaKolumn];
        macierzB[i] = new double[liczbaKolumn];
    }
        
    plik.close();
    plik.open(nazwaPliku);

    ilosc = 0;
    while (getline(plik, linia))
    {
        if (linia.find('=') != string::npos)
        {
            ilosc++;
            
            for (int i = 0; i < liczbaWierszy; i++)
            {
                getline(plik, linia);

                if (linia.empty())
                {
                    cout << "Niepoprawny zapis." << endl;
                    plik.close();
                    return;
                }

                istringstream strumien(linia);

                for (int j = 0; j < liczbaKolumn; j++)
                {
                    if (ilosc == 1)
                    {
                        if (!(strumien >> macierzA[i][j]))
                        {
                            cout << "Bledny format elementow macierzy." << endl;
                            plik.close();
                            return;
                        }
                    }
                    else if (ilosc == 2)
                    {
                        if (!(strumien >> macierzB[i][j]))
                        {
                            cout << "Bledny format elementow macierzy." << endl;
                            plik.close();
                            return;
                        }
                    }
                }
            }
        }
    }

    cout << "Macierz A:" << endl;
    for (int i = 0; i < liczbaWierszy; i++)
    {
        for (int j = 0; j < liczbaKolumn; j++)
            cout << macierzA[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    cout << "Macierz B:" << endl;
    for (int i = 0; i < liczbaWierszy; i++)
    {
        for (int j = 0; j < liczbaKolumn; j++)
            cout << macierzB[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    sumaMacierzy(macierzA, macierzB, liczbaWierszy, liczbaKolumn);

    for (int i = 0; i < liczbaWierszy; i++)
    {
        delete[] macierzA[i];
        delete[] macierzB[i];
    }
    delete[] macierzA;
    delete[] macierzB;
}

int main()
{
    //Zad3();
    Zad4();
}