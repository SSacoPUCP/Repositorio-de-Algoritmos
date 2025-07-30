#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Orden{
    int id;
    char tipo;
    int cant;
};

bool Compara(Orden a, Orden b);

int main(int argc, char** argv) {
    Orden ordenes[]={{1,'l',10},
                     {2,'l',10},
                     {3,'s',8},
                     {4,'l',15},
                     {5,'s',9},
                     {6,'s',11},
                     {7,'l',12},
                     {8,'s',15},
                     {9,'l',6},
                     {10,'s',10},
                     {11,'l',8},
                     {12,'s',15},
                     {13,'l',11},
                     {14,'l',7},
                     {15,'l',7},
                     {16,'s',8},
                     {17,'l',9},
                     {18,'l',11},
                     {19,'s',12},
                     {20,'l',15}};
    int cantLav=5;
    
    //tiempo por lavadora
    vector<int>tiempo(cantLav,0);
    
    
    int n=sizeof(ordenes)/sizeof(ordenes[0]);
    
    //Debo ordenar por las que menos tiempo toman ASC
    sort(ordenes,ordenes+n,Compara);

    
    vector<double>total(n,0); //Vector de tiempo ascendente
    vector<vector<int>>asignadas(cantLav,vector<int>());
    
    for(int i=0;i<n;i++){
        if(ordenes[i].tipo=='l'){
            total[i]=((double)ordenes[i].cant/5)*20;
        }else{
            total[i]=((double)ordenes[i].cant/5)*10;
        }
    }
    
    for(int i=0;i<n;i++){
        //Debemos asignarle cada tiempo a la lavadora menos ocupada
        int lavMin= *min_element(tiempo.begin(),tiempo.begin()+cantLav); //Obtenemos el valor de la lavadora menos ocuapada
        int pos;
        for(int j=0;j<cantLav;j++){
            if(tiempo[j]==lavMin){
                pos=j;
                break;
            }
        }
        asignadas[pos].push_back(i+1);
        tiempo[pos]+=total[i]; //Se le asigna la tarea a la lavadora
        
    }
    
    for(int i=0;i<cantLav;i++){
        cout<<"La lavadora "<<i+1<<" tardo "<<tiempo[i]<<" y se le asigno ";
        for(int j=0;j<asignadas.size()-1;j++){
            cout<<asignadas[i][j]<<" ";
        }
        cout<<endl;
    }
    int maxTiempo=*max_element(tiempo.begin(),tiempo.begin()+cantLav);
    cout<<"El tiempo que tardaran en completar todas las tareas es: "<<maxTiempo<<endl;
    
    return 0;
}

bool Compara(Orden a, Orden b){
    double n;
    double m;
    if(a.tipo=='l'){
        n=(a.cant/5)*20;
    }else{
        n=(a.cant/5)*10;
    }
    
    if(b.tipo=='l'){
        m=(b.cant/5)*20;
    }else{
        m=(b.cant/5)*10;
    }
    return n>m;
}

