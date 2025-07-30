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
};
struct Pila{
    Lista lista;
};

void CrearPila(Pila &pila);
void CrearLista(Lista &koopa);
void Apilar(Pila &pila,int elemento);
void IngresarInicioLista(Lista &lista,int elemento);
void ImprimirPila(Pila &koopa1);
void ImprimirLista(Lista &lista);
Nodo *UltimoNodo(Lista &lista);
void OrdenarLista(Lista &lista);
void MoverNodos(int longPila2,Pila &destino,Pila &origen);
int Desapilar(Pila &pila);
int Cima(Pila &pila);
int RetornarCabeza(Lista &lista);
bool esPilaVacia(Pila &pila);
bool esListaVacia(Lista &lista);
void EliminarCabeza(Lista &lista);
void OrdenarPila(Pila &pila);
//void hanoi(Pila &origen,Pila &destino, Pila &auxiliar,int n);
void pasaPilaIterativo(Pila &koopa1,Pila &champignon);

int main(int argc, char** argv) {
    
    
    Pila koopa1;
    Pila koopa2;
    Pila champignon;
    CrearPila(koopa1);
    CrearPila(koopa2);
    Apilar(koopa1,27);
    Apilar(koopa1,30);
    Apilar(koopa1,56);
    Apilar(koopa1,15);
    Apilar(koopa1,85);

    cout<<"La pila del koopa robot 1 es: ";
    ImprimirPila(koopa1);
    
    Apilar(koopa2,20);
    Apilar(koopa2,68);
    Apilar(koopa2,22);
    Apilar(koopa2,45);
    cout<<"La pila del koopa robot 2 es: ";
    ImprimirPila(koopa2);
    
    MoverNodos(koopa2.lista.longitud,koopa1,koopa2);
    ImprimirPila(koopa1);
    cout<<"La pila del koopa robot ordenada es: ";
    OrdenarPila(koopa1);
    ImprimirPila(koopa1);
    Pila auxiliar;
   // hanoi(koopa1,champignon,auxiliar,koopa1.lista.longitud); no es con hanoi :v
    pasaPilaIterativo(koopa1,champignon);
    cout<<"En el reino champignon la tropa koopa es: ";
    ImprimirPila(champignon);
    return 0;
}

void CrearPila(Pila &pila){
    CrearLista(pila.lista);
}

void CrearLista(Lista &koopa){
    koopa.longitud=0;
    koopa.cabeza=nullptr;
}

void Apilar(Pila &pila,int elemento){
    IngresarInicioLista(pila.lista,elemento);
}

void IngresarInicioLista(Lista &lista,int elemento){
    Nodo *nuevoNodo=new Nodo;
    nuevoNodo->elemento=elemento;
    nuevoNodo->siguiente=lista.cabeza;
    lista.cabeza=nuevoNodo;
    lista.longitud++;
}

void ImprimirPila(Pila &pila){
    ImprimirLista(pila.lista);
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

void MoverNodos(int longPila2,Pila &destino,Pila &origen){
    Nodo *nodoMover=origen.lista.cabeza;
    for(int i=0;i<longPila2;i++){
        int elementoMover=Desapilar(origen);
        Apilar(destino,elementoMover);
    }
    
}

void OrdenarPila(Pila &pila){
    int longitudPila=pila.lista.longitud;
    Pila aux;
    Nodo *recorrido=pila.lista.cabeza;
    for(int i=0;i<longitudPila+9;i++){
        recorrido=pila.lista.cabeza;
        for(int j=0;j<longitudPila-1;j++){
            if(recorrido->elemento<recorrido->siguiente->elemento){
                MoverNodos(j+1,aux,pila);
                int valor=Desapilar(pila);
                MoverNodos(1,pila,aux);
                Apilar(pila,valor);
                MoverNodos(j,pila,aux);
            }else{
               recorrido=recorrido->siguiente;
            }

            
        }
    }
}

int Desapilar(Pila &pila){
    if(esPilaVacia(pila)){
        cout<<"No hay ningun elemento en la pila para desapilar"<<endl;
        return -1;
    }else{
        int elemento=Cima(pila);
        EliminarCabeza(pila.lista);
        return elemento;
    }
}

bool esPilaVacia(Pila &pila){
    return esListaVacia(pila.lista);
}

bool esListaVacia(Lista &lista){
    return lista.cabeza==nullptr;
}

int Cima(Pila &pila){
    return RetornarCabeza(pila.lista);
}

int RetornarCabeza(Lista &lista){
    return lista.cabeza->elemento;
}

void EliminarCabeza(Lista &lista){
    Nodo *nodoEliminar=lista.cabeza;
    if(nodoEliminar==nullptr){
        cout<<"La lista esta vacia asi que no se puede eliminar ningun elemento"<<endl;
    }else{
        lista.cabeza=nodoEliminar->siguiente;
        delete nodoEliminar;
        lista.longitud--;
    }
}

void hanoi(Pila &origen,Pila &destino, Pila &auxiliar,int n){
    if(n==1){
        Apilar(destino,Desapilar(origen));
        return;
        
    }
    hanoi(origen,auxiliar,destino,n-1);
    Apilar(destino,Desapilar(origen));
    hanoi(auxiliar,destino,origen,n-1);
}

void pasaPilaIterativo(Pila &koopa1,Pila &champignon){
    int n,aux,valor;
    while(!esPilaVacia(koopa1)){
        valor=Desapilar(koopa1);
        n=0;
        while(!esPilaVacia(koopa1)){
            Apilar(champignon,valor);
            n++;
            valor=Desapilar(koopa1);
        }
        while(n>0){
            aux=Desapilar(champignon);
            Apilar(koopa1,aux);
            n--;
        }
        Apilar(champignon,valor);
    }
}