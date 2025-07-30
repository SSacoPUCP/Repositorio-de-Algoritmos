#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#define N 30

using namespace std;

/*
 * 
 */

void SolucionesOperacion(char *ope,char *auxOpe,int longitud,int posOpe,int posNuevo,int balanceo);

int main(int argc, char** argv) {
    ifstream archivo("Operacion.txt",ios::in);
    char ope[N]{};
    int contador=0;
    
    while(!archivo.eof()){
        archivo>>ope[contador];
        contador++;
    }
    
    char auxOpe[N]{};
    int longitud=strlen(ope);
    
    SolucionesOperacion(ope,auxOpe,longitud,0,0,0);
    
    return 0;
}

void SolucionesOperacion(char *ope,char *auxOpe,int longitud,int posOpe,int posNuevo,int balanceo){
    
    if(posOpe==longitud){
        if(balanceo==0){
            //La solucion es valida
            for(int i=0;i<posNuevo;i++){
                cout<<auxOpe[i];
            }
            cout<<endl;
        }
        return;
    }
    
    char car=ope[posOpe];
    
    if(ope[posOpe]=='('){
        //Se puede agarrar
        auxOpe[posNuevo]=car;
        SolucionesOperacion(ope,auxOpe,longitud,posOpe+1,posNuevo+1,balanceo+1);
        //No se agarra
        auxOpe[posNuevo]=' '; //Esto no es necesario pq igual se reemplaza luego
        SolucionesOperacion(ope,auxOpe,longitud,posOpe+1,posNuevo,balanceo);
        
    }else if(ope[posOpe]==')'){
        
        //Se debe verificar que haya un ( antes (con el balanceo)
        if(balanceo>0){
            auxOpe[posNuevo]=car;
            SolucionesOperacion(ope,auxOpe,longitud,posOpe+1,posNuevo+1,balanceo-1);
        }else{//Sino se omite
            SolucionesOperacion(ope,auxOpe,longitud,posOpe+1,posNuevo,balanceo);
        }
    }else{
        //Cualquier otro valor no necesita verificacion
        auxOpe[posNuevo]=car;
        SolucionesOperacion(ope,auxOpe,longitud,posOpe+1,posNuevo+1,balanceo);
    }
    
    
}

