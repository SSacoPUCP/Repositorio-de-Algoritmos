#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Paquete{
    int id;
    int ganancia;
    int peso;
};

void Selecciona(Paquete *paquetes,int n,int capacidad);
bool Compara(Paquete a, Paquete b);

int main(int argc, char** argv) {
    Paquete paquetes[]{{1,10,2},
                                {2,15,3},
                                {3,10,5},
                                {4,14,12},
                                {5,8,2},
                                {6,5,5}};
    int n=sizeof(paquetes)/sizeof(paquetes[0]);
    int capacidad=20;
    Selecciona(paquetes,n,capacidad);
    
                                
    
    return 0;
}

void Selecciona(Paquete *paquetes,int n,int capacidad){
    int i=0;
    vector<Paquete>solu;
    double valor=0;
    sort(paquetes,paquetes+n,Compara);
    for(int i=0;i<n;i++){
        if(capacidad>paquetes[i].peso){
            //Entra en el contenedor
            solu.push_back(paquetes[i]);
            valor+=paquetes[i].ganancia;
            capacidad-=paquetes[i].peso;
        }
    }
    
    cout<<"Solución empleando un algoritmo heurístico voraz:  "<<endl;
    cout<<"Peso sobrante en el contenedor: "<<capacidad<<" Tn"<<endl;
    cout<<"Ganancia de la exportación:: "<<valor<<" en miles de dólares"<<endl;
    
}

bool Compara(Paquete a, Paquete b){
    double n=1.0 * a.ganancia/a.peso;
    double m=1.0 * b.ganancia/b.peso;
    return n>m;
}

