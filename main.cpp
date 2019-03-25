#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

inline void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
};

/*

void wypiszElementy(int **tablicaZadan, int iloscZadan, int iloscMaszyn)
{
    cout << "******************" << endl;
    for (int i = 0; i < iloscZadan; i++)
    {
        for (int j = 0; j < iloscMaszyn; j++)
        {
            cout << tablicaZadan[i][j] << " ";
        }
        cout << endl;
    }
    cout << "******************" << endl;
}

*/

int obliczNEH(int **tablicaKolejnosci, int iloscZadan, int iloscMaszyn)
{
    int czasAktualny = 0;
    int czasMinimalny = 99999;

    int **tablicaTymczasowa = new int *[iloscZadan];
    for (int k = 0; k < iloscZadan; k++)
        tablicaTymczasowa[k] = new int[iloscMaszyn];

    for (int i = 0; i < iloscZadan; i++)
        for (int j = 0; j < iloscMaszyn; j++)
            tablicaTymczasowa[i][j] = tablicaKolejnosci[i][j];

    int **harmonogram = new int *[iloscZadan];
    for(int i = 0; i < iloscZadan; i++)
        harmonogram[i] = new int[iloscMaszyn];

    if (iloscZadan == 1)
    {
        for (int j = 0; j < iloscMaszyn; j++)
        {
            harmonogram[0][j] = tablicaTymczasowa[0][j];
            czasAktualny += harmonogram[0][j];
            czasMinimalny = czasAktualny;
        }

        for (int x = 0; x < iloscZadan; x++)
            for (int z = 0; z < iloscMaszyn; z++)
                tablicaKolejnosci[x][z] = tablicaTymczasowa[x][z];
    }
    else
    {
        for (int i = 1; i < iloscZadan+1; i++)
        {
            if  (i != iloscZadan)
            {
                for (int n = 0; n < iloscZadan; n++)
                    for (int m = 0; m < iloscMaszyn; m++)
                    {
                        czasAktualny = 0;
                        if (n == 0 && m == 0)
                        {
                            harmonogram[n][m] = tablicaTymczasowa[n][m];
                            czasAktualny += harmonogram[n][m];
                        }
                        else if (n == 0 && m != 0)
                        {
                            harmonogram[n][m] = harmonogram[n][m-1] + tablicaTymczasowa[n][m];
                            czasAktualny += harmonogram[n][m];
                        }
                        else if (n != 0 && m == 0)
                        {
                            harmonogram[n][m] = harmonogram[n-1][m] + tablicaTymczasowa[n][m];
                            czasAktualny += harmonogram[n][m];
                        }
                        else
                        {
                            harmonogram[n][m] = max(harmonogram[n][m-1], harmonogram[n-1][m]) + tablicaTymczasowa[n][m];
                            czasAktualny += harmonogram[n][m];
                        }
                    }

                if (czasAktualny <= czasMinimalny)
                {
                    czasMinimalny = czasAktualny;

                    for (int x = 0; x < iloscZadan; x++)
                        for (int z = 0; z < iloscMaszyn; z++)
                            tablicaKolejnosci[x][z] = tablicaTymczasowa[x][z];
                }

                swap(tablicaTymczasowa[iloscZadan-i-1],tablicaTymczasowa[iloscZadan-i]);

            }
            else
            {
                for (int n = 0; n < iloscZadan; n++)
                    for (int m = 0; m < iloscMaszyn; m++)
                    {
                        czasAktualny = 0;
                        if (n == 0 && m == 0)
                        {
                            harmonogram[n][m] = tablicaTymczasowa[n][m];
                            czasAktualny += harmonogram[n][m];
                        }
                        else if (n == 0 && m != 0)
                        {
                            harmonogram[n][m] = harmonogram[n][m-1] + tablicaTymczasowa[n][m];
                            czasAktualny += harmonogram[n][m];
                        }
                        else if (n != 0 && m == 0)
                        {
                            harmonogram[n][m] = harmonogram[n-1][m] + tablicaTymczasowa[n][m];
                            czasAktualny += harmonogram[n][m];
                        }
                        else
                        {
                            harmonogram[n][m] = max(harmonogram[n][m-1], harmonogram[n-1][m]) + tablicaTymczasowa[n][m];
                            czasAktualny += harmonogram[n][m];
                        }
                    }

                if (czasAktualny <= czasMinimalny)
                {
                    czasMinimalny = czasAktualny;

                    for (int x = 0; x < iloscZadan; x++)
                        for (int z = 0; z < iloscMaszyn; z++)
                            tablicaKolejnosci[x][z] = tablicaTymczasowa[x][z];
                }
            }
        }
    }
    delete harmonogram;
    return czasMinimalny;
}

int algorytmNEH(int **tablicaZadan, int iloscZadan, int iloscMaszyn)
{
    int wagaAktualna = 0;
    int indeksMaksymalnego = 0;
    int wagaMaksymalna = 0;

    int Cmax = 0;

    int **tablicaKolejnosci = new int *[iloscZadan];
    for (int k = 0; k < iloscZadan; k++)
        tablicaKolejnosci[k] = new int[iloscMaszyn];

    for (int k = 0; k < iloscZadan; k++)
    {
        wagaMaksymalna = 0;
        for (int i = 0; i < iloscZadan; i++)
        {
            wagaAktualna = 0;

            for (int j = 0; j < iloscMaszyn; j++)
            {
                wagaAktualna += tablicaZadan[i][j];
            }
            if (wagaAktualna > wagaMaksymalna)
            {
                wagaMaksymalna = wagaAktualna;
                indeksMaksymalnego = i;
            }
        }

        for (int j = 0; j < iloscMaszyn; j++)
            tablicaKolejnosci[k][j] = tablicaZadan[indeksMaksymalnego][j];

        for (int j = 0; j < iloscMaszyn; j++)
            tablicaZadan[indeksMaksymalnego][j] = 0;

        int czas = obliczNEH(tablicaKolejnosci, k+1, iloscMaszyn);

        Cmax = czas;

    }
    cout << "Cmax = " << Cmax << endl;
    delete tablicaKolejnosci;
}

int main()
{
    int **tablicaZadan, iloscZadan, iloscMaszyn;

    fstream input;
    input.open("inputData.txt");
    if(input)
    {
        input >> iloscZadan;
        input >> iloscMaszyn;

        tablicaZadan = new int *[iloscZadan];
        for(int i = 0; i < iloscZadan; i++)
            tablicaZadan[i] = new int[iloscMaszyn];

        for (int i = 0; i < iloscZadan; i++)
            for (int j = 0; j < iloscMaszyn; j++)
                input >> tablicaZadan[i][j];
    }
    input.close();
    cout << "Zadania: " << iloscZadan << ", Maszyny: " << iloscMaszyn << endl << endl;

    algorytmNEH(tablicaZadan,iloscZadan,iloscMaszyn);

    delete tablicaZadan;
}
