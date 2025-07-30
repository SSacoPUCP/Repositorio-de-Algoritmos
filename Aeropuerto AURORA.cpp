#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <csignal>

using namespace std;

struct Nodo{
    int numVuelo;
    int horaLlegada;
    int nuevaHoraLlegada;
    Nodo *siguiente;
};

struct Lista{
    int longitud;
    Nodo *cabeza;
    Nodo *cola;
};

struct Cola{
    Lista lista;
};

void ConstruirCola(Cola &cola);
void ConstruirLista(Lista &lista);
void LeerDatos(Cola &cola);
int ConvertirHora(int hora,int min);
void AperturaArchivosLeer(ifstream &archVuelos,const char *nomb);
void Encolar(Cola &cola,Nodo *nuevoNodo);
void AgregarNodoFinalLista(Lista &lista,Nodo *nuevoNodo);
Nodo *EncontrarUltimo(Lista &lista);
void ImprimirCola(Cola &cola);
Nodo *Desencolar(Cola &cola);
bool esColaVacia(Cola &cola);
Nodo *RetornarCabeza(Lista &lista);
void EliminarCabeza(Lista &lista);
bool esListaVacia(Lista &lista);
void OrdenarCola(Cola &cola);
void  ActualizarCola(Cola &cola);

int main(int argc, char** argv){
    Cola cola;
    ConstruirCola(cola);
    LeerDatos(cola);
    ImprimirCola(cola);
    OrdenarCola(cola);
    cout<<"HORA LLEGADA: "<<endl<<endl;
    cout<<"Avion  Hora llegada  Nueva hora llegada"<<endl;
    ImprimirCola(cola);
    ActualizarCola(cola);
    OrdenarCola(cola);
    cout<<"NUEVA HORA LLEGADA: "<<endl<<endl;
    cout<<"Avion  Hora llegada  Nueva hora llegada"<<endl;
    ImprimirCola(cola);    

}

void ConstruirCola(Cola &cola){
    ConstruirLista(cola.lista);
}

void ConstruirLista(Lista &lista){
    lista.cabeza=nullptr;
    lista.cola=nullptr;
    lista.longitud=0;
}

void LeerDatos(Cola &cola){
    ifstream archVuelos;
    AperturaArchivosLeer(archVuelos,"Horario.csv");
    int numVuelo,hora,min,nuevaHora,nuevoMin;
    int horaLlegada,nuevaHoraLlegada;
    char c;
    while(1){
        archVuelos>>numVuelo;
        if(archVuelos.eof())break;
        archVuelos>>c>>hora>>c>>min>>c>>nuevaHora>>c>>nuevoMin;
        horaLlegada=ConvertirHora(hora,min);
        nuevaHoraLlegada=ConvertirHora(nuevaHora,nuevoMin);
        Nodo *nuevoNodo= new Nodo;
        nuevoNodo->numVuelo=numVuelo;
        nuevoNodo->horaLlegada=horaLlegada;
        nuevoNodo->nuevaHoraLlegada=nuevaHoraLlegada;
        nuevoNodo->siguiente=nullptr;
        Encolar(cola,nuevoNodo);
        
    }
}

int ConvertirHora(int hora,int min){
    return hora*100+min;
}

void AperturaArchivosLeer(ifstream &archVuelos,const char *nomb){
    archVuelos.open(nomb,ios::in);
    if(!archVuelos){
        cout<<"Error no se pudo abrir el archivo"<<endl;
        exit(1);
    }
}

void Encolar(Cola &cola,Nodo *nuevoNodo){
    AgregarNodoFinalLista(cola.lista,nuevoNodo);
}

void AgregarNodoFinalLista(Lista &lista,Nodo *nuevoNodo){
    Nodo *ultimo=EncontrarUltimo(lista);
    if(ultimo==nullptr){
        nuevoNodo->siguiente=lista.cabeza;
        lista.cabeza=nuevoNodo;
    }else{
        ultimo->siguiente=nuevoNodo;
    }
    lista.cola=nuevoNodo;
    lista.longitud++;
}

