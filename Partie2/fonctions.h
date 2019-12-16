//
// Created by sophie on 09/12/2019.
//

#ifndef MEMPARTAGEE_FONCTIONS_H
#define MEMPARTAGEE_FONCTIONS_H

void swap(int* a, int* b);
int Partitionnement_Elementaire(int* tab, int n, int pivot);
int Partitionnement(int* tab, int n, int pivot, int nb_threads, int* s, int* r);
void SommePrefixe(int* s, int* r, int* somme_left, int* somme_right, int nb_threads);
void Rearrangement(int* somme_left, int* somme_right, int* tab, int* res, int n, int nb_threads);


#endif //MEMPARTAGEE_FONCTIONS_H
