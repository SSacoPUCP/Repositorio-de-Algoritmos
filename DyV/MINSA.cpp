#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define M 6
#define N 8


int BuscarMaximo(int *num,int inicio,int fin);
int BuscarCentro(int *num,int inicio,int med,int fin);
int MaximoTres(int a,int b,int c);
int Maximo(int a,int b);

int main(int argc, char** argv){
    int num[10]={1,2,9,10,16,10,13,8,2,10};
    cout<<"Maximo dias: "<<BuscarMaximo(num,0,9);
    
}

int BuscarMaximo(int *num,int inicio,int fin){
    int med=(fin + inicio)/2;
    if(inicio==fin)return 1;
    int maxIzq=BuscarMaximo(num,inicio,med);
    int maxDer=BuscarMaximo(num,med+1,fin);
    int maxMezcla=BuscarCentro(num,inicio,med,fin);
    return MaximoTres(maxIzq,maxDer,maxMezcla);
}

int BuscarCentro(int *num,int inicio,int med,int fin){
    int cuentaIzq=1;
    for(int i=med;i>inicio;i--){
        if(num[i]>num[i-1]){
            cuentaIzq++;
        }else{
            break;
        }
    }
    int cuentaDer=1;
    for(int i=med+1;i<fin;i++){
        if(num[i]<num[i+1]){
            cuentaDer++;
        }else{
            break;
        }
    }
    if (num[med]<num[med+1]){
        return cuentaIzq + cuentaDer;
    }
    return cuentaIzq;
}

int MaximoTres(int a,int b,int c){
    return Maximo(Maximo(a,b),c);
}

int Maximo(int a,int b){
    if(a<b)return b;
    return a;
}