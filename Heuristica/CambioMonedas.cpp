#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char** argv) {
    
    vector<double>monedas={0.1,0.2,0.5,2,1,5};
    vector<double>usadas(6,0);
    
    int monto=100;
    sort(monedas.begin(),monedas.end(),greater<double>());
    
    while(monto!=0){
        for(int i=0;i<6;i++){
            if(monedas[i]<=monto){
                usadas[i]=monto/monedas[i];
                monto=monto-usadas[i]*monedas[i];
            }
        }
    }
    
    for(int i=0;i<6;i++){
        cout<<"Se usaron "<<usadas[i]<<" monedas de "<<monedas[i]<<endl;
    }
    
    
    
    return 0;
}

