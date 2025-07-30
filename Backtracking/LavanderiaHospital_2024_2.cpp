#include <iostream>
#include <iomanip>
#include <cstring>
#define N 7
#define M 5


using namespace std;

void BacktrackingLavadoras(int ropa[], int &maxPacientes, int &maxKg, int capacidad, 
        int posPac, int kgActuales, int pacActuales, int pacPiso, bool auxRopaLavada[], bool ropaLavada[]);
int ContarPacientes(int ropa[]);

int main(int argc, char** argv) {
    int ropa[M][N]={{14,11,10,19,14,11,0},
                            {20,11,11,10,15,17,8},
                            {15,16,15,16,0,0,0},
                            {11,4,19,12,10,0,0},
                            {18,12,0,0,0,0,0}};
    
    int precios[M]={5,6,8,5,9};
    int capLavadora=50;
    int totalLavadoras=0;
    
    //Para el piso que mas espacio ocupa de la lavadora
    int maxOcupa=0;
    int pisoMaxOcupa=0;
    
    //Para el piso que menos espacio ocupa de su lavadora
    int minOcupa=99999;
    int pisoMinOcupa=0;
    
    //Pisos con mas y menos ropa a lavara por parientes
    int maxParientes=0;
    int minParientes=9999;
    int ropaLavParientes=0;
    int pisoMaxParientes=0;
    int pisoMinParientes=0;
    
    for(int i=0;i<M;i++){
        
        int maxPacientes=0;//Al maximizar pacientes se minimizan costes (Aquellos con mas ropa deberan lavarla ellos) se la ropa de mas pacientes
        int maxKg=0; //Debemos maximizar para aprovechar la lavadora
        int pacPiso=ContarPacientes(ropa[i]);
        
        bool auxRopaLavada[pacPiso]={false};
        bool ropaLavada[pacPiso]={false};  
        BacktrackingLavadoras(ropa[i],maxPacientes,maxKg,capLavadora,0,0,0,pacPiso, auxRopaLavada, ropaLavada);
        int precioPiso=precios[i]*maxKg;
        cout<<"En el piso " <<i+1<<" se cobra "<<precioPiso<<" por "<<maxKg<<" en "<<maxPacientes<<" pacientes."<<endl;
        
        //Imprimimos aquellos pacientes que tendran que lavar su ropa 
        for(int j=0;j<pacPiso;j++){
            if(!ropaLavada[j]){
                
                cout<<"El paciente "<<j+1<<" tendra que lavar su ropa"<<endl;
                
                //Vamos a colar la parte para la d
                //En esta parte del condicional estan todos los que sus parientes deben lavar su ropa
                ropaLavParientes+=ropa[i][j]; //Ropa que deberan lavar los parientes
            }
        }
        
        //Hallamos el total que se ha guardado en las lavadoras
        totalLavadoras+=maxKg;
        
        //Esto es para guardar el piso que mas ocupa
        if(maxKg>maxOcupa){
            maxOcupa=maxKg;
            pisoMaxOcupa=i+1;
        }
        
        if(maxKg<minOcupa){
            minOcupa=maxKg;
            pisoMinOcupa=i+1;
        }
        
        if(maxParientes<ropaLavParientes){
            maxParientes=ropaLavParientes;
            pisoMaxParientes = i+1;
         }
        
        if(minParientes>ropaLavParientes){
            minParientes=ropaLavParientes;
            pisoMinParientes= i+1;
        }
    }
    
    //El total de la capacidad de todas las lavadoras es 50(cap) * 5(N) = 250
    int totalCap=capLavadora*M;
    double porcentajeLav= ((double)totalLavadoras/(double)totalCap)*100;
    cout<<endl<<"El porcentaje ocupado de las lavadoras es del "<<porcentajeLav<<" %"<<endl<<endl;
    
    
    //Piso que mas ocupa en la lavadora
    cout<<"El piso que mas espacio ocupa de su lavadora es el "<<pisoMaxOcupa<<endl; //Con un arreglo se pueden imprimir todas las soluciones (me da pereza xd)
    
    //Piso que menos ocupa en la lavadora
    cout<<"El piso que menos espacio ocupa de su lavadora es el "<<pisoMinOcupa<<endl;
    
    
    //Pisos con mas y menos ropa por lavar por los parientes
    cout<<"El piso que mas ropa por lavar por sus parientes es el "<<pisoMaxParientes<<endl; 
    
    //Piso que menos ocupa en la lavadora
    cout<<"El piso que mas ropa por lavar por sus parientes es el "<<pisoMinParientes<<endl;
    return 0;
}

void BacktrackingLavadoras(int ropa[], int &maxPacientes, int &maxKg, int capacidad, 
        int posPac, int kgActuales, int pacActuales, int pacPiso, bool auxRopaLavada[], bool ropaLavada[]){
    if(kgActuales>capacidad){
        return; //Se excede la capacidad de la lavadora
    }
    
    if(posPac==pacPiso){ //Caso base
        if(pacActuales>maxPacientes or (maxPacientes==pacActuales and maxKg<kgActuales)){ //Si hay mas pacientes debemos verificar que sea el peso maximo
            for(int i=0;i<posPac;i++){
                //Gurdamos la combinacion en el arreglo
                ropaLavada[i]=auxRopaLavada[i];
            }
            maxKg=kgActuales;
            maxPacientes=pacActuales;
        }
        return;
        
    }
    
    
    //Con esto probamos cada posibilidad (tomar o no al paciente)
    //Tomamos al paciente
    auxRopaLavada[posPac]=true;
    BacktrackingLavadoras(ropa,maxPacientes,maxKg,capacidad,posPac+1,kgActuales+ropa[posPac],pacActuales+1,pacPiso, auxRopaLavada, ropaLavada);
    
    //No tomamos al paciente
    auxRopaLavada[posPac]=false;
    BacktrackingLavadoras(ropa,maxPacientes,maxKg,capacidad,posPac+1,kgActuales,pacActuales,pacPiso, auxRopaLavada, ropaLavada);

}

int ContarPacientes(int ropa[]) {
    int i = 0;
    while (i < N && ropa[i] != 0) i++;
    return i;
}

