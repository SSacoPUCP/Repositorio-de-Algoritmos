#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;



struct Elemento{
    int prioridad;
    char nombre[100];
};

struct ArbolBinario{
    struct NodoArbol * raiz;
};

struct NodoArbol{
    Elemento elemento;  //Este dato representa el Elemento
    struct NodoArbol * izquierda;  //puntero al hijo izquierdo
    struct NodoArbol * derecha;   //puntero al hijo derecho
};

struct Nodo{
    NodoArbol *elemento;
    Nodo *siguiente;
};

struct Lista{
    Nodo *cabeza;
    Nodo *cola;
    int longitud;
};

struct Cola{
    Lista lista;
};

void construir(struct ArbolBinario & arbol);
void plantarArbolBinario(struct ArbolBinario & arbol, struct ArbolBinario & arbolIzquierdo,
                         struct Elemento elemento, struct ArbolBinario & arbolDerecho);
void plantarArbolBinario(struct ArbolBinario & arbol, struct NodoArbol * izquierdo,
                         struct Elemento elemento, struct NodoArbol * derecho);
struct NodoArbol * crearNuevoNodoArbol(struct NodoArbol * izquierdo, 
                               struct Elemento elemento, struct NodoArbol * derecho);
int numeroNodos(const struct ArbolBinario & arbol);
int numeroNodosRecursivo(struct NodoArbol * nodo);
bool esNodoVacio(struct NodoArbol * raiz);
bool esArbolVacio(const struct ArbolBinario & arbol);
void construir(struct Cola & cola);
bool esColaVacia(const struct Cola & cola);
void encolar(struct Cola & cola, struct NodoArbol *  elemento);
const bool esListaVacia(const struct Lista & lista) ;
void insertarAlFinal(struct Lista & lista, struct NodoArbol *  elemento);
struct Nodo * crearNodo(struct NodoArbol *  elemento, struct Nodo * siguiente) ;
void construir(struct Lista & lista) ;
struct NodoArbol *  retornaCabeza(const struct Lista & lista);
void eliminaCabeza(struct Lista & lista) ;
void RecorrerNiveles(ArbolBinario &arbol);
struct NodoArbol *  desencolar(struct Cola & cola);
void ImprimirNodo(NodoArbol *nodo);
void destruirArbolBinario(struct ArbolBinario & arbol);
void destruirRecursivo(struct NodoArbol * nodo);
void DestruirLado(ArbolBinario &arbol,char seccion);


int main(int argc, char** argv) {
    ArbolBinario arbol1,arbol2,arbol3,arbol4,arbol5,arbol6,arbol7,arbol8,arbol;
    Elemento elemento1{4,"Seccion 1.1.1"},
                                elemento2{2,"Seccion 1.1.2"},
                                elemento3{3,"Seccion 2.1"},
                                elemento4{4,"Seccion2.2"},
                                elemento5{6,"Seccion 1.1"},
                                elemento6{10,"Principal"},
                                elemento7{8,"Capitulo1"},
                                elemento8{5,"Capitulo2"},
                                elemento9{7,"Titulo"};
                                
    plantarArbolBinario(arbol1,nullptr,elemento1,nullptr);                            
    plantarArbolBinario(arbol2,nullptr,elemento2,nullptr);                            
    plantarArbolBinario(arbol3,nullptr,elemento3,nullptr);                            
    plantarArbolBinario(arbol4,nullptr,elemento4,nullptr);                            
    plantarArbolBinario(arbol5,arbol1,elemento5,arbol2);                            
    plantarArbolBinario(arbol6,nullptr,elemento6,nullptr);                            
    plantarArbolBinario(arbol7,arbol5,elemento7,arbol6);                            
    plantarArbolBinario(arbol8,arbol3,elemento8,arbol4);                            
    plantarArbolBinario(arbol,arbol7,elemento9,arbol8);
    
    RecorrerNiveles(arbol);
    char seccion;
    cout<<"Que seccion quieres quitar D o I"<<endl;
    cin>>seccion;
    DestruirLado(arbol,seccion);
    return 0;
}

void construir(struct ArbolBinario & arbol){
    arbol.raiz = nullptr;
}

void construir(struct Lista & lista) {
    lista.cabeza = nullptr;
    lista.cola = nullptr; //puntero cola a null
    lista.longitud = 0;
}

void plantarArbolBinario(struct ArbolBinario & arbol, struct ArbolBinario & arbolIzquierdo,
                         struct Elemento elemento, struct ArbolBinario & arbolDerecho){
    
    struct NodoArbol * nuevoNodo = crearNuevoNodoArbol(arbolIzquierdo.raiz, elemento, arbolDerecho.raiz);
    arbol.raiz = nuevoNodo;
    
}

void plantarArbolBinario(struct ArbolBinario & arbol, struct NodoArbol * izquierdo,
                         struct Elemento elemento, struct NodoArbol * derecho){
    
    struct NodoArbol * nuevoNodo = crearNuevoNodoArbol(izquierdo, elemento, derecho);
    arbol.raiz = nuevoNodo;
}

struct NodoArbol * crearNuevoNodoArbol(struct NodoArbol * izquierdo, 
                               struct Elemento elemento, struct NodoArbol * derecho){
    struct NodoArbol * nuevoNodo = new struct NodoArbol;
    strcpy(nuevoNodo->elemento.nombre,elemento.nombre);
    nuevoNodo->elemento.prioridad=elemento.prioridad;
    nuevoNodo->izquierda = izquierdo;
    nuevoNodo->derecha = derecho;
    return nuevoNodo;
}

