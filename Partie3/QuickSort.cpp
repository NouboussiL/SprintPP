//
// Created by lionel on 16/12/2019.
//

#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <random>

using namespace std;

void generation_aleatoire(int n, int* tab, int graine, int max){
    srand(time(NULL)+graine);
    for(int i =0; i<n; i++)
        tab[i] = rand()%(max+1);
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b=tmp;
}

int Partitionnement_Elementaire(int * tab, int n, int pivot){
    int s = -1;
    for(int i = 0; i<n; i++){
        if(tab[i]<=pivot){
            s++;
            swap(tab+s,tab+i);
        }
    }
    s++;
    return s;
}

void Partitionnement(int * tab, int root, int n, int pivot, int * s, int * r){
    int pid, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    int * sendcounts = new int[nprocs];
    int * displs = new int[nprocs];

    int q = n/nprocs;
    int reste = n%nprocs;
    for(int i =0; i< nprocs; i++){
        sendcounts[i] = i< reste ? q+1 : q;
        displs[i] = i< reste ? i*(q+1) : i*q+reste;
    }

    int *tab_local = new int[n/nprocs +1];

    MPI_Scatterv(tab,sendcounts, displs,MPI_INT, tab_local,q+1,MPI_INT,root,MPI_COMM_WORLD);
    *s= Partitionnement_Elementaire(tab_local,sendcounts[pid],pivot);
    *r= sendcounts[pid]-*s;


}

void SommePrefixe(int s, int r, int pivot, int nprocs, int pid, int *somme_left, int* somme_right){

}


int main(int argc, char** argv){
    int pid, nprocs;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);

    int n = atoi(argv[1]);

    int root = atoi(argv[2]);
    int* tab_global;


    int pivot = 0;


    if(pid==root){
        tab_global = new int[n];
        generation_aleatoire(n, tab_global, pid, 50);
        cout<<"je suis : "<<pid<<" et le tableau initial est ";
        for(int i =0; i<n ; i++){
            cout<< tab_global[i] << " ";
        }
        cout<<endl;
        srand(time(NULL)+pid);
        pivot = tab_global[rand()%n];
        cout << "le pivot est " << pivot << endl;
    }

    MPI_Bcast(&pivot,nprocs,MPI_INT,root,MPI_COMM_WORLD);

    int s=-1;
    int r=-1;
    Partitionnement(tab_global,0,n,pivot,&s,&r);
    for(int i = 0; i<nprocs; i++) {

        if (pid == i) {
            cout<<"je suis "<<pid<<" : ";
            cout << s<< " "<<r<< endl;
        }
    }



    MPI_Finalize();
}

