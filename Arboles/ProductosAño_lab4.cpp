#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Elemento{
    int cantidad;
    int anho;
};

struct Nodo {
    Elemento elemento; /*Dato que cambia por double, char, struct */
    struct Nodo * siguiente; /*puntero a una variable de tipo struct Nodo*/
};

struct Lista {
    struct Nodo * cabeza; /*apunta al inicio de la lista*/
    int longitud; /*guarda la longitud de la lista*/
};

struct Pila{
    struct Lista lista;
};

struct NodoArbol{
    Elemento elemento;  //Este dato representa el Elemento
    struct NodoArbol * izquierda;  //puntero al hijo izquierdo
    struct NodoArbol * derecha;   //puntero al hijo derecho
};

struct ArbolBinario{
    struct NodoArbol * raiz;
};

struct ArbolBinarioBusqueda{
    struct ArbolBinario arbolBinario;
};

void construir(struct ArbolBinarioBusqueda & arbol);
void construir(struct ArbolBinario & arbol);
bool esNodoVacio(struct NodoArbol * raiz);
void insertar(struct ArbolBinarioBusqueda & arbol, Elemento &elemento);
void insertarRecursivo(struct NodoArbol *& raiz, Elemento &elemento);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, Elemento &elemento, 
                    struct NodoArbol * derecha);
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, Elemento &elemento,
        struct NodoArbol * derecha) ;
void ingresa_lote(ArbolBinarioBusqueda &arbolBB,int anho,int cantidad);
bool buscarRecursivo(struct NodoArbol * nodo, int dato,int cantidad);
int comparaABB(int elementoA, int elementoB);
void construir(struct Pila & pila);
bool esPilaVacia(const struct Pila & pila);
void construir(struct Lista & tad);
const bool esListaVacia(const struct Lista & tad);
void apilar(struct Pila & pila, Elemento elemento);
void insertarAlInicio(struct Lista & tad, Elemento elemento);
Elemento desapilar(struct Pila & pila);
Elemento cima(const struct Pila & pila);
Elemento retornaCabeza(const struct Lista & tad);
void eliminaCabeza(struct Lista & tad) ;
NodoArbol *buscarRecursivoNEW(struct NodoArbol * nodo, int dato);
int comparaABBNEW(int elementoA, int elementoB);
void RecorrerOrdenDesc(ArbolBinario &arbol);
void orden(struct NodoArbol * nodo);
void imprimirNodo(struct NodoArbol * raiz);
int main(int argc, char** argv) {
    ArbolBinarioBusqueda arbolBB;
    construir(arbolBB);
    int anho=2018;
    int cantidad=100;
    ingresa_lote(arbolBB,anho,cantidad);
    ingresa_lote(arbolBB,2020,50);
    ingresa_lote(arbolBB,2022,60);
    ingresa_lote(arbolBB,2015,150);
    orden(arbolBB.arbolBinario.raiz);
    cout<<endl;
    RecorrerOrdenDesc(arbolBB.arbolBinario);
    return 0;
}

void orden(struct NodoArbol * nodo){
    if (not esNodoVacio(nodo)){
        orden(nodo->izquierda);
        imprimirNodo(nodo);
        orden(nodo->derecha);
    }
}
void imprimirNodo(struct NodoArbol * raiz){
    cout<<setw(5)<<raiz->elemento.anho<<'-'<<raiz->elemento.cantidad<<' ';
}

void construir(struct ArbolBinarioBusqueda & arbol){
    construir(arbol.arbolBinario);
}
void construir(struct ArbolBinario & arbol) {
    arbol.raiz = nullptr;
}

bool esNodoVacio(struct NodoArbol * raiz) {
    return raiz == nullptr;
}

void insertar(struct ArbolBinarioBusqueda & arbol, Elemento &elemento){
    insertarRecursivo(arbol.arbolBinario.raiz, elemento);
}

void insertarRecursivo(struct NodoArbol *& raiz, Elemento &elemento){
    if(esNodoVacio(raiz))
        plantarArbolBinario(raiz, nullptr, elemento, nullptr);
    else
        if(raiz->elemento.anho > elemento.anho)
            insertarRecursivo(raiz->izquierda, elemento);
        else
            if(raiz->elemento.anho < elemento.anho)
                insertarRecursivo(raiz->derecha, elemento);
            else
                cout << "El elemento " << elemento.anho << "Ya se encuentra en el árbol" << endl;
}

void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, Elemento &elemento, 
                    struct NodoArbol * derecha){
    
    struct NodoArbol * nuevoNodo = crearNuevoNodo(izquierda, elemento, derecha);
    raiz = nuevoNodo;
}

struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, Elemento &elemento,
        struct NodoArbol * derecha) {

    struct NodoArbol * nuevo = new struct NodoArbol;
    nuevo->derecha = derecha;
    nuevo->izquierda = izquierda;
    nuevo->elemento.anho = elemento.anho;
    nuevo->elemento.cantidad = elemento.cantidad;
    return nuevo;
}

void ingresa_lote(ArbolBinarioBusqueda &arbolBB,int anho,int cantidad){
    Elemento elemento;
    bool seEncontro=buscarRecursivo(arbolBB.arbolBinario.raiz,anho,cantidad);
    if(!seEncontro){
        elemento.anho=anho;
        elemento.cantidad=cantidad;
        insertar(arbolBB,elemento);
    }
}

bool buscarRecursivo(struct NodoArbol * nodo, int dato, int cantidad) {
    if (esNodoVacio(nodo)){
        return false;
    }
    if (comparaABB(nodo->elemento.anho, dato) == 0) {
        if (nodo->elemento.cantidad + cantidad <= 1000) {
            nodo->elemento.cantidad += cantidad;
        }
        return true;
    }
    if (comparaABB(nodo->elemento.anho, dato) == 1) {
        return buscarRecursivo(nodo->izquierda, dato, cantidad);
    }
    else {
        if (comparaABB(nodo->elemento.anho, dato) == -1) {
            return buscarRecursivo(nodo->derecha, dato, cantidad);
        }

    }

}

int comparaABB(int elementoA, int elementoB){
    if(elementoA == elementoB) return 0;
    else if(elementoA < elementoB) return -1;
    else if(elementoA > elementoB) return 1;
}

void RecorrerOrdenDesc(ArbolBinario &arbol){
    Pila pila;
    construir(pila);
    NodoArbol *raiz=arbol.raiz;
    int fin=0;

    while(fin==0){
        while(raiz){
            apilar(pila,raiz->elemento);
            raiz=raiz->derecha;
        }
        if(esPilaVacia(pila)){
            fin=1;
            
        }else{
            Elemento valor=desapilar(pila);
            cout<<valor.anho<<'-'<<valor.cantidad<<' ';
            raiz=buscarRecursivoNEW(arbol.raiz,valor.anho);
            raiz=raiz->derecha;
        }
    }
    
}

void construir(struct Pila & pila){
    construir(pila.lista);
}

/*Determina si la pila está vacía*/
bool esPilaVacia(const struct Pila & pila){
    return esListaVacia(pila.lista);
}

void construir(struct Lista & tad) {
    tad.cabeza = nullptr;
    tad.longitud = 0;
}

/*devuelve si la lista esta vacia 1, caso contrario 0 */
const bool esListaVacia(const struct Lista & tad) {
    return tad.cabeza == nullptr;
}

void apilar(struct Pila & pila, Elemento elemento){
    insertarAlInicio(pila.lista, elemento);
}

void insertarAlInicio(struct Lista & tad, Elemento elemento) {

    /*Se va cambiar por la función crear nodo*/
    struct Nodo * nuevoNodo = new struct Nodo;
    nuevoNodo->elemento.anho = elemento.anho;
    nuevoNodo->elemento.cantidad = elemento.cantidad;
    nuevoNodo->siguiente = tad.cabeza;

    tad.cabeza = nuevoNodo;
    tad.longitud++;
}

Elemento desapilar(struct Pila & pila){
    //Ya aseguramos que siempre se encuentre
    Elemento elemento = cima(pila);
        eliminaCabeza(pila.lista);
        return elemento;
}

Elemento cima(const struct Pila & pila){
    //Ya aseguramos que siempre se encuentre
    	
    return retornaCabeza(pila.lista);
}

Elemento retornaCabeza(const struct Lista & tad){
    return tad.cabeza->elemento;
}

void eliminaCabeza(struct Lista & tad) {
    struct Nodo * nodoAEliminar = tad.cabeza;
    if (nodoAEliminar != nullptr) {
        tad.cabeza = tad.cabeza->siguiente;
        delete nodoAEliminar;
        tad.longitud--;
    }
}

NodoArbol *buscarRecursivoNEW(struct NodoArbol * nodo, int dato){
    if(esNodoVacio(nodo))
        return nullptr;
    if(comparaABBNEW(nodo->elemento.anho, dato) == 0){
        return nodo;
    }
        
    if(comparaABBNEW(nodo->elemento.anho, dato) == 1){
        return buscarRecursivoNEW(nodo->izquierda, dato);
    }
        
    else{
        if(comparaABB(nodo->elemento.anho, dato) == -1)
            return buscarRecursivoNEW(nodo->derecha, dato);
    }
        
}

int comparaABBNEW(int elementoA, int elementoB){
    if(elementoA == elementoB) return 0;
    else if(elementoA < elementoB) return -1;
    else if(elementoA > elementoB) return 1;
}