#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<stdio.h>
#include<algorithm>
#include<cstdlib>
#include<Windows.h>
#include<time.h>

#define INSTANCE_AMOUT 120
#pragma warning(disable: 4996)

using namespace std;

struct DaneZadan
{
 int nr;
 int time;
};

struct WszystkieDane
{
 int **Tablica_Zadan;
 int zadania; //liczba zadan
 int maszyny; //liczba maszyn
 int cmax;
 double time;
 list<DaneZadan> Lista_Zadan;  //lista zadan posiadajaca nr zadania i calkowity czas na maszynach
 vector<int>rozwiazanie; //uszeregowanie nr zadan
};

bool compare(const DaneZadan& _jd1, const DaneZadan& _jd2)
{
    return _jd1.time > _jd2.time; //porownywanie czasow danych zadan i uszeregowanie malejπco
}

int wyczysc_macierz(int **Tab,int x, int y);
void wyswietl_macierz(int **Tab, int x, int y);

// zamien wektor
void swap_V(int &x,int &y);

// Odczyt danych z pliku
// WszystkieDane - wskaznik na strukture danych
// pFile - wskaünik na plik do odczytu

void GetData(WszystkieDane *D, FILE *pFile);

// Zapis danych do pliku
// WszystkieDane - wskaznik na strukture danych
// pFileOut - wskaünik na plik do zapisu

void ToFile(WszystkieDane *W, FILE *pFileOut);

// implementacja algorytmu NEH z akceleracja

void AlgNEH(WszystkieDane *N);



int main()
{
 __int64 start, stop, freq;

 __int64 start1,end1;

 WszystkieDane *ins = new WszystkieDane[INSTANCE_AMOUT]; //tablica danych zadan i maszyn o rozmiarze INSTANT_AMOUNT
 FILE *pFile;
 pFile=fopen("inputData.txt","r");

 for(int instance = 0; instance < INSTANCE_AMOUT; instance++) // for dla kolejnych instancji
  {
   GetData(ins,pFile); //wczytanie danych z pliku
   ins++;
     }
 fclose(pFile);
 ins=ins-INSTANCE_AMOUT;

 QueryPerformanceCounter((LARGE_INTEGER*)&start);

 for(int instance = 0; instance < INSTANCE_AMOUT; instance++)
 {
 QueryPerformanceCounter((LARGE_INTEGER*)&start1);
   AlgNEH(ins); //uszeregowanie danych algorytmem
   QueryPerformanceCounter((LARGE_INTEGER*)&end1);
 QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
   ins->time = ((double)(end1-start1))/freq;
   ins++;
 }

 QueryPerformanceCounter((LARGE_INTEGER*)&stop);
 QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
 cout<<" "<<endl;
 cout<<"time: " << ((double)(stop-start))/freq << "s" << endl;

 ins=ins-INSTANCE_AMOUT;
 FILE *pFileOut;
 pFileOut=fopen("data_out.txt","w");



 for(int instance = 0; instance < INSTANCE_AMOUT; instance++)
 {
   ToFile(ins,pFileOut); //zapis danych do pliku
   ins++;
 }
 fclose(pFileOut);

 getchar();
 return 0;
}

void GetData(WszystkieDane *D, FILE *pFile)
{
 int E_time;
 int time;

 char iname[6];
 DaneZadan Job;

 if(pFile == NULL){fprintf(stderr,"Error: ...\n");exit(-1);}

   fscanf(pFile,"%s",iname);
   fscanf(pFile,"%d",&D->zadania);
   fscanf(pFile,"%d",&D->maszyny);

   D->Tablica_Zadan = new int * [D->maszyny]; // i-zadan na j-maszynach
    for (int j = 0; j < D->maszyny; j++){     //dla kazdej kolumny deklaracja wierszy na stosie
     D->Tablica_Zadan[j] = new int[D->zadania];
     }

   for(int i = 0; i < D->zadania; i++)
   {
     E_time = 0;
    for(int j = 0; j < D->maszyny; j++)
    {
     fscanf(pFile,"%d",&time);
     E_time = E_time + time;
     D->Tablica_Zadan[j][i] = time;

    }
    Job.nr = i+1;
    Job.time = E_time;
    D->Lista_Zadan.push_back(Job);
   } //koniec wczytywania danych





}

void ToFile(WszystkieDane *W, FILE *pFileOut)
{
  fprintf(pFileOut,"%d ", W->cmax);
fprintf(pFileOut,"%lf ", W->time);
 fprintf(pFileOut,"\n");
}

