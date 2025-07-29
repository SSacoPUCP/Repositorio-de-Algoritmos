#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15


int ContarCeros(int *num,int inicio,int fin, int cont);

int main(int argc, char** argv){
    
    int num[14]={1,1,1,1,1,0,0,0,0,0,0,0,0,0};
    
    int cantCeros=ContarCeros(num,0,13,0);    
    cout<<"Cantidad: "<<cantCeros;
}

int ContarCeros(int *num,int inicio,int fin, int cont){
    if(fin<inicio)return cont; //Si se cruzan los extremos termina
    int med= (inicio + fin)/2;
    if(num[med]==0){
        //Todos los datos de aqui a la derecha serian 0
        return ContarCeros(num,inicio,med-1,cont+(fin-med+1));
    }else{
        return ContarCeros(num,med+1,fin,cont);
    }
}    


