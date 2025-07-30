#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#define N 6
#define M 4
using namespace std;

struct Tabla{
    int id;
    int vel;
    vector<int>asignados;
};

struct Disco{
    int id;
    int vel;
    vector<int>asignados;

};

bool ComparaT(Tabla a, Tabla b);
bool ComparaD(Disco a, Disco b);
void ImprimirVector(vector<Disco>v);

int main(int argc, char** argv) {
    vector<Tabla>tablas={{1,150},
                                        {2,100},
                                        {3,180},
                                        {4,50},
                                        {5,120},
                                        {6,10}};
    
    vector<Disco>discos={{1,250},
                                        {2,200},
                                        {3,200},
                                        {4,100}};
    int t=tablas.size();
    int d=discos.size();
    
    sort(tablas.begin(),tablas.begin()+t,ComparaT);
    sort(discos.begin(),discos.begin()+d,ComparaD);
    
    for(int i=0;i<d;i++){
        for(int j=0;j<t;j++){
            if(discos[i].vel>=tablas[j].vel and tablas[j].vel!=0){
                //Si entra en el disco se agrega
                discos[i].vel-=tablas[j].vel;
                discos[i].asignados.push_back(tablas[j].id);
                tablas[j].vel=0;
            }
        }
    }
    ImprimirVector(discos);
    
    
    return 0;
}

bool ComparaT(Tabla a, Tabla b){
    int n=a.vel;
    int m=b.vel;
    return n>m;
}
bool ComparaD(Disco a, Disco b){
    int n=a.vel;
    int m=b.vel;
    return n>m;
}

void ImprimirVector(vector<Disco>v){
    
    for(Disco a:v){
        cout<<"El disco "<<a.id<<" tiene: ";
        for(int b:a.asignados){
            cout<<b<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}