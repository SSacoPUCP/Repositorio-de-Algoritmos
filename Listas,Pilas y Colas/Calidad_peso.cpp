#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;


struct Nodo{
    int peso;
    int calidad;
    Nodo *siguiente;
};

struct Lista{
    int longitud;
    Nodo *cabeza;
};

struct Pila{
    Lista lista;
};

void ConstruirLista(Lista &lista);
void LeerDatosEIngresarEnLista(Lista &lista);
void AperturaArchivosLeer(ifstream &archDatos,const char *nomb);
void IngresarInicioLista(int peso,int calidad,Lista &lista);
void IngresarListaEnPila(Pila &pila,Lista &lista);
int PosicionEnPila(int calidad,int peso,Pila &pila);
void Hanoi(Pila &origen,Pila &destino,Pila &aux,int n);
Nodo *cima(Pila &origen);
void EliminarCabeza(Lista &lista);
void apilarNodo(int peso,int calidad,Pila &destino);
void ConstruirPila(Pila &pila);
void ImprimirLista(Lista &lista);

int main(int argc, char** argv){
    
    Lista lista;
    Pila pila;
    ConstruirLista(lista);
    LeerDatosEIngresarEnLista(lista);
    ImprimirLista(lista);
    ConstruirPila(pila);
    IngresarListaEnPila(pila,lista);
    cout<<"La pila ordenada es: "<<endl;
    ImprimirLista(pila.lista);
}

void ConstruirLista(Lista &lista){
    lista.cabeza=nullptr;
    lista.longitud=0;
}

void LeerDatosEIngresarEnLista(Lista &lista){
    ifstream archDatos;
    AperturaArchivosLeer(archDatos,"Datos2.txt");
    int peso,calidad;
    
    while(1){
        archDatos>>calidad;
        if(archDatos.eof())break;
        archDatos.get();
        archDatos>>peso;
        IngresarInicioLista(peso,calidad,lista);
    }
}

void AperturaArchivosLeer(ifstream &archDatos,const char *nomb){
    archDatos.open(nomb,ios::in);
    if(!archDatos){
        cout<<"Error el archivo no se pudo abrir"<<endl;
        exit(1);
    }
}

void IngresarInicioLista(int peso,int calidad,Lista &lista){
    Nodo *nuevoNodo=new Nodo;
    nuevoNodo->calidad=calidad;
    nuevoNodo->peso=peso;
    nuevoNodo->siguiente=lista.cabeza;
    lista.cabeza=nuevoNodo;
    lista.longitud++;
}

void IngresarListaEnPila(Pila &pila,Lista &lista){
    Nodo *recorrido=lista.cabeza;
    Pila destino,aux;
    ConstruirPila(destino);
    ConstruirPila(aux);
    while(recorrido!=nullptr){
        int peso=recorrido->peso;
        int calidad=recorrido->calidad;
        int n=PosicionEnPila(calidad,peso,pila);
        if(n>0)Hanoi(pila,destino,aux,n);
        apilarNodo(peso,calidad,pila);
        if(n>0)Hanoi(destino,pila,aux,n);
        recorrido=recorrido->siguiente;
    }
}

int PosicionEnPila(int calidad,int peso,Pila &pila){
    int n=0;
    Nodo *recorrido=pila.lista.cabeza;
    while(recorrido!=nullptr){
        if(peso>=recorrido->peso){
            n++;
            if(peso==recorrido->peso and calidad>recorrido->calidad){
                n++;
                break;
            }
        }else{
            break;
        }
        recorrido=recorrido->siguiente;
    }
    return n;
}

void Hanoi(Pila &origen,Pila &destino,Pila &aux,int n){
    if(n==1 or n==0){
        Nodo *nuevoNodo=cima(origen);
        int peso=nuevoNodo->peso;
        int calidad=nuevoNodo->calidad;
        apilarNodo(peso,calidad,destino);
        EliminarCabeza(origen.lista);
        return;
    }
    Hanoi(origen,aux,destino,n-1);
    Nodo *nuevoNodo=cima(origen);
    int peso=nuevoNodo->peso;
    int calidad=nuevoNodo->calidad;
    apilarNodo(peso,calidad,destino);
    EliminarCabeza(origen.lista);  
    Hanoi(aux,destino,origen,n-1);
}

Nodo *cima(Pila &origen){
    return origen.lista.cabeza;
}

void EliminarCabeza(Lista &lista){
    Nodo*nodoEliminar=lista.cabeza;
    if(nodoEliminar!=nullptr){
        lista.cabeza=lista.cabeza->siguiente;
        delete nodoEliminar; 
        lista.longitud--;
    }
    
}

void apilarNodo(int peso,int calidad,Pila &destino){
    IngresarInicioLista(peso,calidad,destino.lista);
}

void ConstruirPila(Pila &pila){
    ConstruirLista(pila.lista);
}

void ImprimirLista(Lista &lista){
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        int peso=recorrido->peso;
        int calidad=recorrido->calidad;
        cout<<peso<<" - "<<calidad<<endl;
        recorrido=recorrido->siguiente;
    }
}