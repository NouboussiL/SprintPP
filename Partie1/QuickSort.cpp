//
// Created by lionel on 16/12/2019.
//

#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <random>


using namespace std;

void partionnement(int* tab, int n, int pivot, int nb_threads, int*s , int* r){
    int id = omp_get_thread_num();
    omp_set_num_threads(nb_threads);
#pragma omp parallel
    {
        int id = omp_get_thread_num();
#pragma omp for
        for(int i =0; i< n; i++){
            if(tab[i]>pivot) r[id]+=1;
            else s[id]+=1;
        }
    }
}

int main(int argc, char* argv[]){
    int tab[7] = {10,17,5,9,11};
    int s[4] = {0,0,0,0};
    int r[4] = {0,0,0,0};

    partionnement(tab,5,9,4,s,r);

    for(int i = 0; i<4;i++){
        cout<<r[i]<<" ";
    }
    cout<<endl;

    for(int i = 0; i<4;i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
}


