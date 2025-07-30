#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;


void MochilaBacktracking(int capacidad, vector<int>peso, vector<int>valor,int &maxValor,int valorActual,
        int pesoActual, int i);
int Max(int a,int b);
/*
 * 
 */
int main(int argc, char** argv) {
    vector<int>valor = {60,100,120};
    vector<int>peso = {10,20,30};
    int capacidad=50;
    
    
    int maxValor= 0;
    MochilaBacktracking(capacidad, peso, valor,maxValor,0,0,0);
    cout<<"El valor máximo que se puede obtener en la mochila es: "<<maxValor<<endl;
    
    return 0;
}

void MochilaBacktracking(int capacidad, vector<int>peso, vector<int>valor,int &maxValor,int valorActual,
        int pesoActual, int i){
    if(pesoActual>capacidad){
        return; //Se excedio la capacidad
    }
    
    if(peso.size()==i){ //Se acabo el arreglo
        maxValor=Max(maxValor,valorActual);
        return;
    }
    
    //Tomar el elemento i
    MochilaBacktracking(capacidad,peso,valor,maxValor,valorActual+valor[i], pesoActual+peso[i],i+1);
    
    //No tomar el elemento i
    MochilaBacktracking(capacidad,peso,valor,maxValor,valorActual, pesoActual,i+1);
}


int Max(int a,int b){
    if(a>b)return a;
    return b;
}
