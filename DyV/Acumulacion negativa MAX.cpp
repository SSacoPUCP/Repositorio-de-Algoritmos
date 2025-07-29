#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15

int AcumulacionNegativa(int *marcas,int inicio,int fin);
int SumaTotal(int *marcas,int inicio,int med,int fin);
int MinimoTres(int a , int b, int c);
int Minimo(int a,int b);

int main(int argc, char** argv){
    int marcas[5]={2, -3, 4, -5, -7};
    int sumaMin=AcumulacionNegativa(marcas,0,4);
    cout<<"La acumulacion negativa mas alta es: "<<sumaMin<<endl;
    
}

int AcumulacionNegativa(int *marcas,int inicio,int fin){
    int med=(fin + inicio)/2;
    if(inicio==fin)return marcas[med];
    int sumaMinIzq=AcumulacionNegativa(marcas,inicio,med);
    int sumaMinDer=AcumulacionNegativa(marcas,med+1,fin);
    int minMezcla=SumaTotal(marcas,inicio,med,fin);
    return MinimoTres(sumaMinIzq,sumaMinDer,minMezcla);
}

int SumaTotal(int *marcas,int inicio,int med,int fin){
    int suma=0;
    int sumaIzq=99999;
    for(int i=med;i>=inicio;i--){
        suma=suma+marcas[i];
        if(suma<sumaIzq){
            sumaIzq=suma;
        }
    }
    suma=0;
    int sumaDer=99999;
    for(int i=med+1;i<=fin;i++){
        suma=suma+marcas[i];
        if(suma<sumaDer){
            sumaDer=suma;
        }  
    }
    MinimoTres(sumaDer+sumaIzq,sumaDer,sumaIzq);
}

int MinimoTres(int a , int b, int c){
    Minimo(Minimo(a,b),c);
}

int Minimo(int a,int b){
    if(a<b)return a;
    else return b;
}
