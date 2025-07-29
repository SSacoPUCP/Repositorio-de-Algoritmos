#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

#define N 15

int HallarMax(int *num,int inicio,int fin);
int CuentaCerosFinal(int *num,int inicio,int fin,int cont);
int CuentaCerosInicio(int *num,int inicio,int fin,int cont);

int main(int argc, char** argv){
    int num[10][10]={{0,0,0,3,3,7,5,5,1,1},
                                {8,8,10,9,9,5,4,4,2,0},
                                {3,5,8,9,7,6,4,2,0,0},
                                {9,7,7,4,4,4,2,0,0,0},
                                {0,2,2,3,3,4,4,5,3,3},
                                {0,0,0,0,0,0,2,3,4,5},
                                {1,2,2,3,3,4,3,2,0,0},
                                {0,0,0,0,0,0,3,5,5,7},
                                {6,5,5,2,2,1,0,0,0,0},
                                {3,2,2,0,0,0,0,0,0,0}};
    int maximo=-9999;
    for(int i=0;i<10;i++){
        int numero=HallarMax(num[i],0,10-1);
        if(numero>maximo){
            maximo=numero;
        }
    }
    cout<<"La máxima pureza de las muestras es: "<<maximo<<endl;

    
    int arrMinMax[10]={};
    int cantMin;
    int cantCeros;
    int max=-9999;
    for(int i=0;i<10;i++){
        if(num[i][0]!=0){
            cantCeros=CuentaCerosFinal(num[i],0,10-1,0);
            cantMin=10-cantCeros;
        }else{
            cantCeros=CuentaCerosInicio(num[i],0,10-1,0);
            cantMin=10-cantCeros;
        }
        arrMinMax[i]=cantMin;
        if(cantMin>max){
            max=cantMin;
        }
    }
    cout<<"Las muestras con mayor cantidad de niveles con minerales son: ";
    for(int i=0;i<10;i++){
        if(arrMinMax[i]==max){
            cout<<i+1<<' ';
        }
    }
    cout<<" con "<<max<<" estratos de minerales. ";
}

int HallarMax(int *num,int inicio,int fin){
    int med=(fin+inicio)/2;
    if(inicio==fin)return num[med];
    if(num[med]<num[med+1]){
        HallarMax(num,med+1,fin);
    }else{
        HallarMax(num,inicio,med);
    }
}

int CuentaCerosFinal(int *num,int inicio,int fin,int cont){
    if(inicio>fin)return cont;
    int med=(inicio+fin)/2;
    if(num[med]==0){
        CuentaCerosFinal(num,inicio,med-1,cont+(fin-med+1));
    }else{
        CuentaCerosFinal(num,med+1,fin,cont);
    }
}

int CuentaCerosInicio(int *num,int inicio,int fin,int cont){
    if(inicio>fin)return cont;
    int med=(inicio+fin)/2;
    if(num[med]==0){
        CuentaCerosInicio(num,med+1,fin,cont+(med-inicio+1));
    }else{
        CuentaCerosInicio(num,inicio,med-1,cont);
    }
}