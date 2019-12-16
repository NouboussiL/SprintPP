//
// Created by sophie on 09/12/2019.
//
#include <iostream>
#include <omp.h>
#include <math.h>
#include "fonctions.h"

using namespace std;

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int Partitionnement_Elementaire (int* tab, int n, int pivot) {
    int s = -1;
    for (int i=0; i<n; i++) {
        if (tab[i]<=pivot) {
            s++;
            swap(tab+s,tab+i);
        }
    }
    s++;
    return s;
}
int Partitionnement(int* tab, int n, int pivot, int nb_threads, int* s, int* r) {
#pragma omp parallel num_threads(nb_threads)
    {
        int n_local = n / nb_threads;
        int debut;
        int my_id = omp_get_thread_num();
        int reste = n%nb_threads;
        if (my_id < reste)
            debut = my_id * (n_local + 1);
        else
            debut = reste * (n_local + 1) + (my_id - reste) * n_local;
        if (my_id < reste)
            n_local++;
        int s_local = Partitionnement_Elementaire(tab + debut, n_local, pivot);
        s[my_id] = s_local;
        r[my_id] = n_local-s_local;
    }
}


void SommePrefixe(int *s, int *r, int *somme_left, int *somme_right, int nb_threads) {
    somme_left[0] = 0;
    somme_right[0] = 0;
    int *left_tmp = new int[nb_threads + 1];
    int *right_tmp = new int[nb_threads + 1];
    int *e;

#pragma omp parallel num_threads(nb_threads)
    {
        int my_id = omp_get_thread_num();
        somme_left[my_id + 1] = s[my_id];
        somme_right[my_id + 1] = r[my_id];

#pragma omp barrier
        int k = ceil((log((double) nb_threads) / log(2.0)));
        int ptr = 1;
        for (int i = 0; i <= k; i++) {
            if (my_id >= ptr) {
                left_tmp[my_id + 1] = somme_left[my_id + 1] + somme_left[my_id - ptr + 1];
                right_tmp[my_id + 1] = somme_right[my_id + 1] + somme_right[my_id - ptr + 1];
            } else {
                left_tmp[my_id + 1] = somme_left[my_id + 1];
                right_tmp[my_id + 1] = somme_right[my_id + 1];
            }
            ptr = 2 * ptr;
#pragma omp barrier
            int a = left_tmp[my_id+1];
            left_tmp[my_id+1] = somme_left[my_id+1];
            somme_left[my_id+1] = a;

            a = right_tmp[my_id+1];
            right_tmp[my_id+1] = somme_right[my_id+1];
            somme_right[my_id+1] = a;
      #pragma omp barrier
        }
    }
    delete[] left_tmp;
    delete[] right_tmp;
}

void Rearrangement(int* somme_left, int* somme_right, int* tab, int* res, int n, int nb_threads)
{
    #pragma omp parallel num_threads(nb_threads)
    {
        int my_id = omp_get_thread_num();
        int n_local = n / nb_threads;
        int debut;
        int reste = n%nb_threads;
        if (my_id < reste)
            debut = my_id * (n_local + 1);
        else
            debut = reste * (n_local + 1) + (my_id - reste) * n_local;
        if (my_id<reste)
            n_local++;
        int my_s = somme_left[my_id+1] - somme_left[my_id];


        for (int i = 0; i < my_s; i++)
            res[somme_left[my_id] + i] = tab[debut + i];

        for (int i = 0; i < n_local - my_s; i++)
            res[somme_left[nb_threads] + somme_right[my_id] + i] = tab[debut + my_s + i];

    }

}

