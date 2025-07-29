#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15


int BuscarNumero(int *num,int inicio,int fin);

int main(int argc, char** argv){
    
    int num[N]={2,2,5,5,10,10,15,18,18};
    int numNoRep;
    numNoRep=BuscarNumero(num,0,9);
    if(numNoRep>0)cout<<"El numero que no se repite es "<<numNoRep;        
    else cout<<"Todos se repiten";
}

int BuscarNumero(int *num,int inicio,int fin){
    if(inicio>fin)return -1;
    int med=(inicio+fin)/2;
    if(inicio==fin) return num[med];
    if(med%2==0){
        if(num[med+1]==num[med]){
             BuscarNumero( num, med+1, fin);
        }else{
             BuscarNumero( num, inicio, med);
        }
    }else{
        if(num[med-1]==num[med]){
             BuscarNumero( num, med+1, fin);
        }else{
             BuscarNumero( num, inicio, med);
        }
    }
        
}
