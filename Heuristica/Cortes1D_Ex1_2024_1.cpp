#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pedido{
    int id;
    int dimension;
    int cantidad;
    int ganancia;
};

bool Comparar(Pedido a, Pedido b);

int main(int argc, char** argv) {
    int longBarra=10;
    int cantBarras = 20;
    
    int cantPed=5;
    
    Pedido pedidos[]{{1,10,5,10},
                                {2,20,10,20},
                                {3,1,18,15},
                                {4,3,1,5},
                                {5,1,1,2}};
    
    int n=sizeof(pedidos)/sizeof(pedidos[0]);
    sort(pedidos,pedidos+n,Comparar);
    vector<int> sobra(cantBarras,longBarra);
    int ganancia=0;
    for(int i=0;i<cantPed;i++){
        for(int j=0;j<cantBarras and pedidos[i].cantidad>0;j++){
            
            while(pedidos[i].dimension<=sobra[j] and pedidos[i].cantidad>0){
                
            sobra[j]=sobra[j]-pedidos[i].dimension;
            pedidos[i].cantidad--;
            ganancia+=pedidos[i].ganancia;
            
            }
        }
            
    }
    
    cout<<"Ganancia total: "<<ganancia<<endl;
    for(int i=0;i<cantBarras;i++){
        cout<<"Para la barra "<<i+1<<" se desperdicio "<<sobra[i]<<endl;
    }
    return 0;
}

bool Comparar(Pedido a, Pedido b){
    double n = a.dimension;
    double m =b.dimension;
    
    return n>m;
}