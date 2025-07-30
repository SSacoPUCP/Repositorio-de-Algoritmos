#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstddef>

using namespace std;

struct Nodo{
    int elemento;
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

void CrearLista(Lista &lista);
void AgregarFinalLista(Lista &lista,int i);
struct Nodo *ObtenerUltimoNodo(Lista &lista);
void ImprimirLista(Lista &lista);
void EliminarMultiplos(Lista &lista,int dato);
void EliminarNodo(int dato,Lista &lista);
bool esPrimo(int dato);
void CrearCola(Cola &cola);
void AgregarElementoACola(Cola &cola,int valor);
bool esVacia(Lista &lista);

int main(int argc, char** argv) {
    Lista lista;
    CrearLista(lista);
    int n;
    cout<<"Ingrese un numero: ";
    cin>>n;
    cout<<endl;
    for(int i=2;i<=n;i++){
        AgregarFinalLista(lista,i);
    }
    cout<<"La lista en cuestion es: ";
    ImprimirLista(lista);
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        int dato=recorrido->elemento;
        if(esPrimo(dato)){
            cout<<"Numero procesado es: "<<dato<<endl;
            EliminarMultiplos(lista,dato);
        }
        recorrido=recorrido->siguiente;
    }
    cout<<"La lista final es: ";
    ImprimirLista(lista);
    
    return 0;
}

void CrearLista(Lista &lista){
    lista.cabeza=nullptr;
    lista.longitud=0;
    lista.cola=nullptr;
}

void AgregarFinalLista(Lista &lista,int i){
    Nodo *ultimo=ObtenerUltimoNodo(lista);
    Nodo *nuevoNodo=new Nodo;
    nuevoNodo->elemento=i;
    nuevoNodo->siguiente=nullptr;
    if(ultimo==nullptr){//La lista esta vacia
        lista.cabeza=nuevoNodo;
    }else{
        ultimo->siguiente=nuevoNodo;
    }
    lista.longitud++;
}

struct Nodo *ObtenerUltimoNodo(Lista &lista){
    Nodo *ultimo=nullptr;
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        ultimo=recorrido;
        recorrido=recorrido->siguiente;
    }
    return ultimo;
}

void ImprimirLista(Lista &lista){
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        cout<<recorrido->elemento;
        recorrido=recorrido->siguiente;
        (recorrido==nullptr)? cout<<".":cout<<",";
    }
    cout<<endl;
}

bool esPrimo(int dato){
    int cantDiv=0;
    for(int i=1;i<=dato;i++){
        if(dato%i==0)cantDiv++;
    }
    return (cantDiv==2)? true:false;
}

void EliminarMultiplos(Lista &lista,int dato){
    Nodo *recorrido=lista.cabeza;
    Cola cola;
    CrearCola(cola);
    
    
    cout<<"Numeros tachados para el  "<<dato<<": ";
    while(recorrido!=nullptr){
        int valor=recorrido->elemento;
        recorrido=recorrido->siguiente;
        if(valor!=dato){
            if(valor%dato==0){
                AgregarElementoACola(cola,valor);
                EliminarNodo(valor,lista);
            }
           
        }
         
    }
    if(!esVacia(cola.lista)){
        ImprimirLista(cola.lista);
    }else{
        cout<<"No tiene numeros tachados"<<endl;
    }
    
}

void EliminarNodo(int dato,Lista &lista){
    Nodo *ultimo=nullptr;
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr and recorrido->elemento!=dato){
        ultimo=recorrido;
        recorrido=recorrido->siguiente;
    }
    if(ultimo==nullptr){
        cout<<"La lista esta vacia asi que no se puede eliminar ningun nodo"<<endl;
    }else{
        ultimo->siguiente=recorrido->siguiente;
        delete recorrido;
        lista.longitud--;
    }
    
}

void CrearCola(Cola &cola){
    CrearLista(cola.lista);
}

void AgregarElementoACola(Cola &cola,int valor){
    AgregarFinalLista(cola.lista,valor);
}

bool esVacia(Lista &lista){
    return lista.cabeza==nullptr;
}