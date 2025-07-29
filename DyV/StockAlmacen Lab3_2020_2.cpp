#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

#define N 15

int HallarMayor(int *producto,int inicio,int fin);
int BuscarProd(int *producto,int inicio,int fin,int buscar);
int BuscarProdDecreciente(int *producto,int inicio,int fin,int buscar);
int main(int argc, char** argv){
    int prodBuscar=20;
    int stockProd=0;
    int producto[10]={10,15,20,80,1000,200,100,50,20,10};
    int stock[10]={20,20,30,10,10,10,20,20,20,10};
    int posMax=HallarMayor(producto,0,10-1);
    int posAntes=BuscarProd(producto,0,posMax,prodBuscar);
    int posDespues=BuscarProdDecreciente(producto,posMax+1,10-1,prodBuscar);
    if(posAntes!=-1){
        stockProd+=stock[posAntes];
        cout<<"El producto esta en "<<posAntes<<endl;
    }
    if(posDespues!=-1){
        stockProd+=stock[posDespues];
        cout<<"El producto esta en "<<posDespues<<endl;
    }
    cout<<"El stock de " << prodBuscar<<" es "<<stockProd;
    
    
}

int HallarMayor(int *producto,int inicio,int fin){
    int med=(inicio+fin)/2;
    if(inicio==fin)return med;
    if(producto[med]<producto[med+1]){
        HallarMayor(producto, med+1,fin);
    }else{
        HallarMayor(producto, inicio,med);
    }
}

int BuscarProd(int *producto,int inicio,int fin,int buscar){
    if(inicio>fin)return -1;
    int med=(inicio+fin)/2;
    if(producto[med]==buscar)return med;
    if(producto[med]<buscar){
        BuscarProd(producto,med+1,fin,buscar);
    }else{
        BuscarProd(producto,inicio,med-1,buscar);
    }
}

int BuscarProdDecreciente(int *producto,int inicio,int fin,int buscar){
    if(inicio>fin)return -1;
    int med=(inicio+fin)/2;
    if(producto[med]==buscar)return med;
    if(producto[med]>buscar){
        BuscarProd(producto,med+1,fin,buscar);
    }else{
        BuscarProd(producto,inicio,med-1,buscar);
    }
}