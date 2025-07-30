#include <iostream>
#include <iomanip>
#include <vector>
#define N 5

using namespace std;

void BubbleSort(vector<int>&valores,vector<int>&pesos,vector<double>&proporciones);

int main(int argc, char** argv) {
    vector<int>valores={20,30,66,40,60};
    vector<int>pesos={10,20,30,40,50};
    vector<double>proporciones(N,0);
    vector<double>tomados(N,0);
    double valor=0;
    int capacidad=100;
    for(int i=0;i<N;i++){
        proporciones[i]=static_cast<double>(valores[i])/pesos[i]; //Arriba lo que quiero maximizar y abajo lo que quiero minimizar    
    }
    
    BubbleSort(valores,pesos,proporciones);
    for(int i=0;i<N;i++){
        if(capacidad>pesos[i]){
            tomados[i]=1;
            capacidad=capacidad-pesos[i];
            valor+=valores[i];
        }else{
            //Significa que no entra el objeto completo
            tomados[i]=static_cast<double>(capacidad)/pesos[i];
            valor+=valores[i]*tomados[i];
            break;
        }
    }
    
    for(int i=0;i<N;i++){
        cout<<"Valor: "<<valores[i]<<" Pesos"<<pesos[i]<<"K = "<<proporciones[i]<<endl;
    }
    cout<<"Se tomo en total: "<<valor<<endl;
    
    
    return 0;
}


void BubbleSort(vector<int>&valores,vector<int>&pesos,vector<double>&proporciones){
    
    for(int i=0;i<N-1;i++){
        for(int j=0;j<N-i-1;j++){
            if(proporciones[j]<proporciones[j+1]){
                double tmpProp=proporciones[j];
                proporciones[j]=proporciones[j+1];
                proporciones[j+1]=tmpProp;
                
                int tmp=valores[j];
                valores[j]=valores[j+1];
                valores[j+1]=tmp;
                
                tmp=pesos[j];
                pesos[j]=pesos[j+1];
                pesos[j+1]=tmp;
            }
        }
    }
}
