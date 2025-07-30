/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Sebastian
 *
 * Created on 28 de junio de 2025, 01:22 AM
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iterator>
#include <map>
#include <algorithm>
#define IND 15
#define ITERACIONES 1000
#define TSELECCION 0.5
#define TCASAMIENTO 0.5
int *gpaq;



using namespace std;

void MochilaGenetica(int *paquetes,int n, int peso);
void GenerarPoblacionInicial(vector<vector<int>> &poblacion,
            int *paquetes,int peso, int n);
bool Aberracion(vector<int>vcromosoma,int *paquetes,int peso);
void Seleccion(vector<vector<int>>&padres,vector<vector<int>>poblacion,
        int *paquetes, int n,int peso);
void CalculoSupervivencia(vector<vector<int>>poblacion,vector<int> &vsupervivencia,
        int* paquetes, int peso,int n);
int CalcularFitness(vector<int> vcromosoma,int *paquetes);
void CargarRuleta(vector<int>vsupervivencia, int *ruleta);
void Casamiento(vector<vector<int>>&padres, vector<vector<int>>&poblacion,
            int *paquetes, int peso);
void GenerarHijo(vector<int>&padre,vector<int> &madre,
            vector<int>&hijo);
void Inversion(vector<vector<int>>&poblacion,vector<vector<int>> padres, 
        int *paquetes, int peso);
void EliminarRepetido(vector<vector<int>>&poblacion);
int CalcularDecimal(vector<int> vcromosoma);
void GenerarElite(vector<vector<int>>&poblacion,int *paquetes);
bool compara(vector<int>a,vector<int>b);
void MuestraPoblacion(vector<vector<int>>poblacion,int *paquetes);

int main(int argc, char** argv) {
    int paquetes[]={4,9,10,3,15,11,9,20,12,9,10,11,18,27,14,15};
    int peso=53;
    int n=sizeof(paquetes)/sizeof(paquetes[0]);
    
    MochilaGenetica(paquetes, n, peso);
    return 0;
}

void MochilaGenetica(int *paquetes,int n, int peso){
    int cont = 0;
    vector<vector<int>>poblacion;
    GenerarPoblacionInicial(poblacion,paquetes,peso,n);
    while(1){
        vector<vector<int>>padres;
        Seleccion(padres,poblacion,paquetes, n, peso);
        Casamiento(padres, poblacion, paquetes, peso);
        Inversion(poblacion, padres, paquetes, peso);
        EliminarRepetido(poblacion);
        GenerarElite(poblacion,paquetes);
        cont++;
        if(cont==ITERACIONES)break;
    }
    MuestraPoblacion(poblacion,paquetes); 
}

void GenerarPoblacionInicial(vector<vector<int>> &poblacion,
            int *paquetes,int peso, int n){
    int cont=0;
    
    srand(time(NULL));
    while(cont<IND){
        vector<int>vcromosoma;
        for(int j=0;j<n;j++){
            vcromosoma.push_back(rand()%2);
        }
        if(!Aberracion(vcromosoma,paquetes,peso)){
            poblacion.push_back(vcromosoma);
            cont++;
        }
    }
}

bool Aberracion(vector<int>vcromosoma,int *paquetes,int peso){
    int total=0;
    for(int i=0;i<vcromosoma.size();i++)
        total+=vcromosoma[i]*paquetes[i];
    return total>peso;
}


void Seleccion(vector<vector<int>>&padres,vector<vector<int>>poblacion,
        int *paquetes, int n,int peso){
    int ruleta[100];
    for(int i=0;i<100;i++){
        ruleta[i]=-1;
    }
    vector<int>vsupervivencia;
    CalculoSupervivencia(poblacion, vsupervivencia, paquetes, peso,n);
    CargarRuleta(vsupervivencia, ruleta);
    int nselect=TSELECCION*poblacion.size(); //Solo se tomara a la mitad de la poblacion
    for(int i=0;i<nselect;i++){
        int indice=rand()%100;
        if(ruleta[indice]>-1){
            padres.push_back(poblacion[ruleta[indice]]);
        }
    }
    
}

