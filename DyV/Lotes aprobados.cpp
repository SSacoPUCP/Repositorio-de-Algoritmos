#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define M 6
#define N 8

void MergeSort(char *lotes,int inicio,int fin);
void Merge(char *lotes,int inicio,int med,int fin);
int ContarIncorrectos(char *lotes,int inicio,int fin,int cont);

int main(int argc, char** argv){
    double p=0.7;
    char lotes[M][N]  = {{'F','F','F','C','C','F',' ',' '},
                                {'C','F','C','C','C','F','C','F'},
                                {'F','C','C','C','C','C','C','C'},
                                {'C','C','C','C','C','F','C',' '},
                                {'C','F','F','F','F','C',' ',' '},
                                {'C','C','F','C','F','C','C',' '}};
    for(int i=0;i<M;i++){
        MergeSort(lotes[i],0,N-1);
        //Contar la cantidad de espacios
        int contEsp=0;
        for(int j=0;j<N;j++){
            if(lotes[i][j]==' '){
                contEsp++;
            }
        }
        int cantIncorrectos=ContarIncorrectos(lotes[i],contEsp,N-1,0);
        int total=N-contEsp;
        int cantCorrectos=N-contEsp-cantIncorrectos;
        double porcentaje=(double)cantCorrectos/total;
        cout<<"Lote "<<i+1<<' ';
        if(porcentaje>0.7){
            cout<<"Aprobado"<<endl;
        }else{
            cout<<"Rechazado"<<endl;
        }
    }
    cout<<endl;
    
}

void MergeSort(char *lotes,int inicio,int fin){
    if(inicio==fin)return;
    int med=(inicio+fin)/2;
    MergeSort(lotes,inicio,med);
    MergeSort(lotes,med+1,fin);
    Merge(lotes,inicio,med,fin);
}

void Merge(char *lotes,int inicio,int med,int fin){
    int i=inicio,j=med+1;
    char aux[fin-inicio+1];
    int k=0;
    while(i<=med and j<=fin){
        if(lotes[i]>lotes[j]){
            aux[k]=lotes[j];
            j++;
        }else{
            aux[k]=lotes[i];
            i++;
        }
        k++;
    }
    while(j<=fin){
        aux[k]=lotes[j];
        j++;
        k++;
    }
    while(i<=med){
        aux[k]=lotes[i];
        i++;
        k++;
    }
    for(int p=0;p<k;p++){
        lotes[inicio + p]=aux[p];
    }
}

int ContarIncorrectos(char *lotes,int inicio,int fin,int cont){
    if(inicio>fin)return cont;
    int med=(inicio+fin)/2;
    if(lotes[med]=='F'){
        ContarIncorrectos(lotes,inicio,med-1,cont+(fin-med+1));
    }else{
        ContarIncorrectos(lotes,med+1,fin,cont);
    }
}

