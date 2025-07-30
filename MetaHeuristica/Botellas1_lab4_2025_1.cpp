/* 
 * File:   main.cpp
 * Author: Sebastian Saco Alvarado 
 *
 * Created on 14 de junio de 2025, 09:05 AM
 */

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

#define M 5
#define N 20
struct Orden{
    int id;
    int cant;
    int prioridad;
};

struct Linea{
    int id;
    vector<Orden> asignadas;
};
void Grasp(Orden *ordenes,int n, int iteraciones);
bool Compara(Orden a, Orden b);

int main(int argc, char** argv) {
    Orden ordenes[N]={{1,103,2},
                     {2,58,1},
                     {3,88,3},
                     {4,126,1},
                     {5,195,2},
                     {6,90,2},
                     {7,54,3},
                     {8,195,1},
                     {9,124,2},
                     {10,113,3},
                     {11,193,2},
                     {12,55,1},
                     {13,97,1},
                     {14,97,2},
                     {15,169,2},
                     {16,50,2},
                     {17,167,3},
                     {18,74,1},
                     {19,79,2},
                     {20,109,1}};
   
    int n=sizeof(ordenes)/sizeof(ordenes[0]);
    Grasp(ordenes,n,10000);
    return 0;
}

void Grasp(Orden *ordenes,int n, int iteraciones){
    //Primero debemos ordenar las ordenes en base al tiempo que demoran prepararse
    sort(ordenes,ordenes+n,Compara);
    srand(0);
    vector<Linea>mejorSolu;
    int mejorMakespan=9999;
    for(int ite=0;ite<iteraciones;ite++){
        vector<Linea>solu={{1},
                            {2},    
                            {3},
                            {4},
                            {5}};
        vector<int>tiempoLinea(M,0); //El tiempo que cada linea esta ocupada
        vector<double>tiempos; //Obtenemos todos los tiempos de procesamiento de cada orden
        for(int i=0;i<n;i++){
            double temp = (1.0 * ordenes[i].cant)*(2+1+1.5+1.5);
            tiempos.push_back(temp);
        }
        
        
        vector<Orden>candidatos(ordenes,ordenes+n);
        
        while(!candidatos.empty()){
            int mejor= tiempos[0];
            int peor= tiempos[tiempos.size()-1];
            int umbral = mejor - 0.43*(mejor-peor); //alfa
            
            vector<Orden>RCL;
            int cont=0;
            for(Orden o : candidatos){ //Por cada orden
                if(tiempos[cont]>=umbral){ //Verificamos si es una buena opcion (RCL)
                    //Se agrega al RCL
                    RCL.push_back(o);
                }
                cont++;
            }
            if(RCL.empty())break;
            
            //Escogemos al azar cual de estos valores asignaremos a una maquina
            int r = rand()%RCL.size();
            Orden elegido = candidatos[r];
            
            //Agregamos esta orden a una linea (La mas vacia)
            int pos=min_element(tiempoLinea.begin(),tiempoLinea.end())-tiempoLinea.begin();
            //En la posicion "pos" agregaremos el tiempo
            tiempoLinea[pos]+=(1.0 * elegido.cant)*(2+1+1.5+1.5); //Aumentamos el tiempo de trabajo de la linea
            solu[pos].asignadas.push_back(elegido);
            //Se elimina el valor
            tiempos.erase(tiempos.begin()+r);
            candidatos.erase(candidatos.begin()+r);
        }
        
        //Calculamos el makespan
        int makespan = *max_element(tiempoLinea.begin(),tiempoLinea.end());
        
        if(makespan<mejorMakespan){
            mejorMakespan=makespan;
            mejorSolu=solu;
        }
        
    }
    
    cout<<"Mejor Makespan: "<<mejorMakespan<<" minutos. "<<endl;
    int i=0;
    for(Linea l : mejorSolu){
        cout<<"Linea "<<i+1<<' ';
        for(Orden o: mejorSolu[i].asignadas){
            cout<<o.id<<' ';
            //cout<<"("<<o.cant<<") ";
        }
        i++;
        cout<<endl;
    }
}

bool Compara(Orden a, Orden b){
    double n= (1.0 * a.cant)*(2+1+1.5+1.5);
    double m= (1.0 * b.cant)*(2+1+1.5+1.5);
    return n<m;
}

