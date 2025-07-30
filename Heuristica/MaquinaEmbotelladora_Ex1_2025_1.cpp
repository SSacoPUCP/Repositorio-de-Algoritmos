#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#define M 5
#define N 20
using namespace std;

struct Orden{
    int id;
    int cant;
    //Tipo embotellado nunca se usa
};

struct Linea{
    int id;
    double total;
    vector<int> asignados;
    vector<int> ordenCant;
    
};
bool Compara(Orden a, Orden b);

int main(int argc, char** argv) {
    vector<Orden>ordenes={{1,103},
                    {2,58},
                    {3,88},
                    {4,126},
                    {5,195},
                    {6,90},
                    {7,54},
                    {8,195},
                    {9,124},
                    {10,113},
                    {11,193},
                    {12,55},
                    {13,97},
                    {14,97},
                    {15,169},
                    {16,50},
                    {17,167},
                    {18,74},
                    {19,79},
                    {20,109}};
    vector<Linea>lineas={{1,0},
                         {2,0},
                         {3,0},
                         {4,0},
                         {5,0}};
    //Debo ordenar de menor a mayor
    
    
    int n=ordenes.size();
    sort(ordenes.begin(),ordenes.begin()+n,Compara); //desc
    //Calculamos el tiempo por orden
    vector<double>tiempo(N,0);
    //Las 4 maquinas estan en una misma linea
    double l=2.0; //Llenadora de liquido
    double g=1.0; //Gasificadora
    double t=1.5; //Tapadora
    double e=1.5; //Etiquetadora
    
    //Calculamos el tiempo de cada orden al pasar por una linea
    for(int i=0;i<n;i++){
        //int id= ordenes[i].id;
        int c=ordenes[i].cant;
        double valor= c*l + c*g + c*t + c*e;
        tiempo[i]=valor;
    }
    
    vector<double>tiemposLinea(M,0);
    int m=tiemposLinea.size();
    for(int i=0;i<n;i++){
        //Vamos a asignarle cada orden a una linea
        //A la que este menos ocupada
        double time=tiempo[i];
        int numLinea = min_element(tiemposLinea.begin(),tiemposLinea.begin()+M) - tiemposLinea.begin();
        tiemposLinea[numLinea]+=time; //Actualizamos el tiempo de trabajo de esa maquina
        lineas[numLinea].total+=time;
        lineas[numLinea].asignados.push_back(ordenes[i].id);
        lineas[numLinea].ordenCant.push_back(ordenes[i].cant);
        
    }
    
    //Ya estan todas las ordenes asignadas
    cout<<"Lineas       Ordenes                                    Carga(minutos)"<<endl;
    for(int i=0;i<tiemposLinea.size();i++){
        //Recorremos todas las maquinas
        cout<<"Linea "<<lineas[i].id<<"      ";
        int j=0;
        for(int a:lineas[i].asignados){
            //Imprime las ordenes
            cout<<"Orden "<<a<<" ("<<lineas[i].ordenCant[j]<<") ";
            j++;
        }
        cout<<"                   Total:"<<lineas[i].total<<endl;
    }
    
    int pos = max_element(tiemposLinea.begin(),tiemposLinea.begin()+M) - tiemposLinea.begin();
    cout<<"Tiempo acumulado: "<<tiemposLinea[pos];
    return 0;
}

bool Compara(Orden a, Orden b){
    int n=a.cant;
    int m=b.cant;
    return n>m;
}