void CalculoSupervivencia(vector<vector<int>>poblacion,vector<int> &vsupervivencia,
        int* paquetes, int peso,int n){
    int suma=0;
    
    for(int i=0;i<poblacion.size();i++){
        suma+=CalcularFitness(poblacion[i],paquetes);
    }
    for(int i=0;i<poblacion.size();i++){
        int porSup = round(100*CalcularFitness(poblacion[i],paquetes)/suma);
        vsupervivencia.push_back(porSup);
    }
}

int CalcularFitness(vector<int> vcromosoma,int *paquetes){
    int cont=0;
    for(int i=0;i<vcromosoma.size();i++){
        cont+=  vcromosoma[i]*paquetes[i]; //Calcula el fitness
    }
    
    return cont; //Devuelve el fitness
}

void CargarRuleta(vector<int>vsupervivencia, int *ruleta){
    
    int indice=0;
    for(int i=0;i<vsupervivencia.size();i++){
        for(int j=0;j<vsupervivencia[i];j++){
            ruleta[indice]=i;
            indice++;
        }
    }
}

void Casamiento(vector<vector<int>>&padres, vector<vector<int>>&poblacion,
            int *paquetes, int peso){
    for(int i=0;i<padres.size();i++){
        for(int j=0;j<padres.size();j++){
            if(i!=j){
                vector<int>hijo;
                GenerarHijo(padres[i],padres[j],hijo);
                if(!Aberracion(hijo,paquetes,peso)){
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

void GenerarHijo(vector<int>&padre,vector<int> &madre,
            vector<int>&hijo){
    int pos=round(padre.size()*TCASAMIENTO);
    for(int i=0;i<pos;i++){
        hijo.push_back(padre[i]);
    }
     for(int i=pos;i<madre.size();i++){
        hijo.push_back(madre[i]);
    }
}


void Inversion(vector<vector<int>>&poblacion,vector<vector<int>> padres, 
        int *paquetes, int peso){
    for(int i=0;i<padres.size();i++){
        vector<int>nsol;
        for(int j=0;j<padres[i].size();j++){
            if(padres[i][j]){
                nsol.push_back(1);
            }else{
                nsol.push_back(0);
            }
        }
         if(!Aberracion(nsol,paquetes,peso)){
        poblacion.push_back(nsol);
        }
    }
}

void EliminarRepetido(vector<vector<int>>&poblacion){
    //Para que se eliminen los repetidos usamos map (En un map no se tienen id iguales)
    map<int,vector<int>>municos;
    
    for(int i=0;i<poblacion.size();i++){
        int dec=CalcularDecimal(poblacion[i]);
        municos[dec]=poblacion[i];
    }
    poblacion.clear();
    for(map<int,vector<int>>::iterator it = municos.begin(); it!=municos.end();it++){
        poblacion.push_back(it->second);
    }
}

int CalcularDecimal(vector<int> vcromosoma){
    int num=0;
    for(int i=0;i<vcromosoma.size();i++){
        num+=pow(2,i)*vcromosoma[i]; //Al ser binario si dos cadenas de binarios son iguales, la potencia sera igual
    }
    return num;
}

void GenerarElite(vector<vector<int>>&poblacion,int *paquetes){
    gpaq=paquetes;
    sort(poblacion.begin(),poblacion.end(),compara);
    poblacion.erase(poblacion.begin()+IND,poblacion.end());
}

bool compara(vector<int>a,vector<int>b){
    int fa=CalcularFitness(a,gpaq);
    int fb=CalcularFitness(b,gpaq);
    return fa>fb;
}

void MuestraPoblacion(vector<vector<int>>poblacion,int *paquetes){
     for(int i=0;i<poblacion.size();i++){
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< CalcularFitness(poblacion[i],paquetes) <<endl;
    }
    cout <<endl;
}