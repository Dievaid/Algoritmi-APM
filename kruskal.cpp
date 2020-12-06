#include <iostream>
#include <fstream>
using namespace std;

typedef struct
{
    int x, y, cost; //Vectorul este format din x-nodul1, y-nodul2 si costul de pe muchia lor
} muchie;

int viz[30], n, m, c;
muchie v[30], aux;

//cititm datele problemei sub forma: nod1 -> nod2 – cost

void citire()
{
    ifstream f("graf.txt");
    int i;
    f >> n;
    f >> m;
    for (i = 1; i <= m; i++)
        f >> v[i].x >> v[i].y >> v[i].cost;
}

//Sortam muchiile in functie de costul lor- Partea „Greedy” din algoritm

void sortare()
{
    int k = 0, i;
    while (k == 0)
    {
        k = 1;
        for (i = 1; i <= m - 1; i++)
        {
            if (v[i].cost > v[i + 1].cost)
            {
                aux = v[i + 1];
                v[i + 1] = v[i];
                v[i] = aux;
                k = 0;
            }
        }
    }
}

void kruskal()
{
    int i, j, k;
    i = 1;
    for (k = 1; k <= n - 1; k++)
    { // verificam sa nu vizitam noduri deja vizitate
        while (viz[v[i].x] == viz[v[i].y] && viz[v[i].x] != 0)
            i++;
        //calculam costul total al arborelui de cost minim
        c += v[i].cost;
        //afisam cele 2 noduri
        cout << v[i].x << " " << v[i].y << "\n";
        //daca cele 2 noduri nu sunt vizitate atunci le vizitam si le salvam o valoare din cele 2 //in „viz”
        if (viz[v[i].x] + viz[v[i].y] == 0)
            viz[v[i].x] = viz[v[i].y] = v[i].x;
        //daca 1 din cele 2 valori este 0 o completam cu valoarea celeilalte
        else
            //daca ambele valori fac parte deja dintr-un arbore secundar, modificam toate valorile
            //lui cu valorile celuilalt; practic legam cei 2 arbori
            if (viz[v[i].x] * viz[v[i].y] == 0)
            viz[v[i].x] = viz[v[i].y] = viz[v[i].x] + viz[v[i].y];
        else
        {
            for (j = 1; j <= n; j++)
                if (viz[j] == viz[v[i].x] && j != v[i].x)
                    viz[j] = viz[v[i].y];

            viz[v[i].x] = viz[v[i].y];
        }
        i++;
    }
    cout << c;
}

int main()
{
    citire();
    sortare();
    kruskal();
}