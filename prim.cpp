#include <iostream>
#include <fstream>
#include <climits>
#define N 100
using namespace std;

struct muchie
{
    int x, y, cost;
} U[N];

int n, m, ctotal;

//citim datele problemei sub forma: nod1 -> nod2 -> cost

void citire()
{
    ifstream f("graf.txt");
    int i, j;
    f >> n >> m;
    for (i = 1; i <= m; i++)
        f >> U[i].x >> U[i].y >> U[i].cost;
}

int main()
{
    citire();
    int i, j, arb[N], p, k;
    for (i = 1; i <= n; i++)
        arb[i] = i;
    int mini = INT_MAX; // initializam variabila ce cost minim cu o valoare foarte mare
    cout << "APM Prim este:\n";
    for (i = 1; i <= m; i++)
        if (U[i].cost < mini)
        {
            mini = U[i].cost;
            p = i;
        }                                    // actualizam costul minim si retinem pozitia muchiei
    ctotal = U[p].cost;                      // actualizare cost
    cout << U[p].x << ' ' << U[p].y << endl; // afisare muchie
    U[p].cost = INT_MAX;                     //seteaza costul muchiei retinute cu o valoare "infinita" pentru a nu mai fi identificata in pasii urmatori
    int arbcrt;
    arbcrt = arb[U[p].x] = arb[U[p].y];
    for (k = 2; k <= n - 1; k++)
    {
        mini = INT_MAX;
        for (i = 1; i <= m; i++)
            if (U[i].cost < mini)
                if (arb[U[i].x] == arbcrt || arbcrt == arb[U[i].y])
                    if (arb[U[i].x] != arb[U[i].y])
                    {
                        mini = U[i].cost;
                        p = i;
                    }                            //actualizam cost minim si retinem pozitia muchiei
        cout << U[p].x << ' ' << U[p].y << endl; // afisare muchie
        ctotal += U[p].cost;                     // actualizare cost total
        U[p].cost = INT_MAX;                     //seteaza costul muchiei cu o valoare "infinita" pentru a nu mai fi identificata ulterior
        arb[U[p].x] = arb[U[p].y] = arbcrt;      // unirea arborilor dintre cele 2 extremitati
    }
    cout << "Costul total este: " << ctotal;
}