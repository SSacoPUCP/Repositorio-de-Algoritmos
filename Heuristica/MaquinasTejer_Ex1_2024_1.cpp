#include <iostream>
#include <algorithm>
#include <vector>
#define M 3
#define N 6
using namespace std;

int main(int argc, char** argv) {
    int maquinas[M]={5,4,6};  //Tiempo que se toman por 1m de tela
    int tela[N]={10,7,9,12,6,8};
    
    int tiempo[M]={0,0,0};
    sort(tela,tela+N,greater<int>()); //Descendente
    sort(maquinas,maquinas+M); //Ascendente
    
    
    for(int i=0;i<N;i++){
        //min_element devuelve un puntero al elemento mas pequeño
        int mejorM = min_element(tiempo,tiempo+M) - tiempo; //min_element usa la biblioteca algorithm para hallar el menor elemento de un arreglo
        
        //La tarea la debe realizar la maquina que tenga menos tiempo acumulado
        tiempo[mejorM]=tiempo[mejorM]+tela[i]*maquinas[mejorM];
    }
    
    for(int i=0;i<M;i++){
        cout<<"La maquina "<<i+1<<" tarda "<<tiempo[i] <<endl;
    }
    int makespan = *max_element(tiempo,tiempo+M);
    cout<<"Se tardara en completar todas las tareas: "<<makespan;
    return 0;
}
