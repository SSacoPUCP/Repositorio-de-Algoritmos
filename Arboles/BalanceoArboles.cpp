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

struct Nodo {
    NodoArbol* elemento; /*Dato que cambia por double, char, struct Elemento*/
    struct Nodo * siguiente; /*puntero a una variable de tipo struct Nodo*/
};
struct Lista {
    struct Nodo * cabeza; /*apunta al inicio de la lista*/
    struct Nodo * cola; /*apunta al final de la lista*/
    int longitud; /*guarda la longitud de la lista*/
};
struct Cola {
    struct Lista lista;
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
void recorrerEnOrden(const struct ArbolBinario & arbol);
void recorrerEnOrdenRecursivo(struct NodoArbol * nodo);
void imprimirNodo(struct NodoArbol * raiz);
NodoArbol *BalancearArbol(NodoArbol *raiz);
NodoArbol *BalancearNodo(NodoArbol *raiz);
int alturaRecursivo(struct NodoArbol * nodo);
NodoArbol *RotarDerecha(NodoArbol *nodo);
NodoArbol *RotarIzquierda(NodoArbol *nodo);
int maximo(int a, int b);
void construir(struct Cola & cola);
void construir(struct Lista & lista) ;
bool esColaVacia(const struct Cola & cola);
const bool esListaVacia(const struct Lista & lista);
void encolar(struct Cola & cola, NodoArbol* elemento);
NodoArbol* desencolar(struct Cola & cola);
NodoArbol* retornaCabeza(const struct Lista & lista);
void eliminaCabeza(struct Lista & lista);
void insertarAlFinal(struct Lista & lista, NodoArbol* elemento) ;
struct Nodo * crearNodo(NodoArbol* elemento, struct Nodo * siguiente) ;
void RecorrerAmplitud(ArbolBinario &arbol);
bool esArbolVacio(const struct ArbolBinario & arbol);

int main(int argc, char** argv) {
    ArbolBinarioBusqueda arbolBB;
    construir(arbolBB);
    insertar(arbolBB,12);
    insertar(arbolBB,45);
    insertar(arbolBB,2);
    insertar(arbolBB,87);
    insertar(arbolBB,25);
    insertar(arbolBB,7);
    insertar(arbolBB,88);
    insertar(arbolBB,1);
    insertar(arbolBB,80);
    insertar(arbolBB,75);
    recorrerEnOrden(arbolBB.arbolBinario);
    cout<<endl;
    cout<<"Antes de balancear"<<endl;
    RecorrerAmplitud(arbolBB.arbolBinario);
    cout<<endl;
    arbolBB.arbolBinario.raiz=BalancearArbol(arbolBB.arbolBinario.raiz);
    cout<<"Despues de balancear"<<endl;
    RecorrerAmplitud(arbolBB.arbolBinario);
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

NodoArbol *BalancearArbol(NodoArbol *raiz){
    if(esNodoVacio(raiz)) return nullptr;
    raiz->izquierda=BalancearArbol(raiz->izquierda);
    raiz->derecha=BalancearArbol(raiz->derecha);
    raiz=BalancearNodo(raiz);
    return raiz;
}

NodoArbol *BalancearNodo(NodoArbol *raiz){

    int factorBalanceo=alturaRecursivo(raiz->izquierda)-alturaRecursivo(raiz->derecha);
    if(factorBalanceo>1){//El subarbol izquierdo es mas alto
        if(alturaRecursivo(raiz->izquierda->izquierda)>=alturaRecursivo(raiz->izquierda->derecha)){
            raiz=RotarDerecha(raiz); //Rotacion simple derecha
        }else{
            raiz->izquierda=RotarIzquierda(raiz->izquierda); //Rotacion doble derecha
            raiz=RotarDerecha(raiz);
        }
    }else if(factorBalanceo<-1){
        if(alturaRecursivo(raiz->derecha->derecha)>=alturaRecursivo(raiz->derecha->izquierda)){
            raiz=RotarIzquierda(raiz); //Rotacion simple izquierda
        }else{
            raiz->derecha=RotarDerecha(raiz->derecha); //Rotacion doble izquierda
            raiz=RotarIzquierda(raiz);
        }
    }
    return raiz;
}

int alturaRecursivo(struct NodoArbol * nodo){
    if(esNodoVacio(nodo)){
        return 0;
    }
        
    else if(esNodoVacio(nodo->izquierda) and esNodoVacio(nodo->derecha)){
        return 0;
    }
        
    else{
         return 1 + maximo(alturaRecursivo(nodo->izquierda), alturaRecursivo(nodo->derecha));
    }
}

NodoArbol *RotarDerecha(NodoArbol *nodo){
    NodoArbol *nodoIzq=nodo->izquierda;
    nodo->izquierda=nodoIzq->derecha;
    nodoIzq->derecha=nodo;
    return nodoIzq;
}

NodoArbol *RotarIzquierda(NodoArbol *nodo){
    NodoArbol *nodoDer=nodo->derecha;
    nodo->derecha=nodoDer->izquierda;
    nodoDer->izquierda=nodo;
    return nodoDer;
}

int maximo(int a, int b){
    return a >= b ? a : b;
}





void RecorrerAmplitud(ArbolBinario &arbol){
    int nivel=0;
    Cola cola;
    construir(cola);
    if(!esArbolVacio(arbol)){
        encolar(cola,arbol.raiz);
        encolar(cola,nullptr);
        
        while(!esColaVacia(cola)){
            NodoArbol *nodo=desencolar(cola);
            if(nodo==nullptr){ //Cambia de nivel
                nivel++;
                cout<<endl;
                if(!esColaVacia(cola)){
                    encolar(cola,nullptr);
                }
            }else{
                imprimirNodo(nodo);
                if(!esNodoVacio(nodo->izquierda)){
                    encolar(cola,nodo->izquierda);
                }
                if(!esNodoVacio(nodo->derecha)){
                    encolar(cola,nodo->derecha);
                }
            }
            
        }
    }
}

void construir(struct Cola & cola){
    construir(cola.lista);
}

void construir(struct Lista & lista) {
    lista.cabeza = nullptr;
    lista.cola = nullptr;
    lista.longitud = 0;
}

bool esArbolVacio(const struct ArbolBinario & arbol) {
    return esNodoVacio(arbol.raiz);
}

bool esColaVacia(const struct Cola & cola){
    return esListaVacia(cola.lista);
}

const bool esListaVacia(const struct Lista & lista) {
    return lista.cabeza == nullptr;
}

void encolar(struct Cola & cola, NodoArbol* elemento){
    insertarAlFinal(cola.lista, elemento);
}

NodoArbol* desencolar(struct Cola & cola){
    if(esColaVacia(cola)){
        cout<<"La cola está vacía no se puede desencolar"<<endl;
        exit(1);
    }
    NodoArbol* elemento = retornaCabeza(cola.lista);
    eliminaCabeza(cola.lista);
    return elemento;
}

NodoArbol* retornaCabeza(const struct Lista & lista){
    if (esListaVacia(lista)){
        cout<<"No existe la cabeza por que la cola está vacía"<<endl;
        exit(1);
    }
    return lista.cabeza->elemento;
}

void eliminaCabeza(struct Lista & lista) {
    struct Nodo * nodoAEliminar = lista.cabeza;
    if (nodoAEliminar == nullptr){
        cout<<"No se puede eliminar la cabeza pues la lista está vacía";
        exit(1);
    }
    else{
        lista.cabeza = lista.cabeza->siguiente;
        if(lista.cabeza == nullptr)
            lista.cola = nullptr;
        delete nodoAEliminar;
        lista.longitud--;
    }
}

void insertarAlFinal(struct Lista & lista, NodoArbol* elemento) {
 
    struct Nodo * ultimoNodo = lista.cola;
    struct Nodo * nuevoNodo = crearNodo(elemento, nullptr);

    if (ultimoNodo == nullptr) /*Si la lista está vacia*/
        lista.cabeza = nuevoNodo; /*se inserta en la cabeza de la lista*/
    else //La lista ya tiene nodos
        ultimoNodo->siguiente = nuevoNodo;
    lista.cola = nuevoNodo;
    lista.longitud++;
}

/*Crea un nuevo nodo con los datos dados como parámetros*/
struct Nodo * crearNodo(NodoArbol* elemento, struct Nodo * siguiente) {
    struct Nodo * nuevoNodo = new struct Nodo;
    nuevoNodo->elemento = elemento;
    nuevoNodo->siguiente = siguiente;
    return nuevoNodo;
}