Nodo *EncontrarUltimo(Lista &lista){
    Nodo *ultimo=nullptr;
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        ultimo=recorrido;
        recorrido=recorrido->siguiente;
    }
    return ultimo;
}


void ImprimirCola(Cola &cola){
    int cant=cola.lista.longitud;
    for(int i=0;i<cant;i++){
        Nodo *nodoImprimir=Desencolar(cola);
        int horaLlegada=nodoImprimir->horaLlegada/100;
        int minLlegada=nodoImprimir->horaLlegada%100;
        int nuevaHLlegada=nodoImprimir->nuevaHoraLlegada/100;
        int nuevaMLlegada=nodoImprimir->nuevaHoraLlegada%100;
        cout<<nodoImprimir->numVuelo<<setw(10)<<horaLlegada<<':'<<minLlegada<<
                setw(10)<<nuevaHLlegada<<':'<<nuevaMLlegada<<endl;;

        Encolar(cola,nodoImprimir);
    }
}

Nodo *Desencolar(Cola &cola){
    if(esColaVacia(cola)){
        cout<<"La cola no tiene elementos"<<endl;
        return nullptr;
    }else{
        Nodo *nodoDesencolado=RetornarCabeza(cola.lista);
        cola.lista.cabeza=cola.lista.cabeza->siguiente;
        nodoDesencolado->siguiente=nullptr;
        cola.lista.longitud--;
        return nodoDesencolado;
    }
    
}

bool esColaVacia(Cola &cola){
    return esListaVacia(cola.lista);
}

Nodo *RetornarCabeza(Lista &lista){
    return lista.cabeza;
}

void EliminarCabeza(Lista &lista){
    Nodo *nodoEliminar=lista.cabeza;
    if(esListaVacia(lista)){
        cout<<"La lista esta vacia"<<endl;
    }else{
        lista.cabeza=lista.cabeza->siguiente;
        delete nodoEliminar;
        lista.longitud--;
    }
}

bool esListaVacia(Lista &lista){
    return lista.cabeza==nullptr;
}

void OrdenarCola(Cola &cola){
    int n=cola.lista.longitud;
    for(int i=0;i<n;i++){
        Nodo *maxNodo=nullptr;
        int tamActual=n-i;
        for(int j=0;j<tamActual;j++){
            Nodo *elemento=Desencolar(cola);
            if(maxNodo==nullptr or elemento->nuevaHoraLlegada>maxNodo->nuevaHoraLlegada){
                maxNodo=elemento;
            }
            Encolar(cola,elemento);
        }
        bool encontrado=false;
        for(int k=0;k<n;k++){
            Nodo *elemento=Desencolar(cola);
            if(elemento->nuevaHoraLlegada==maxNodo->nuevaHoraLlegada and encontrado==false){
                encontrado==true;
            }else{
                Encolar(cola,elemento);
            }
            
        }
        Encolar(cola,maxNodo);
            for(int l=0;l<i;l++){
                Nodo *elemento=Desencolar(cola);
                Encolar(cola,elemento);
            }
        
        
    }
}

void  ActualizarCola(Cola &cola){
    ifstream archCorreccion;
    AperturaArchivosLeer(archCorreccion,"Correccion.csv");
    int n=cola.lista.longitud;
    int numVueloAct,horaLlegadaAct,minLlegadaAct,horaNuevaAct,minNuevaAct;
    int nuevaHora;
    char c;
    while(1){
        archCorreccion>>numVueloAct;
        if(archCorreccion.eof())break;
        archCorreccion.get();
        archCorreccion>>horaLlegadaAct>>c>>minLlegadaAct>>c>>horaNuevaAct>>c>>minNuevaAct;
        nuevaHora=ConvertirHora(horaNuevaAct,minNuevaAct);
        
        for(int i=0;i<n;i++){
            Nodo *elemento=Desencolar(cola);
            if(elemento->numVuelo==numVueloAct){
                elemento->nuevaHoraLlegada=nuevaHora;
            }
            Encolar(cola,elemento);
        }
   
    }
}