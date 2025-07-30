#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <csignal>

using namespace std;

struct Nodo{
    int elemento;
    Nodo *siguiente;
};

struct Lista{
    int longitud;
    Nodo *cabeza;
};

struct Pila{
    Lista lista;
};
void ConstruirPila(Pila &pila);
void ConstruirLista(Lista &lista);
void ProcesarInstrucciones(Pila &pila,char *instrucciones,int n);
bool esPilaVacia(Pila &pila);
bool esListaVacia(Lista &lista);
void Apilar(Pila &pila,int elemento);
int Desapilar(Pila &pila);
int Cima(Pila &pila);
int RetornarCabeza(Lista &lista);
void EliminarCabeza(Lista &lista);
void IngresarAlInicio(Lista &lista,int elemento);

int main(int argc, char** argv){
    int i=0,validar=1;
    char instrucciones[10];
    while(validar==1 and i<10){
        cout<<"Ingrese si el submarino sube(s) o baja(b): "<<endl;
        cin>>instrucciones[i];
        cout<<"Instrucciones: ";
        for(int k=0;k<=i;k++) cout<<instrucciones[k]<<' ';
        cout<<endl;
        cout<<"Desea ingresar otra instruccion si(1),no(0)"<<endl;
        cin>>validar;
        i++;
        system("cls");
    }
    Pila pila;
    ConstruirPila(pila);
    cout<<"Instrucciones del submarino: "<<endl;
    for(int j=0;j<i;j++)cout<<instrucciones[j]<<' ';
    cout<<endl;
    ProcesarInstrucciones(pila,instrucciones,i);
}

void ConstruirPila(Pila &pila){
    ConstruirLista(pila.lista);
}

void ConstruirLista(Lista &lista){
    lista.cabeza=nullptr;
    lista.longitud=0;
}

void ProcesarInstrucciones(Pila &pila,char *instrucciones,int n){
    int i=0;
    while(i<n){
        Apilar(pila,i+1);
        if(instrucciones[i]=='s'){
            while(!esPilaVacia(pila)){
                int elemento=Desapilar(pila);
                cout<<elemento<<' ';
                
            }
        }
        i++; 
    }
    Apilar(pila,i+1);
    while(!esPilaVacia(pila)){
                int elemento=Desapilar(pila);
                cout<<elemento<<' ';
            }
}

bool esPilaVacia(Pila &pila){
    return esListaVacia(pila.lista);
}

bool esListaVacia(Lista &lista){
    return lista.cabeza==nullptr;
}

void Apilar(Pila &pila,int elemento){
    IngresarAlInicio(pila.lista,elemento);
}

int Desapilar(Pila &pila){
    if(esPilaVacia(pila)){
        cout<<"No se puede desapilar, la pila esta vacia"<<endl;
        
    }else{
        int elemento=Cima(pila);
        EliminarCabeza(pila.lista);
        return elemento;
    }
}

int Cima(Pila &pila){
    if(esPilaVacia(pila)){
        cout<<"La pila esta vacia"<<endl;
        return -1;
    }else{
        return RetornarCabeza(pila.lista);
    }
}

int RetornarCabeza(Lista &lista){
    return lista.cabeza->elemento;
}

void EliminarCabeza(Lista &lista){
    Nodo *nodoEliminar=lista.cabeza;
    if(nodoEliminar!=nullptr){
        lista.cabeza=nodoEliminar->siguiente;
        delete nodoEliminar;
        lista.longitud--;
    }
}

void IngresarAlInicio(Lista &lista,int elemento){
    Nodo *nuevoNodo=new Nodo;
    nuevoNodo->elemento=elemento;
    nuevoNodo->siguiente=lista.cabeza;
    lista.cabeza=nuevoNodo;
    lista.longitud++;
    
}
