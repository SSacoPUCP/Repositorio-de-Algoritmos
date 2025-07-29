#include <iostream>
#include <iomanip>
#include <cstring>
#include <codecvt>

using namespace std;

struct NodoArbol{
    char elemento;  //Este dato representa el Elemento
    struct NodoArbol * izquierda;  //puntero al hijo izquierdo
    struct NodoArbol * derecha;   //puntero al hijo derecho
};

struct ArbolBinario{
    struct NodoArbol * raiz;
};


void construir(struct ArbolBinario & arbol) ;
bool esNodoVacio(struct NodoArbol * raiz);
bool esArbolVacio(const struct ArbolBinario & arbol) ;
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, char elemento, 
                    struct NodoArbol * derecha);

struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, char elemento,
        struct NodoArbol * derecha);
void recorrerEnOrdenRecursivo(struct NodoArbol * nodo);
void imprimirNodo(struct NodoArbol * raiz);
void RecorrerImprimir(ArbolBinario &arbol);
void ImprimirRecursivo(NodoArbol *raiz,ArbolBinario &arbol,char *,int);

int main(int argc, char** argv) {
    ArbolBinario arbol;
    construir(arbol);
    plantarArbolBinario(arbol.raiz,nullptr,'B',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda,nullptr,'I',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda->izquierda,nullptr,'E',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda->izquierda->izquierda,nullptr,'N',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda->derecha,nullptr,'L',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda->derecha->izquierda,nullptr,'B',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda->derecha->izquierda->izquierda,nullptr,'A',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda->derecha->izquierda->izquierda->izquierda,nullptr,'O',nullptr);
    plantarArbolBinario(arbol.raiz->derecha,nullptr,'U',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->izquierda,nullptr,'E',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->izquierda->izquierda,nullptr,'N',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->izquierda->izquierda->izquierda,nullptr,'A',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->izquierda->izquierda->derecha,nullptr,'O',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->izquierda->izquierda->derecha->derecha,nullptr,'S',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha,nullptr,'R',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha->derecha,nullptr,'R',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha->derecha->izquierda,nullptr,'A',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha->derecha->derecha,nullptr,'O',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha->derecha->derecha->derecha,nullptr,'S',nullptr);
//    recorrerEnOrdenRecursivo(arbol.raiz);
    RecorrerImprimir(arbol);
    return 0;
}

void construir(struct ArbolBinario & arbol) {
    arbol.raiz = nullptr;
}

bool esNodoVacio(struct NodoArbol * raiz) {
    return raiz == nullptr;
}
bool esArbolVacio(const struct ArbolBinario & arbol) {
    return esNodoVacio(arbol.raiz);
}

void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, char elemento, 
                    struct NodoArbol * derecha){
    
    struct NodoArbol * nuevoNodo = crearNuevoNodo(izquierda, elemento, derecha);
    raiz = nuevoNodo;
}

struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, char elemento,
        struct NodoArbol * derecha) {

    struct NodoArbol * nuevo = new struct NodoArbol;
    nuevo->derecha = derecha;
    nuevo->izquierda = izquierda;
    nuevo->elemento = elemento;
    return nuevo;
}

void recorrerEnOrdenRecursivo(struct NodoArbol * nodo){
    if (not esNodoVacio(nodo)){
        recorrerEnOrdenRecursivo(nodo->izquierda);
        imprimirNodo(nodo);
        recorrerEnOrdenRecursivo(nodo->derecha);
    }
}

void imprimirNodo(struct NodoArbol * raiz){
    cout<<setw(5)<<raiz->elemento;
}

void RecorrerImprimir(ArbolBinario &arbol){

    int i=0;
    char palabra[10];
    ImprimirRecursivo(arbol.raiz,arbol,palabra,i);
}

void ImprimirRecursivo(NodoArbol *raiz,ArbolBinario &arbol,char *palabra,int i){
    if(raiz==nullptr){
        return;
    }
    palabra[i]=raiz->elemento;
    i++;
    if(raiz->derecha==nullptr and raiz->izquierda==nullptr){//Es hoja
        for(int k=0;k<i;k++){
            cout<<palabra[k];
        }
        cout<<endl;
        return;
    }
    
    ImprimirRecursivo(raiz->izquierda,arbol,palabra,i);
    ImprimirRecursivo(raiz->derecha,arbol,palabra,i);
    
}
