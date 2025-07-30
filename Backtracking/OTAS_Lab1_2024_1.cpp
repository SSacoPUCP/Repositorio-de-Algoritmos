#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#define N 4
using namespace std;
void AgruparBacktracking(char *equipos,vector<char>agrupados,int cantEquipos,int numAgrupacion);
void ImprimirVector(vector<char>agrupados);


int main(int argc, char** argv) {
    char equipos[N]={'4','5','9','2'};
    vector<char>agrupados;
    cout<<"Los grupos que se pueden armar son: "<<endl;
    AgruparBacktracking(equipos,agrupados,N,0);
    return 0;
}

void AgruparBacktracking(char *equipos,vector<char>agrupados,int cantEquipos,int numAgrupacion){
    //  Caso base
    if(numAgrupacion==cantEquipos){
        //Ya se agruparon todos los equipos que habian
        ImprimirVector(agrupados);
        return;
    }
    
    agrupados.push_back(equipos[numAgrupacion]);
    AgruparBacktracking(equipos,agrupados,cantEquipos,numAgrupacion+1);
    agrupados.pop_back();
    
    //Se junta con el siguiente equipo
    if(numAgrupacion>0){ //Para que no se inserte el espacio antes del primer 
        
        agrupados.push_back(' ');
        agrupados.push_back(equipos[numAgrupacion]);
        AgruparBacktracking(equipos,agrupados,cantEquipos,numAgrupacion+1);
    }
    
}

void ImprimirVector(vector<char>agrupados){
    
    for(char a:agrupados){
        cout<<a;
    }
    cout<<endl;
}