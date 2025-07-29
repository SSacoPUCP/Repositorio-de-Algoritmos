#include <iostream>
#include <iomanip>
#include <cstring>

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
void construir(struct ArbolBinario & arbol) ;
void insertar(struct ArbolBinarioBusqueda & arbol, int elemento);
void insertarRecursivo(struct NodoArbol *& raiz, int elemento);
bool esNodoVacio(struct NodoArbol * raiz);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, int elemento, 
                    struct NodoArbol * derecha);
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, int elemento,
        struct NodoArbol * derecha);
void recorrerEnOrden(const struct ArbolBinario & arbol);
void recorrerEnOrdenRecursivo(struct NodoArbol * nodo);
void imprimirNodo(struct NodoArbol * raiz);
int numeroNodosRecursivo(struct NodoArbol * nodo);
int numeroHojasRecursivo(struct NodoArbol * nodo);
NodoArbol *AplicarArbolRecursivo(NodoArbol *raizBB );
void RecorrerValidar(NodoArbol *raiz,NodoArbol *parbol);
void AplicarArbol(ArbolBinarioBusqueda &arbolP,ArbolBinario &arbolS,ArbolBinario &arbolR);
bool VerificarBusqueda(NodoArbol *raiz) ;
void sumaNodos(int &suma,NodoArbol *raiz);

int main(int argc, char** argv) {
    ArbolBinarioBusqueda arbolP;
    ArbolBinario arbolS;
    construir(arbolP);
    insertar(arbolP,5);
    insertar(arbolP,3);
    insertar(arbolP,9);
    construir(arbolS);
    plantarArbolBinario(arbolS.raiz,nullptr,1,nullptr);
    plantarArbolBinario(arbolS.raiz->izquierda,nullptr,7,nullptr);
    plantarArbolBinario(arbolS.raiz->izquierda->izquierda,nullptr,2,nullptr);
    plantarArbolBinario(arbolS.raiz->izquierda->derecha,nullptr,3,nullptr);
    plantarArbolBinario(arbolS.raiz->derecha,nullptr,8,nullptr);
    cout<<"IMPRESION DE ARBOLES EN ORDEN"<<endl;
    recorrerEnOrden(arbolP.arbolBinario);
    cout<<endl;
    recorrerEnOrden(arbolS);
    ArbolBinario arbolR;
    construir(arbolR);
    AplicarArbol(arbolP,arbolS,arbolR);
    cout<<endl;
    recorrerEnOrden(arbolR);
    cout<<endl;
    if(VerificarBusqueda(arbolR.raiz)){
        cout<<"SIN EVENTOS SOSPECHOSOS"<<endl;
    }else{
        cout<<"ANOMALIA DETECTADA"<<endl;
    }
    return 0;
}

void construir(struct ArbolBinarioBusqueda & arbol){
    construir(arbol.arbolBinario);
}

void construir(struct ArbolBinario & arbol) {
    arbol.raiz = nullptr;
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

bool esNodoVacio(struct NodoArbol * raiz) {
    return raiz == nullptr;
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

void imprimirNodo(struct NodoArbol * raiz){
    cout<<setw(5)<<raiz->elemento;
}

void AplicarArbol(ArbolBinarioBusqueda &arbolP,ArbolBinario &arbolS,ArbolBinario &arbolR){
    
    NodoArbol *parbol;
    parbol=AplicarArbolRecursivo(arbolP.arbolBinario.raiz);
    
    arbolR.raiz=parbol;
    NodoArbol *parbol2;
    
    parbol2=arbolS.raiz;
    RecorrerValidar(arbolR.raiz,parbol2);
}

NodoArbol *AplicarArbolRecursivo(NodoArbol *raizBB ){
    if(raizBB==nullptr){
        return raizBB;
    }
    NodoArbol *izq,*der,*parbol;
    izq=AplicarArbolRecursivo(raizBB->izquierda);
    der=AplicarArbolRecursivo(raizBB->derecha);
    parbol=crearNuevoNodo(izq,raizBB->elemento,der);
    return parbol;
}

void RecorrerValidar(NodoArbol *raiz,NodoArbol *parbol){
    int sumaNodos=numeroNodosRecursivo(parbol);
    int sumaHojas=numeroHojasRecursivo(parbol);
    if(not esNodoVacio(raiz)){
        raiz->elemento=raiz->elemento+sumaNodos-sumaHojas;
        RecorrerValidar(raiz->izquierda,parbol->izquierda);
        RecorrerValidar(raiz->derecha,parbol->derecha);
    }
}


int numeroNodosRecursivo(struct NodoArbol * nodo){
    if(esNodoVacio(nodo))
        return 0;
    else
        return 1 + numeroNodosRecursivo(nodo->izquierda) + numeroNodosRecursivo(nodo->derecha);
}

int numeroHojasRecursivo(struct NodoArbol * nodo){
    if(esNodoVacio(nodo))
        return 0;
    else if(esNodoVacio(nodo->izquierda) and esNodoVacio(nodo->derecha))
        return 1;
    else return numeroHojasRecursivo(nodo->izquierda) + numeroHojasRecursivo(nodo->derecha);
}

bool VerificarBusqueda(NodoArbol *raiz) {
    int suma = 0;
    sumaNodos(suma,raiz);
    if (not esNodoVacio(raiz)) {
        if (raiz->elemento < raiz->derecha->elemento and raiz->elemento > raiz->izquierda->elemento and
                suma % 2==0) {
            return true;
        } else {
            return false;
        }
        VerificarBusqueda(raiz->izquierda);
        VerificarBusqueda(raiz->derecha);
    }
}

void sumaNodos(int &suma,NodoArbol *raiz){
    if(not esNodoVacio(raiz)){
        suma=raiz->elemento+suma;
        sumaNodos(suma,raiz->izquierda);
        sumaNodos(suma,raiz->derecha);
    }
}