#include <iostream>
#include <iomanip>
#include <cstring>

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
bool esNodoVacio(struct NodoArbol * raiz) ;
bool esArbolVacio(const struct ArbolBinario & arbol);
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, char elemento,
        struct NodoArbol * derecha);
void plantarArbolBinario(struct ArbolBinario & arbol, struct NodoArbol * izquierda, 
                         char elemento, struct NodoArbol * derecha);
void plantarArbolBinario(struct ArbolBinario & arbol, struct ArbolBinario & arbolIzquierda, 
                         char elemento, struct ArbolBinario & arbolDerecha);
void recorrerEnOrden(const struct ArbolBinario & arbol);
void recorrerEnOrdenRecursivo(struct NodoArbol * nodo);
void imprimirNodo(struct NodoArbol * raiz);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, char elemento, 
                    struct NodoArbol * derecha);
bool BuscarPalabra(char *palabra,ArbolBinario &arbol);
void BuscarRecursivo(char *palabra,NodoArbol *raiz);

int main(int argc, char** argv) {
    char palabra[6][20]=  {{'H','I','J','O'},
                                     {'F','I','N','A','L'},
                                     {'M','U','N','D','O'},
                                     {'D','E','L'} ,
                                     {'C','I','C','L','O'}};
    
    ArbolBinario arbol;
    construir(arbol);
    plantarArbolBinario(arbol.raiz,nullptr,'L',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda,nullptr,'D',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda->izquierda,nullptr,'E',nullptr);
    plantarArbolBinario(arbol.raiz->izquierda->derecha,nullptr,'E',nullptr);
    plantarArbolBinario(arbol.raiz->derecha,nullptr,'I',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->izquierda,nullptr,'C',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->izquierda->izquierda,nullptr,'C',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->izquierda->izquierda->izquierda,nullptr,'O',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha,nullptr,'N',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha->izquierda,nullptr,'A',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha->izquierda->izquierda,nullptr,'F',nullptr);
    plantarArbolBinario(arbol.raiz->derecha->derecha->izquierda->derecha,nullptr,'T',nullptr);
    recorrerEnOrden(arbol);
    for(int i=0;i<6;i++){
        if(BuscarPalabra(palabra[i],arbol)){
            cout<<' '<<palabra[i]<<' ';
        }
    }
    return 0;
}

bool BuscarPalabra(char *palabra,ArbolBinario &arbol){
    char aux[20];
    strcpy(aux,palabra);
    BuscarRecursivo(aux,arbol.raiz);
    for(int i=0;aux[i];i++){
        if(aux[i]!=' '){
            return false;
        }
    }
    return true;
}

void BuscarRecursivo(char *palabra,NodoArbol *raiz){
    if(raiz==nullptr){
        return;
    }
    bool esValido=false;
    for(int i=0;palabra[i];i++){
        if(palabra[i]==raiz->elemento){
            palabra[i]=' ';
            esValido=true;
            break;
        }
    }
    if(!esValido)return; //No encontro la letra
     BuscarRecursivo(palabra,raiz->izquierda);
     BuscarRecursivo(palabra,raiz->derecha);
    
    
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

void recorrerEnOrden(const struct ArbolBinario & arbol){
    recorrerEnOrdenRecursivo(arbol.raiz);
}
void recorrerEnOrdenRecursivo(struct NodoArbol * nodo){
    if (not esNodoVacio(nodo)){
        recorrerEnOrdenRecursivo(nodo->izquierda);
        imprimirNodo(nodo);
        recorrerEnOrdenRecursivo(nodo->derecha);
    }
}

struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, char elemento,
        struct NodoArbol * derecha) {

    struct NodoArbol * nuevo = new struct NodoArbol;
    nuevo->derecha = derecha;
    nuevo->izquierda = izquierda;
    nuevo->elemento = elemento;
    return nuevo;
}

void plantarArbolBinario(struct ArbolBinario & arbol, struct NodoArbol * izquierda, 
                         char elemento, struct NodoArbol * derecha) {
    
    struct NodoArbol * nuevoNodo = crearNuevoNodo(izquierda, elemento, derecha);
    arbol.raiz = nuevoNodo;

}

void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, char elemento, 
                    struct NodoArbol * derecha){
    
    struct NodoArbol * nuevoNodo = crearNuevoNodo(izquierda, elemento, derecha);
    raiz = nuevoNodo;
}

void plantarArbolBinario(struct ArbolBinario & arbol, struct ArbolBinario & arbolIzquierda, 
                         char elemento, struct ArbolBinario & arbolDerecha) {
    struct NodoArbol * nuevoNodo = crearNuevoNodo(arbolIzquierda.raiz, elemento,
            arbolDerecha.raiz);
    arbol.raiz = nuevoNodo;

}

void imprimirNodo(struct NodoArbol * raiz){
    cout<<setw(5)<<raiz->elemento;
}
