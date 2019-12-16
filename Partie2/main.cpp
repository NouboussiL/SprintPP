#include <iostream>

#include <omp.h>
#include <math.h>
#include "fonctions.h"

using namespace std;



int main(int argc, char** argv) {

    if (argc<2) {
        cout << "Mauvaise utilisation du programme :" << endl;
        cout << "./Etape1 [taille du tableau] [nombre de threads]" << endl;
        return 1;
    }

    omp_set_nested(1);

    int n = atoi(argv[1]);
    int nthreads = atoi(argv[2]);

    int *tab = new int[n];
    //srand(time(NULL));
    srand(64);
    for (int i = 0; i < n; i++)
        tab[i] = rand() % n;
    cout << "dans le main les données initiales :" << endl;
        for (int i = 0; i < n; i++)
            cout << tab[i] << " ";
        cout << endl;
    int pivot = tab[4];

    cout << "pivot=" << pivot << endl;
    int* s = new int[nthreads];
    int* r = new int[nthreads];
    Partitionnement(tab,n,pivot,nthreads,s,r);

    cout << "dans le main les données avec partitionnement :" << endl;
    for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
    cout << endl;

    for (int i=0; i<nthreads; i++)
        cout << s[i] << " ";
    cout << endl;
    for (int i=0; i<nthreads; i++)
        cout << r[i] << " ";
    cout << endl;


    int* somme_left = new int[nthreads+1];
    int* somme_right = new int[nthreads+1];

    SommePrefixe(s,r,somme_left,somme_right, nthreads);

    cout << "la somme des préfixes (gauche et droit)" << endl;

    for (int i=0; i<nthreads+1; i++)
        cout << somme_left[i] << " ";
    cout << endl;

    for (int i=0; i<nthreads+1; i++)
        cout << somme_right[i] << " ";
    cout << endl;

   int* res = new int[n];
    Rearrangement(somme_left, somme_right, tab, res, n, nthreads);

    cout << "dans le main les données après réarrangement :" << endl;
    for (int i = 0; i < n; i++)
        cout << res[i] << " ";
    cout << endl;

    delete[] tab;
    delete[] s;
    delete[] r;
    delete[] somme_left;
    delete[] somme_right;
    return 0;
}