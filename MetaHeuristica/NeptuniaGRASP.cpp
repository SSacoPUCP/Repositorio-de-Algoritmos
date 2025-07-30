//Ejemplo de Heuristica (Neptunia) pasado a Grasp
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

struct Paquete{
    int id;
    int ganancia;
    int peso;
};

void Grasp(Paquete *paquetes,int n,int capacidad, int iteraciones, double alfa);
vector<Paquete> ConstruirSolucion(Paquete *paquetes,int n,int capacidad,double alfa);
bool Compara(Paquete a, Paquete b);

int main(int argc, char** argv) {
    Paquete paquetes[]{{1,10,2},
                                {2,15,3},
                                {3,10,5},
                                {4,14,12},
                                {5,8,2},
                                {6,5,5}};
    int n=sizeof(paquetes)/sizeof(paquetes[0]);
    int capacidad=20;
    Grasp(paquetes,n,capacidad,100,0.3); //100 Iteraciones y 0.3 de alfa
    
                                
    
    return 0;
}

void Grasp(Paquete *paquetes,int n,int capacidad, int iteraciones, double alfa){
    
    srand(time(0));
    vector<Paquete>mejorSol;
    double  mejorGanancia=0;
    
    for(int i=0; i<iteraciones; i++){
        vector<Paquete> solu = ConstruirSolucion(paquetes,n,capacidad,alfa); //Solucion combinacion de paquetes
        double ganancia=0;
        int peso=0;
        for(Paquete p : solu){
            ganancia += p.ganancia;
            peso += p.peso;
        }
        if(ganancia>mejorGanancia){
            mejorGanancia = ganancia;
            mejorSol = solu;
        }
    }
    
    
    cout<<"Mejor solucion con GRASP:  "<<endl;
    for(Paquete p : mejorSol){
        cout<<"Paquete "<<p.id<<"(Ganancia: "<<p.ganancia<<", Peso: "<<p.peso<<")"<<endl;
    }
    int pesoTotal=0;
    for (Paquete p : mejorSol) pesoTotal += p.peso;
    
     cout << "Peso total usado: " << pesoTotal << " / " << capacidad << " Tn" << endl;
    cout << "Ganancia total: " << mejorGanancia << " en miles de dólares" << endl;
    
}

vector<Paquete> ConstruirSolucion(Paquete *paquetes,int n,int capacidad,double alfa){
    vector<Paquete> solu;
    vector<Paquete> candidatos(paquetes, paquetes+n);
    int pesoActual=0;
    double gananciaTotal=0;
    
    while(!candidatos.empty()){
        //Ordenamos los candidatos por ganancia/peso
        sort(candidatos.begin(), candidatos.end(),Compara);
        
        //Ahora establecemos el limite para LRC (lista restringida de candidatos)
        double mejor= 1.0 * candidatos[0].ganancia / candidatos[0].peso;
        double peor= 1.0 * candidatos.back().ganancia / candidatos.back().peso;
        double umbral = mejor - alfa * (mejor - peor);
        
        //LRC: contiene los paquetes con buena relacion ganancia/peso
        vector<Paquete>LRC;
        for(Paquete p : candidatos){
            double ratio = 1.0 * p.ganancia / p.peso;
            if(ratio>=umbral){
                LRC.push_back(p);
            }
        }
        if(LRC.empty())break;
        
        //Elegimos aleatoriamente uno de los LRC
        int r = rand() % LRC.size();
        Paquete elegido = LRC[r];
        
        if(pesoActual + elegido.peso <= capacidad){
            solu.push_back(elegido);
            pesoActual += elegido.peso;
            gananciaTotal += elegido.ganancia; 
        }
        
        //Eliminamos el paquete elegido de la lista de candidatos
        candidatos.erase(remove_if(candidatos.begin(),candidatos.end(),
                                                    [=](Paquete p){return  p.id == elegido.id;}),candidatos.end());
                                                    
                                                  
    }
    return solu;
}

bool Compara(Paquete a, Paquete b){
    double n=1.0 * a.ganancia/a.peso;
    double m=1.0 * b.ganancia/b.peso;
    return n>m;
}



