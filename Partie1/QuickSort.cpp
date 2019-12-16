//
// Created by lionel on 16/12/2019.
//

#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <random>


using namespace std;

void Partionnement(int* tab, int n, int pivot, int nb_threads, int*s , int* r){
    omp_set_num_threads(nb_threads);
#pragma omp parallel
    {
        int id = omp_get_thread_num();
#pragma omp for
        for(int i =0; i< n; i++){
                if(tab[i]>pivot){
                    r[id]+=1;
                }
                else{
                    s[id]+=1;
                }
        }
    }
}

void SommePrefixe(int* s, int* r, int* somme_left, int* somme_right, int nb_threads){
 //   somme_left = new int[nb_threads+1];
   // somme_right = new int[nb_threads+1];
    omp_set_num_threads(nb_threads);
    somme_left[0]=somme_right[0]=0;
    #pragma omp parallel sections
        {
        #pragma omp section
            {
                for(int i = 1; i<nb_threads+1; i++){
                    somme_right[i]+=somme_right[i-1]+r[i-1];
                }
            }
        #pragma omp section
        {
            for(int i = 1; i<nb_threads+1; i++){
                somme_left[i]+=somme_left[i-1]+s[i-1];
            }
        }
    }
}

void Rearrangement(int* somme_left,int* somme_right, int* tab, int* res, int n, int nb_threads){

}

int main(int argc, char* argv[]){
    int tab[5] = {10,17,5,9,11};
    int s[4] = {0,0,0,0};
    int r[4] = {0,0,0,0};

    Partionnement(tab,5,9,4,s,r);

    for(int i = 0; i<4;i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;

    for(int i = 0; i<4;i++){
        cout<<r[i]<<" ";
    }
    cout<<endl;

    int * right=new int[5];
    int * left = new int[5];

    SommePrefixe(s,r,left,right,4);

    for(int i = 0; i<5;i++){
        cout<<left[i]<<" ";
    }
    cout<<endl;

    for(int i = 0; i<5;i++){
        cout<<right[i]<<" ";
    }
    cout<<endl;
}


