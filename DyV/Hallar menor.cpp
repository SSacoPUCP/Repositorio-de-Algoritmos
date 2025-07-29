#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15


int BuscarMenor(int *num,int inicio,int fin);
int HallarMenor(int a,int b);
int main(int argc, char** argv){
    
    int num[7]={5,6,7,1,2,3,4};
    cout<<"El menor es: "<<BuscarMenor(num,0,6);

}

int BuscarMenor(int *num,int inicio,int fin){    
    int med=(inicio+fin)/2;
    if(inicio==fin)return num[med];
    
    int menorIzq=BuscarMenor(num,inicio,med);
    int menorDer=BuscarMenor(num,med+1,fin);
    int menor= HallarMenor(menorDer,menorIzq);
    return menor;
}

int HallarMenor(int a,int b){
    if(a<b)return a;
    else return b;
}
