#include <vector>
#include <iostream>
#include <algorithm>

#define MAX 8

using namespace std;

struct nodo{
    int posicion;
    int tiempo;
};

bool compara(nodo a,nodo b){
    return a.tiempo<b.tiempo;
}

int minruta(int ini,int fin,int mapa[][MAX]){
    int suma=0;
    int ciudad=ini;
    while(1){
        vector<nodo> vecinos;
        for(int i=0;i<MAX;i++){
            if(mapa[ciudad][i]>0){
                nodo aux;
                aux.posicion=i;
                aux.tiempo=mapa[ciudad][i];
                vecinos.push_back(aux);
            }
        }
        if(!vecinos.empty()){
            sort(vecinos.begin(),vecinos.end(),compara);
            ciudad=vecinos[0].posicion;
            suma+=vecinos[0].tiempo;
        }
        if(ciudad==fin) break;
        if(vecinos.empty()){
            cout << "No existe una ruta" << endl;
            suma=0;
            break;
        }
    }
    return suma;
}

int main(int argc, char** argv) {
    
    int mapa[][MAX]={   {0,4,5,6,0,0,0,0},
                                    {0,0,0,0,2,0,0,0},
                                    {0,0,0,0,0,0,0,3},
                                    {0,0,0,0,0,3,0,0},
                                    {0,0,0,0,0,0,10,0},
                                    {0,0,0,0,0,0,2,0},
                                    {0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0}};   
    
    cout <<"La ruta minina es:" << minruta(0,6,mapa);
    return 0;
}