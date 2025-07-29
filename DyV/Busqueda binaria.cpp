#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15


int BusBin(int *num,int numPed,int inicio, int fin);

int main(int argc, char** argv){
    
    int num[N]={2,3,5,8,10,11,15,18,25,30};
    int numPed;
    cout<<"Ingresa el numero que desea buscar: "<<endl;
    cin>>numPed;
    int pos=BusBin(num,numPed,0,10-1);
    if(pos>0){
        cout<<"El numero buscado esta en la posicion "<<pos<<' ';
    }else{
        cout<<"El numero buscado no esta en el arreglo.";
    }
            
}

int BusBin(int *num,int numPed,int inicio, int fin){
    if(fin<inicio) return -1;
    int med=(fin+inicio)/2;
    if(num[med]==numPed)return med;
    if(num[med]>numPed){
        BusBin(num,numPed,inicio,med-1);
    }else{
        BusBin(num,numPed,med+1,fin);
    }
}
