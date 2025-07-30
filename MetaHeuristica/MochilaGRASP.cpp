#include <iostream>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

struct Elemento{
    int id;
    int peso;
    int ganancia;
};

void Grasp(Elemento *elementos,int n,int capacidad,int iteraciones,double alfa);
bool Compara(Elemento a, Elemento b);

int main(int argc, char** argv) {
   Elemento elementos[]={{1,10,20},
                                        {2,6,30},
                                        {3,3,5},
                                        {4,5,25},
                                        {5,9,40},
                                        {6,8,18},
                                        {7,14,34},
                                        {8,20,10},
                                        {9,23,33},
                                        {10,17,50}};
   int n=sizeof(elementos)/sizeof(elementos[0]);
   int capacidad=41;
   Grasp(elementos,n,capacidad,100,0.3);
    return 0;
}

void Grasp(Elemento *elementos,int n,int capacidad,int iteraciones,double alfa){
    srand(0);
    vector<Elemento>mejorSolu;
    double mejorGanancia=0;
    
    for(int i=0; i<iteraciones;i++){
        vector<Elemento> solu;
        vector<Elemento> candidatos(elementos, elementos+n);
        
        int pesoActual=0;
        int gananciaActual=0;
        
        while(!candidatos.empty()){
            sort(candidatos.begin(), candidatos.end(),Compara);
            
            double mejor= 1.0 * candidatos[0].ganancia / candidatos[0].peso; 
            double peor= 1.0 * candidatos.back().ganancia / candidatos.back().peso; 
            double umbral = mejor - alfa * (mejor - peor); 
            
            //LRC: contiene los paquetes con buena relacion ganancia/peso
            vector<Elemento>LRC;
            for(Elemento e : candidatos){
                double ratio = 1.0 * e.ganancia/e.peso;
                if(ratio>=umbral){
                    LRC.push_back(e);
                }
            }
            
            if(LRC.empty())break;
            
            //Elegimos aleatoriamente de los LRC
            
            int r = rand()%LRC.size();
            Elemento elegido = LRC[r];
            
            //Una vez tomamos un elemento al azar de entre los mejores para tomar
            //Probamos si entra en la mochila
            if(pesoActual + elegido.peso<=capacidad){
                solu.push_back(elegido);
                pesoActual += elegido.peso;
                gananciaActual +=elegido.ganancia;
            }
            
            
            //Eliminamos el elemento que elegimos de la lista de candidatos
            candidatos.erase(remove_if(candidatos.begin(), candidatos.end(),
                                                                [=](Elemento e){return e.id == elegido.id;}), candidatos.end());                                                     
        }
        
        double ganancia=0;
        int peso=0;
        for(Elemento e: solu){
            ganancia+=e.ganancia;
            peso+=e.peso;
        }
        
        if(ganancia>mejorGanancia){
            mejorGanancia=ganancia;
            mejorSolu=solu;
        }
    }
    
    cout<<"Mejor solucion con GRASP:  "<<endl;
    for(Elemento p : mejorSolu){
        cout<<"Elemento "<<p.id<<"(Ganancia: "<<p.ganancia<<", Peso: "<<p.peso<<")"<<endl;
    }
    int pesoTotal=0;
    for (Elemento p : mejorSolu) pesoTotal += p.peso;
    
     cout << "Peso total usado: " << pesoTotal << " / " << capacidad << " Tn" << endl;
    cout << "Ganancia total: " << mejorGanancia << " en miles de dólares" << endl;
        
    
}

bool Compara(Elemento a, Elemento b){
    double n=1.0 * a.ganancia/a.peso;
    double m=1.0 * b.ganancia/b.peso;
    return n>m;
}