#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Proyecto{
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int>predecesores;
};

int Selecciona(Proyecto *proyectos,int n,int presupuesto);
bool Compara(Proyecto a, Proyecto b);
bool Verificar(Proyecto proyectos, vector<Proyecto>solucion);

int main(int argc, char** argv) {
    Proyecto proyectos[]={
        {1,80,150,2,{}},
        {2,20,80,4,{4}},
        {3,100,300,1,{1,2}},
        {4,100,150,4,{}},
        {5,50,80,2,{}},
        {6,10,50,1,{2}},
        {7,50,120,2,{6}},
        {8,50,150,4,{6}}
    };
    
    int presupuesto=250;
    int n=sizeof(proyectos)/sizeof(proyectos[0]);
    
    cout<<endl<<"Ganancia: "<< Selecciona(proyectos,n,presupuesto);
    return 0;
}

int Selecciona(Proyecto *proyectos,int n,int presupuesto){
    int i=0,total=0,ganancia=0;
    vector<Proyecto>solucion;
    vector<Proyecto>cartera;
    
    sort(proyectos, proyectos+n,Compara);
    cartera.insert(cartera.begin(),proyectos,proyectos+n);
    
    while(cartera.size()>0 and total<presupuesto and i<cartera.size()){
        if(Verificar(cartera[i],solucion) and total+cartera[i].costo<=presupuesto){
            total+=cartera[i].costo;
            ganancia+=cartera[i].ganancia;
            solucion.push_back(cartera[i]);
            cartera.erase(cartera.begin()+i);
            i=0;
        }else{
            i++;
        }
    }
    for(int i=0;i<solucion.size();i++){
        cout<<solucion[i].id<<" ";
    }
    return ganancia;
}

bool Compara(Proyecto a, Proyecto b){
    double n=1.0 * a.beneficio * a.ganancia / a.costo; 
    double m=1.0 * b.beneficio * b.ganancia / b.costo;
    return n>m;
}

bool Verificar(Proyecto proyectos, vector<Proyecto>solucion){
    int cont=0;
    
    if(!proyectos.predecesores.size())return true;
    for(int i=0;i<proyectos.predecesores.size();i++){
        for(int j=0;j<solucion.size();j++){
            if(proyectos.predecesores[i]==solucion[j].id)cont++;
        }
    }
    return cont==proyectos.predecesores.size();
}