#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15


int BuscarMayor(int *num,int inicio,int fin);

int main(int argc, char** argv){
    
    int num[9]={12,23,34,45,56,77,34,11,9};
    cout<<"El maximo valor del arreglo es: "<<BuscarMayor(num,0,8);
}

int BuscarMayor(int *num,int inicio,int fin){
    int med=(inicio+fin)/2;
    if(inicio==fin)return num[med];
    if(num[med]<num[med+1]){
        BuscarMayor(num,med+1,fin);
    }else{
        BuscarMayor(num,inicio,med);
    }
    
}
