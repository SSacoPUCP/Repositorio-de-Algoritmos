#include <iostream>
#include <iomanip>
#include <cstring>
#define N 9
#define M 5
using namespace std;

bool RecorridoRobot(char minas[][M],char pos,int posX,int posY);
void ImprimirMatriz(char minas[][M],int ejeY,int ejeX);
int main(int argc, char** argv) {
    char minas[N][M]={{' ',' ',' ',' ','*'},
                                  {' ',' ',' ',' ',' '},
                                  {' ',' ','*',' ',' '},
                                  {' ',' ',' ',' ',' '},
                                  {' ','*','*',' ','*'},
                                  {' ','*','*',' ','*'},
                                  {' ','*',' ','*',' '},
                                  {'*','*','*','*',' '},
                                  {' ',' ',' ',' ',' '}};
    minas[0][0]='A';
    bool solucion=RecorridoRobot(minas,'B',0,0);
    ImprimirMatriz(minas,N,M);
    return 0;
}

bool RecorridoRobot(char minas[][M],char pos,int posX,int posY){
    if(posX==M-1 and posY==N-1){  //Llego al final
        minas[posY][posX]=pos;
        return true;
    }
    
    
    //Movimientos posibles 
    int movX[8] = {1, 0, 1, -1, 0, -1, 1, -1};
    int movY[8] = {0, 1, 1, 0, -1, -1, -1, 1};
    
    for(int i=0;i<8;i++){
        int nuevoX=posX+movX[i];
        int nuevoY=posY+movY[i];
        
        //Verificamos que el movimiento sea valido 
        if(0<=nuevoX and nuevoX<M and 0<=nuevoY and nuevoY<N){
            //Esta adentro del tablero
            if(minas[nuevoY][nuevoX]==' ' ){ //La posicion a la que se movio no tiene una mina
                minas[nuevoY][nuevoX]=pos;
                if(RecorridoRobot(minas,pos+1,nuevoX,nuevoY)){
                    return true;
                }
                minas[nuevoY][nuevoX]=' ';
            }
        }
    }
    
    return false;
    
    
}

void ImprimirMatriz(char minas[][M],int ejeY,int ejeX){
    for(int i=0;i<ejeY;i++){
        for(int j=0;j<ejeX;j++){
            cout<<setw(2)<<minas[i][j]<<' ';
        }
        cout<<endl;
    }
}