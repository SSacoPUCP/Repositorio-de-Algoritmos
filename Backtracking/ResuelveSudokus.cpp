#include <iostream>
#include <iomanip>
#include <cstring>
#define N 8
using namespace std;

bool RecorridoCaballo(int tablero[][8],int x,int y,int movNum);

int main(int argc, char** argv) {
        
    //Representamos el tablero
    
    int tablero[8][8]={{0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0}};
    
    tablero[0][0]=1;
    bool solucion=RecorridoCaballo(tablero,0,0,2);
    if (solucion) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout <<setw(2)<< tablero[i][j]<<" ";
            }
            cout << endl;
        }
    }else {
        cout << "No se encontro solucion";
    }
    return 0;
}

bool RecorridoCaballo(int tablero[][8],int x,int y,int movNum){
    if(movNum==N*N+1){
        return true; //Caso base
    }
    
    //Movimientos posibles
    int movX[8]={2,1,-1,-2,-1,1,-2,2};
    int movY[8]={1,2,2,1,-2,-2,-1,-1};
    
    for(int i=0;i<8;i++){
        int nuevoX=x+movX[i];
        int nuevoY=y+movY[i];
        
        //Verificamos que el movimiento sea valido
        if(0<=nuevoX and nuevoX<N and 0<=nuevoY and nuevoY<N){
            if(tablero[nuevoY][nuevoX]==0){ //No visitado
                tablero[nuevoY][nuevoX]=movNum; //Marcar casilla
                if(RecorridoCaballo(tablero,nuevoX,nuevoY,movNum+1)){
                    return true;
                }
                tablero[nuevoY][nuevoX]=0;
            }
        }
    }
    return false;
    
}