void AlgNEH(WszystkieDane *N)
{
 int max1, min1;
 int _dict = 0;
 int new_job;
 int cmax;
 int tmp_job;
 vector<int>max_vect;
 N->rozwiazanie.clear();
 N->Lista_Zadan.sort(compare);
 N->rozwiazanie.push_back(N->Lista_Zadan.front().nr); //dodanie elementu z najd≥uøszym czasem na koniec wektiora rozwiazan
 N->Lista_Zadan.pop_front(); //usuniecie pierwszego elementu z listy


 int **E = new int*[N->maszyny+1];
  for (int i = 0; i < N->maszyny+1; i++)
  {
   E[i] = new int[N->zadania];
  }

 int **Q= new int*[N->maszyny+1];
  for (int i = 0; i < N->maszyny+1; i++)
  {
   Q[i] = new int[N->zadania];
  }
 int **F= new int*[N->maszyny+1];
  for (int i = 0; i < N->maszyny+1; i++)
  {
   F[i] = new int[N->zadania];
  }

 int **F_Q= new int*[N->maszyny+1];
  for (int i = 0; i < N->maszyny+1; i++)
  {
   F_Q[i] = new int[N->zadania];
  }
  wyczysc_macierz(E,N->maszyny+1,N->zadania);
  wyczysc_macierz(Q,N->maszyny+1,N->zadania);
  wyczysc_macierz(F,N->maszyny+1,N->zadania);
  wyczysc_macierz(F_Q,N->maszyny+1,N->zadania);

 while(N->Lista_Zadan.size() != 0)
 {
 max_vect.clear();
 for(int i=0; i < (int)N->rozwiazanie.size(); i++) //macierz E
  {
   for(int j=0; j < N->maszyny; j++)// w pierwszej kolumnie
   {

    E[j+1][i+1] = max(E[j][i+1],E[j+1][i]) + N->Tablica_Zadan[j][N->rozwiazanie[i]-1];
   }

  }
 for(int i = (int)N->rozwiazanie.size()-1; i >= 0; i--) //macierz QQ
  {
   for(int j = N->maszyny-1; j >= 0; j--)// w pierwszej kolumnie
   {

    Q[j][i] = max(Q[j+1][i],Q[j][i+1]) + N->Tablica_Zadan[j][N->rozwiazanie[i]-1];
   }

  }

 new_job = N->Lista_Zadan.front().nr; //wybranie nowego zadania
 N->Lista_Zadan.pop_front();

 for(int i=0; i < (int)N->rozwiazanie.size()+1; i++) //macierz F
  {
   for(int j=0; j < N->maszyny; j++)// w pierwszej kolumnie
   {

    F[j+1][i] = max(E[j+1][i],F[j][i]) + N->Tablica_Zadan[j][new_job-1];
   }

  }
 for(int i=0; i < (int)N->rozwiazanie.size()+1; i++) //macierz F_Q
  {
   for(int j=0; j < N->maszyny; j++)// w pierwszej kolumnie
   {

    F_Q[j][i] = Q[j][i]+F[j+1][i];
   }

  }

 for(int i=0; i < (int)N->rozwiazanie.size()+1; i++) //znajdowanie max
  {
   max1 = 0;
   for(int j=0; j < N->maszyny; j++)
   {
    if(F_Q[j][i] > max1) {max1 = F_Q[j][i];}
   }
   max_vect.push_back(max1);
  }

 min1=999999;
 for(int i=0; i < (int)max_vect.size(); i++)
 {
  if(max_vect[i]<min1){ min1 = max_vect[i];
  _dict = i;}
 }
 cmax = min1;
 N->cmax = cmax;
 N->rozwiazanie.push_back(0);
 for(int i = _dict; i < (int)N->rozwiazanie.size(); i++)
 {
  swap_V(N->rozwiazanie[i],tmp_job);
 }
 N->rozwiazanie[_dict] = new_job;


}
}
void swap_V(int &x,int &y)
{
 int temp;
 temp=x;
 x=y;
 y=temp;
}

int wyczysc_macierz(int **Tab,int x, int y)
{
 for(int i = 0; i < x; i++)
  for(int j = 0; j < y; j++)
   Tab[i][j]=0;
 return 0;
}

void wyswietl_macierz(int **Tab, int x, int y)
{
 for(int i = 0; i < x; i++){
  for(int j = 0; j < y; j++)
  {cout<<Tab[i][j];}
  cout<<" "<<endl;}
}
