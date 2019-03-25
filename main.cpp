#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;



int main()
{
    int iloscZadan = 4;

    int tablicaZadan[iloscZadan] = {2, 6, 4, 8};
    int tablicaKolejnosci[iloscZadan];

    int wartoscMax = 0;
    int indeksMax = 0;
    for (int i = 0; i < iloscZadan; i++)
    {
        if (tablicaZadan[i] > wartoscMax)
        {
            tablicaKolejnosci[0] = tablicaZadan[i];
            wartoscMax = tablicaZadan[i];
            indeksMax = i;
        }

    }

    tablicaZadan[indeksMax] = 0;

    cout << tablicaZadan[0] << " " << tablicaZadan[1] << " " << tablicaZadan[2] << " " << tablicaZadan[3] << endl;

    wartoscMax = 0;
    indeksMax = 0;
    for (int i = 0; i < iloscZadan; i++)
    {
        if (tablicaZadan[i] > wartoscMax)
        {
            tablicaKolejnosci[1] = tablicaZadan[i];
            wartoscMax = tablicaZadan[i];
            indeksMax = i;
        }

    }

    tablicaZadan[indeksMax] = 0;

    cout << tablicaZadan[0] << " " << tablicaZadan[1] << " " << tablicaZadan[2] << " " << tablicaZadan[3] << endl;
    cout << tablicaKolejnosci[0] << " " << tablicaKolejnosci[1] << endl;

    swap(tablicaKolejnosci[0], tablicaKolejnosci[1]);

    cout << tablicaKolejnosci[0] << " " << tablicaKolejnosci[1] << endl;






};