int numeroNodos(const struct ArbolBinario & arbol){
    return numeroNodosRecursivo(arbol.raiz);
}

int numeroNodosRecursivo(struct NodoArbol * nodo){
    if(esNodoVacio(nodo))
        return 0;
    else
        return 1 + numeroNodosRecursivo(nodo->izquierda) + numeroNodosRecursivo(nodo->derecha);
}

bool esNodoVacio(struct NodoArbol * raiz) {
    return raiz == nullptr;
}

bool esArbolVacio(const struct ArbolBinario & arbol){
    return esNodoVacio(arbol.raiz);
}


void RecorrerNiveles(ArbolBinario &arbol){ //Amplitud
    int nivel=0;
    int ultimoNivel=-1;
    Cola cola;
    construir(cola);
    if(!esArbolVacio(arbol)){
        encolar(cola,arbol.raiz);
        encolar(cola,nullptr);
        while(!esColaVacia(cola)){
            NodoArbol *nodo=desencolar(cola);
            if(nodo!=nullptr and strcmp(nodo->elemento.nombre,"Principal")==0){
                ultimoNivel=nivel;
            }
            if(nodo==nullptr){
                nivel++;
                cout<<endl;
                if(!esColaVacia(cola)){
                    encolar(cola,nullptr);
                }
                
            }else{
                 ImprimirNodo(nodo);
                if (!esNodoVacio(nodo->derecha)) {
                    encolar(cola, nodo->derecha);
                }
                if (!esNodoVacio(nodo->izquierda)) {
                    encolar(cola, nodo->izquierda);
                }
            }
           
        }
    }
    cout<<"El nivel es "<<ultimoNivel<<endl;
}

void construir(struct Cola & cola){
    construir(cola.lista);
}

bool esColaVacia(const struct Cola & cola){
    return esListaVacia(cola.lista);
}

void encolar(struct Cola & cola, struct NodoArbol *  elemento){
    insertarAlFinal(cola.lista, elemento);
}

void insertarAlFinal(struct Lista & lista, struct NodoArbol *  elemento) {

    //struct Nodo * ultimoNodo = obtenerUltimoNodo(lista);
    struct Nodo * ultimoNodo = lista.cola; /*obtiene el último nodo*/
    struct Nodo * nuevoNodo = crearNodo(elemento, nullptr);

    if (ultimoNodo == nullptr) {/*Si la lista está vacia*/
        lista.cabeza = nuevoNodo; /*se inserta en la cabeza de la lista*/
        lista.cola = nuevoNodo;
    }
    else {//La lista ya tiene nodos
        ultimoNodo->siguiente = nuevoNodo;
        lista.cola = nuevoNodo;
    }
    lista.longitud++;
}

struct Nodo * crearNodo(struct NodoArbol *  elemento, struct Nodo * siguiente) {
    struct Nodo * nuevoNodo = new struct Nodo;
    nuevoNodo->elemento = elemento;
    nuevoNodo->siguiente = siguiente;
    return nuevoNodo;
}

const bool esListaVacia(const struct Lista & lista) {
    return lista.cabeza == nullptr;
}

struct NodoArbol *  desencolar(struct Cola & cola){
    if(esColaVacia(cola)){
        cout<<"La cola está vacía no se puede desencolar"<<endl;
        exit(1);
    }
    struct NodoArbol *  elemento = retornaCabeza(cola.lista);
    eliminaCabeza(cola.lista);
    return elemento;
}

struct NodoArbol *  retornaCabeza(const struct Lista & lista){
    return lista.cabeza->elemento;
}

void eliminaCabeza(struct Lista & lista) {
    struct Nodo * nodoAEliminar = lista.cabeza;
    if (nodoAEliminar != nullptr) {
        lista.cabeza = lista.cabeza->siguiente;
        if(lista.cabeza == nullptr) /*falta añadir para que coloque*/
            lista.cola = nullptr;  /*cola en null*/
        delete nodoAEliminar;
        lista.longitud--;
    }
}

void ImprimirNodo(NodoArbol *nodo){
    cout<<nodo->elemento.nombre<<setw(10)<<nodo->elemento.prioridad<<' ';
}

void destruirArbolBinario(struct ArbolBinario & arbol){
    destruirRecursivo(arbol.raiz);
    arbol.raiz = nullptr;
}

void destruirRecursivo(struct NodoArbol * nodo){
    if(not (esNodoVacio(nodo))){
        destruirRecursivo(nodo->izquierda);
        destruirRecursivo(nodo->derecha);
        delete nodo;
    }
}

void DestruirLado(ArbolBinario &arbol,char seccion){
    NodoArbol *aux;
    cout<<"Nodos antes de eliminar: "<<numeroNodos(arbol)<<endl;
    if(seccion=='D'){
        aux=arbol.raiz->derecha;
        arbol.raiz->derecha=nullptr;
    }else{
        aux=arbol.raiz->izquierda;
        arbol.raiz->izquierda=nullptr;
    }
    cout<<"Nodos despues de eliminar: "<<numeroNodos(arbol);
    destruirRecursivo(aux);
}
