#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15

int BuscarInicioBomba(int *bomba,int inicio,int fin);
int VerificarRadiacion(int *bomba,int inicio,int fin);
int Mayor(int a,int b);

int main(int argc, char** argv){
    int bomba[14]={0,-1,0,-1,0,1,1,2,2,2,2,2,1,1};
    //Primero haremos un dyv para hallar donde empieza la bomba
    int posInicio=BuscarInicioBomba(bomba,0,13);
    if(posInicio>-1){
        cout<<"La bomba exploto en la posicion "<<posInicio<<endl;
        int megatones=VerificarRadiacion(bomba,posInicio,13);
        cout<<"La bomba es de  "<<megatones<<"megatones "<<endl;
    }else{
        cout<<"La bomba no exploto"<<endl;
    }
    
    
}

int BuscarInicioBomba(int *bomba,int inicio,int fin){
    if(inicio>fin) return -1;
    int med=(inicio+fin)/2;
    if(bomba[med]==0 and bomba[med+1]>bomba[med]) return med;
    if(bomba[med]>0){
        BuscarInicioBomba(bomba,inicio,med-1);
    }else{
        BuscarInicioBomba(bomba,med+1,fin);
    }
}


int VerificarRadiacion(int *bomba,int inicio,int fin){
    
    int med=(inicio+fin)/2;
    if(inicio==fin)return bomba[med];
    int mayorIzq=VerificarRadiacion(bomba,inicio,med);
    int mayorDer=VerificarRadiacion(bomba,med+1,fin);
    Mayor(mayorDer,mayorIzq);
    
}

int Mayor(int a,int b){
    if(a>b)return a;
    return b;
}



