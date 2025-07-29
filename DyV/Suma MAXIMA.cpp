#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15


int HallarSuma(int *num,int inicio,int fin);
int MaximoTres(int a, int b, int c);
int Maximo(int a,int b);
int SumaMezcla(int *num,int inicio,int med,int fin);

int main(int argc, char** argv){
    
    int num[8]={-2,-5,6,-2,-3,1,5,-6};
    cout<<"La suma maxima es: "<<HallarSuma(num,0,7);
}

int HallarSuma(int *num,int inicio,int fin){
    int med=(fin + inicio)/2;
    if(inicio==fin)return num[med];
    int sumMaxDer=HallarSuma(num,inicio,med);
    int sumMaxIzq=HallarSuma(num,med+1,fin);
    int maxMezcla=SumaMezcla(num,inicio,med,fin);
    return MaximoTres(sumMaxDer,sumMaxIzq, maxMezcla);
    
    
}

int MaximoTres(int a, int b, int c){
    Maximo(Maximo(a,b),c);
}

int Maximo(int a,int b){
    if(a<b)return b;
    else return a;
}

int SumaMezcla(int *num,int inicio,int med,int fin){
    int suma=0;
    int sumaIzq=-99999;
    for(int i=med;i>=inicio;i--){
        suma=suma+num[i];
        if(sumaIzq<suma){
            sumaIzq=suma;
        }
    }
    suma=0;
    int sumaDer=-99999;
    for(int i=med+1;i<=fin;i++){
        suma=suma+num[i];
        if(sumaDer<suma){
            sumaDer=suma;
        }
    }
    MaximoTres(sumaDer+sumaIzq,sumaDer,sumaIzq);
}



