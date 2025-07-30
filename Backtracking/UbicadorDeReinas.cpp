#include <iostream>
#include <iomanip>
#include <vector> //Se pueden usar arreglos tambien
#define N 8

using namespace std;


bool UbicarReinas(int tablero[][8], vector<bool>& filasOcup, vector<bool> &columnasOcup, vector<bool>&diagCrecOcup,
            vector<bool> &diagDecrOcup, int columna);
void ImprimirTablero(int tablero[][8]);


int main(int argc, char** argv) {
    
    int tablero[8][8]={{0}}; //Para  no hacer la matriz entera
    
    //Para no llenarse de arreglos (Vectores booleanos)
    vector<bool> filasOcup(8,false);  //Horizontal
    vector<bool> columnasOcup(8,false); //Vertical
    vector<bool> diagCrecOcup(15,false); //Diagonal creciente
    vector<bool> diagDecrOcup(15,false); //Diagonal decreciente
    
    
    bool solucion=UbicarReinas(tablero,filasOcup,columnasOcup,diagCrecOcup,diagDecrOcup,0);
    if(solucion){
        ImprimirTablero(tablero);
    }else{
        cout<<"No se encontro solucion";
    }
    return 0;
}


bool UbicarReinas(int tablero[][8], vector<bool>& filasOcup, vector<bool> &columnasOcup, vector<bool>&diagCrecOcup,
            vector<bool> &diagDecrOcup, int columna){
    if(columna==8){
        return true;  //Caso base todas las reinas fueron colocadas
    }
    
    for(int fila = 0; fila<8;fila++){
        //Antes de colocar la reina comprobamos que la fila,columna y diagonales estan desocupadas
        if(!filasOcup[fila] and !columnasOcup[columna] and !diagCrecOcup[fila+columna] and 
                !diagDecrOcup[fila-columna+7]){
            tablero[fila][columna]=1;
            filasOcup[fila]=true;
            columnasOcup[columna]=true;
            diagCrecOcup[fila+columna]=true; //Si contamos las diagonales desde (0,0) como la primera hasta (7,7) como la ultima, hay 14 
            diagDecrOcup[fila-columna +7] =true;
            
            
            if(UbicarReinas(tablero,filasOcup,columnasOcup,diagCrecOcup,diagDecrOcup,columna+1)){
                return true;
            }
            
            //Si no se puede colocar, la descolocamos
            tablero[fila][columna]=0;
            filasOcup[fila]=false;
            columnasOcup[columna]=false;
            diagCrecOcup[fila+columna]=false; //Si contamos las diagonales desde (0,0) como la primer hasta (7,7) como la ultima hay 14 
            diagDecrOcup[fila-columna +7] =false;
        }  
        
    }
    
    return false;
        
}

void ImprimirTablero(int tablero[][8]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<setw(2)<<tablero[i][j]<<" ";
        }
        cout<<endl;
    }
}

