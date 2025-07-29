#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

struct NodoArbol{
    int elemento;  //Este dato representa el Elemento
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
void insertar(struct ArbolBinarioBusqueda & arbol, int elemento);
void insertarRecursivo(struct NodoArbol *& raiz, int elemento);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, int elemento, 
                    struct NodoArbol * derecha);
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, int elemento,
        struct NodoArbol * derecha);
double HallarDensidadArbol(ArbolBinario &arbol);
int numeroNodosRecursivo(struct NodoArbol * nodo,int &maxAltura,int altura);

int main(int argc, char** argv) {
    ArbolBinarioBusqueda arbolBB;
    construir(arbolBB);
    insertar(arbolBB,6);
    insertar(arbolBB,4);
    insertar(arbolBB,7);
    insertar(arbolBB,5);
    insertar(arbolBB,8);
    insertar(arbolBB,3);
    insertar(arbolBB,1);
    
    cout<<"La densidad del arbol es: "<<HallarDensidadArbol(arbolBB.arbolBinario);
    return 0;
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


void insertar(struct ArbolBinarioBusqueda & arbol, int elemento){
    insertarRecursivo(arbol.arbolBinario.raiz, elemento);
}

void insertarRecursivo(struct NodoArbol *& raiz, int elemento){
    if(esNodoVacio(raiz))
        plantarArbolBinario(raiz, nullptr, elemento, nullptr);
    else
        if(raiz->elemento > elemento)
            insertarRecursivo(raiz->izquierda, elemento);
        else
            if(raiz->elemento < elemento)
                insertarRecursivo(raiz->derecha, elemento);
            else
                cout << "El elemento " << elemento << "Ya se encuentra en el árbol" << endl;
}

void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, int elemento, 
                    struct NodoArbol * derecha){
    
    struct NodoArbol * nuevoNodo = crearNuevoNodo(izquierda, elemento, derecha);
    raiz = nuevoNodo;
}

struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, int elemento,
        struct NodoArbol * derecha) {

    struct NodoArbol * nuevo = new struct NodoArbol;
    nuevo->derecha = derecha;
    nuevo->izquierda = izquierda;
    nuevo->elemento = elemento;
    return nuevo;
}

double HallarDensidadArbol(ArbolBinario &arbol){
    int maxAltura=-9999,altura=0;
    int num=numeroNodosRecursivo(arbol.raiz,maxAltura,altura);
    return (double)num/maxAltura;
}

int numeroNodosRecursivo(struct NodoArbol * nodo,int &maxAltura,int altura){
    
    if(esNodoVacio(nodo))
        return 0;
    else{
        if(esNodoVacio(nodo->izquierda) and esNodoVacio(nodo->derecha)){
            if(altura>maxAltura){
                maxAltura=altura;
            }
        }
        altura++;
        return 1 + numeroNodosRecursivo(nodo->izquierda,maxAltura,altura) + numeroNodosRecursivo(nodo->derecha,maxAltura,altura);
    }
        
}