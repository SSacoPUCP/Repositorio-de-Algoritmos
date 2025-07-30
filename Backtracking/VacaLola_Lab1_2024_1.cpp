#include <iostream>
#include <iomanip>
#include <vector>
#define N 5
using namespace std;

bool CortesCarne(vector<int>&pesos,int capacidad,int k,int pesoActual,int numCarne, int cantCarnes,
        vector<int>&tomados, vector<bool>&usados);
void ImprimirVector(vector<int>tomados);
bool CumpleCondicion(vector<int>tomados,int peso,int k);

int main(int argc, char** argv) {
    int capacidad=15, k=4;
    vector<int>pesos={2, 8, 9, 6, 7}; //Pesos de las carnes
    vector<bool>usados(pesos.size(),false); //Vector para marcar las carnes usadas
    int pedido=1;
    bool solucion = true;
    while(solucion){ //Se repetira hasta que no encuentre solucion
        vector<int>tomados; //Las carnes tomadas por cada solucion
        solucion=CortesCarne(pesos,capacidad,k,0,0,pesos.size(),tomados,usados);
        if(solucion){
            cout<<"Pedido No: "<<pedido<<endl;
            pedido++;
        }
        ImprimirVector(tomados);
    }
    cout<<"Numero de pedidos de "<<capacidad<<" que se han podido atender: "<<pedido-1<<endl;
    
    return 0;
}

bool CortesCarne(vector<int>&pesos,int capacidad,int k,int pesoActual,int numCarne, int cantCarnes,
        vector<int>&tomados, vector<bool>&usados){
    
    //Casos base
    if(pesoActual>capacidad){
        return false; //Se excedio la capacidad
    }
    
    if(pesoActual==capacidad){
        return true; //Es igual a lo deseado
        
    }
    
    if(numCarne==cantCarnes){
        return false; //Se acabo el arreglo
    }
    
    //Se puede decidir entre tomar la carne (si no esta marcada y cumple con la condicion de k) o no tomarla
    
    //Si se toma
    if(usados[numCarne]==false){ //Verifica que no este marcada
        if(true ){ //Verifica la condicion, aqui se pondria algo con la k pero no se entiende
            tomados.push_back(pesos[numCarne]); //Lo agrega al vector de tomados
            usados[numCarne]=true; //Lo marca como tomado
            if(CortesCarne(pesos,capacidad,k,pesoActual+pesos[numCarne],numCarne+1,cantCarnes,tomados,usados)){ //Si regresa true significa que se encontro un rsultado
                return true;
            }
            usados[numCarne]=false; //Si no devolvio true significa que agarrarlo no sirve, entonces se suelta
            tomados.pop_back();
        }
    }
    
    //No se toma
    
    if(CortesCarne(pesos,capacidad,k,pesoActual,numCarne+1,cantCarnes,tomados,usados)){//Si regresa true significa que se encontro un rsultado
        return true;
    }
    
    //Si llega hasta aca no encontro un resultado yendo por este camino
    return false;
    
    
}

bool CumpleCondicion(vector<int>tomados,int peso,int k){
    for(int i=0;i<tomados.size();i++){
        if(abs(tomados[i] - peso )>k)return false; //No cumple la condicion
    }
    return true; //Cumple la condicion
}

void ImprimirVector(vector<int>tomados){
    
    for(int a:tomados){
        cout<<a<<' ';
    }
    cout<<endl;
}
