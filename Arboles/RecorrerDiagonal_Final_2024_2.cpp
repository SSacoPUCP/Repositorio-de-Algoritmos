 * File:   main.cpp
 * Author: Sebastian
 *
 * Created on 10 de diciembre de 2024, 12:51 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstddef>

using namespace std;

struct Elemento{
    int esSkynerd;
    int id;
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

struct Nodo {
    int elemento; /*Dato que cambia por double, char, struct Elemento*/
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

struct Pila{
    struct Lista lista;
};

void construir(struct ArbolBinarioBusqueda & arbol);
void construir(struct ArbolBinario & arbol) ;
bool esNodoVacio(struct NodoArbol * raiz) ;
void insertar(struct ArbolBinarioBusqueda & arbol, Elemento elemento);
void insertarRecursivo(struct NodoArbol *& raiz, Elemento elemento);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, Elemento elemento, 
                    struct NodoArbol * derecha);
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, Elemento elemento,
        struct NodoArbol * derecha) ;
void RecorrerDiagonal(ArbolBinario &arbol);
void construir(struct Cola & cola);
void construir(struct Lista & lista) ;
bool esNodoVacio(struct NodoArbol * raiz) ;
bool esColaVacia(const struct Cola & cola);
const bool esListaVacia(const struct Lista & lista) ;
void encolar(struct Cola & cola, int elemento);
void insertarAlFinal(struct Lista & lista, int elemento) ;
struct Nodo * crearNodo(int elemento, struct Nodo * siguiente);
int desencolar(struct Cola & cola);
int retornaCabeza(const struct Lista & lista);
void eliminaCabeza(struct Lista & lista) ;
NodoArbol *buscarRecursivo(struct NodoArbol * nodo, int dato);
int comparaABB(int elementoA, int elementoB);
void recorrerPreOrdenRecursivo(struct NodoArbol * nodo);
void imprimirNodo(struct NodoArbol * raiz);
void construir(struct Pila & pila);
bool esPilaVacia(const struct Pila & pila);
void apilar(struct Pila & pila, int elemento);
int desapilar(struct Pila & pila);
int cima(const struct Pila & pila);
void insertarAlInicio(struct Lista & tad, int elemento) ;
int HallarNivel(NodoArbol *&raiz,int dato,int nivel);
void RecorrerDiagonalInverso(ArbolBinario &arbol);


int main(int argc, char** argv) {
    //Construimos el arbol 
    ArbolBinarioBusqueda arbolitoBB;
    construir(arbolitoBB);
    
    Elemento e1;
    e1.esSkynerd=0;
    e1.id=100;
    insertar(arbolitoBB,e1);
    
    Elemento e2;
    e2.esSkynerd=0;
    e2.id=50;
    insertar(arbolitoBB,e2);
    
    Elemento e3;
    e3.esSkynerd=0;
    e3.id=150;
    insertar(arbolitoBB,e3);
    
    Elemento e4;
    e4.esSkynerd=1;
    e4.id=125;
    insertar(arbolitoBB,e4);
    
    Elemento e5;
    e5.esSkynerd=0;
    e5.id=175;
    insertar(arbolitoBB,e5);
    
    Elemento e6;
    e6.esSkynerd=0;
    e6.id=25;
    insertar(arbolitoBB,e6);
    
    Elemento e7;
    e7.esSkynerd=0;
    e7.id=200;
    insertar(arbolitoBB,e7);
    
    Elemento e8;
    e8.esSkynerd=0;
    e8.id=75;
    insertar(arbolitoBB,e8);
    
    Elemento e9;
    e9.esSkynerd=0;
    e9.id=40;
    insertar(arbolitoBB,e9);
    recorrerPreOrdenRecursivo(arbolitoBB.arbolBinario.raiz);
    cout<<endl;
    RecorrerDiagonal(arbolitoBB.arbolBinario);
    cout<<endl;
    RecorrerDiagonalInverso(arbolitoBB.arbolBinario);
    cout<<endl;
    return 0;
}

void recorrerPreOrdenRecursivo(struct NodoArbol * nodo){
    if(not esNodoVacio(nodo)){
        imprimirNodo(nodo);
        recorrerPreOrdenRecursivo(nodo->izquierda);
        recorrerPreOrdenRecursivo(nodo->derecha);
    }
}

void imprimirNodo(struct NodoArbol * raiz){
    cout<<setw(5)<<raiz->elemento.esSkynerd<<' '<<raiz->elemento.id<<' ';
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

void insertar(struct ArbolBinarioBusqueda & arbol, Elemento elemento){
    insertarRecursivo(arbol.arbolBinario.raiz, elemento);
}

void insertarRecursivo(struct NodoArbol *& raiz, Elemento elemento){
    if(esNodoVacio(raiz))
        plantarArbolBinario(raiz, nullptr, elemento, nullptr);
    else
        if(raiz->elemento.id > elemento.id)
            insertarRecursivo(raiz->izquierda, elemento);
        else
            if(raiz->elemento.id < elemento.id)
                insertarRecursivo(raiz->derecha, elemento);
            else
                cout << "El elemento ";
}

void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, Elemento elemento, 
                    struct NodoArbol * derecha){
    
    struct NodoArbol * nuevoNodo = crearNuevoNodo(izquierda, elemento, derecha);
    raiz = nuevoNodo;
}

struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, Elemento elemento,
        struct NodoArbol * derecha) {

    struct NodoArbol * nuevo = new struct NodoArbol;
    nuevo->derecha = derecha;
    nuevo->izquierda = izquierda;
    nuevo->elemento.esSkynerd = elemento.esSkynerd;
    nuevo->elemento.id = elemento.id;
    return nuevo;
}

void RecorrerDiagonal(ArbolBinario &arbol){
    Cola cola;
    construir(cola);
    NodoArbol *raiz=arbol.raiz;
    while(1){
        while(raiz){
            encolar(cola,raiz->elemento.id);
            raiz=raiz->derecha;
        }
        int buscar=desencolar(cola);
        raiz=buscarRecursivo(arbol.raiz,buscar);
        cout<<raiz->elemento.esSkynerd<<'-'<<raiz->elemento.id<<' ';
        
        if(raiz->izquierda){
            raiz=raiz->izquierda;
        }else{
            raiz=nullptr;
        }
        if(esColaVacia(cola))break;
    }
}

void RecorrerDiagonalInverso(ArbolBinario &arbol) {
    Pila pilaDer;
    Pila pilaIzq;
    construir(pilaDer);
    construir(pilaIzq);
    NodoArbol *nodoIzq = arbol.raiz->izquierda;
    NodoArbol *nodoDer = arbol.raiz->derecha;
    int valorDer = 0, valorIzq = 0;
    while (1) {
        while (nodoIzq) {
            apilar(pilaIzq, nodoIzq->elemento.id);
            nodoIzq = nodoIzq->izquierda;
        }
        
        while (nodoDer) {
                apilar(pilaDer, nodoDer->elemento.id);
                nodoDer = nodoDer->izquierda;
            }
        
        int supIzq = cima(pilaIzq);
        nodoIzq = buscarRecursivo(arbol.raiz, supIzq);
        
        int supDer = cima(pilaDer);
        nodoDer = buscarRecursivo(arbol.raiz, supDer);
        
        
        int nivelIzq=HallarNivel(arbol.raiz,nodoIzq->elemento.id,0) ;
        int nivelDer=HallarNivel(arbol.raiz,nodoDer->elemento.id,0);
        
        if (nivelIzq>=nivelDer ) {
             if (nodoIzq->derecha and valorIzq != nodoIzq->derecha->elemento.id) {
                 nodoIzq = nodoIzq->derecha;
                 nodoDer=nullptr;
            }else{
                 valorIzq=desapilar(pilaIzq);
                 cout<<nodoIzq->elemento.id<<"-"<<nodoIzq->elemento.esSkynerd<<"  ";
                 nodoIzq=nullptr;
                 nodoDer=nullptr;
            }
         }else{
            if (nodoDer->derecha and valorDer != nodoDer->derecha->elemento.id) {
                 nodoDer = nodoDer->derecha;
                 nodoIzq=nullptr;
            }else{
                 valorDer=desapilar(pilaDer);
                 cout<<nodoDer->elemento.id<<"-"<<nodoDer->elemento.esSkynerd<<"  ";
                 nodoDer=nullptr;
                 nodoIzq=nullptr;
            }
         }
        if(esPilaVacia(pilaIzq)){
            valorDer=supDer;
            break;
        }
        
    }
    //Ya solo falta terminar de hacerle el preorden al subarbol derecho
    while(1){
        while (nodoDer) {
                apilar(pilaDer, nodoDer->elemento.id);
                nodoDer = nodoDer->izquierda;
            }

            int supDer = cima(pilaDer);
            nodoDer = buscarRecursivo(arbol.raiz, supDer);

            if (nodoDer->derecha and valorDer != nodoDer->derecha->elemento.id) {
                nodoDer = nodoDer->derecha;
            }else{
                    valorDer= desapilar(pilaDer);
                    nodoDer=buscarRecursivo(arbol.raiz,valorDer);
                    cout << nodoDer->elemento.id << '-' << nodoDer->elemento.esSkynerd << "  ";
                    nodoDer=nullptr;
            }
            if(esPilaVacia(pilaDer)){
            break;
        }
    }
    cout<<arbol.raiz->elemento.id<<"-"<<arbol.raiz->elemento.esSkynerd<<endl;
}





void construir(struct Cola & cola){
    construir(cola.lista);
}

void construir(struct Lista & lista) {
    lista.cabeza = nullptr;
    lista.cola = nullptr;
    lista.longitud = 0;
}

bool esColaVacia(const struct Cola & cola){
    return esListaVacia(cola.lista);
}

const bool esListaVacia(const struct Lista & lista) {
    return lista.cabeza == nullptr;
}

void encolar(struct Cola & cola, int elemento){
    insertarAlFinal(cola.lista, elemento);
}

void insertarAlFinal(struct Lista & lista, int elemento) {
 
    struct Nodo * ultimoNodo = lista.cola;
    struct Nodo * nuevoNodo = crearNodo(elemento, nullptr);

    if (ultimoNodo == nullptr) /*Si la lista está vacia*/
        lista.cabeza = nuevoNodo; /*se inserta en la cabeza de la lista*/
    else //La lista ya tiene nodos
        ultimoNodo->siguiente = nuevoNodo;
    lista.cola = nuevoNodo;
    lista.longitud++;
}


struct Nodo * crearNodo(int elemento, struct Nodo * siguiente) {
    struct Nodo * nuevoNodo = new struct Nodo;
    nuevoNodo->elemento=elemento;
    nuevoNodo->siguiente = siguiente;
    return nuevoNodo;
}

int desencolar(struct Cola & cola){
    if(esColaVacia(cola)){
        cout<<"La cola está vacía no se puede desencolar"<<endl;
        exit(1);
    }
    int elemento = retornaCabeza(cola.lista);
    eliminaCabeza(cola.lista);
    return elemento;
}

int retornaCabeza(const struct Lista & lista){
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

NodoArbol *buscarRecursivo(struct NodoArbol * nodo, int dato){
    if(esNodoVacio(nodo))
        return nullptr;
    if(comparaABB(nodo->elemento.id, dato) == 0)
        return nodo;
    if(comparaABB(nodo->elemento.id, dato) == 1)
        return buscarRecursivo(nodo->izquierda, dato);
    else
        if(comparaABB(nodo->elemento.id, dato) == -1)
            return buscarRecursivo(nodo->derecha, dato);
}

int comparaABB(int elementoA, int elementoB){
    if(elementoA == elementoB) return 0;
    else if(elementoA < elementoB) return -1;
    else if(elementoA > elementoB) return 1;
}

void construir(struct Pila & pila){
    construir(pila.lista);
}

/*Determina si la pila está vacía*/
bool esPilaVacia(const struct Pila & pila){
    return esListaVacia(pila.lista);
}

void apilar(struct Pila & pila, int elemento){
    insertarAlInicio(pila.lista, elemento);

}

/* pop, elimina un elemento de la parte superior de la pila*/
int desapilar(struct Pila & pila){
    
    if (esPilaVacia(pila)){
        cout<<"La pila está vacía, por lo tanto no se puede desapilar"<<endl;
	return -1; //O cualquier otro valor que no se encuentre en la pila
    }	
    else{
        int elemento = cima(pila);
        eliminaCabeza(pila.lista);
        return elemento;
    }
}

/*examina un elemento situado en la parte superior de la pila*/
int cima(const struct Pila & pila){
    
    if (esPilaVacia(pila)){
	cout<<"La pila está vacía por lo tanto no posee cima"<<endl;
        return -1; //O cualquier otro valor que no se encuentre en la pila
    }		
    return retornaCabeza(pila.lista);
}

void insertarAlInicio(struct Lista & tad, int elemento) {

    /*Se va cambiar por la función crear nodo*/
    struct Nodo * nuevoNodo = new struct Nodo;
    nuevoNodo->elemento = elemento;
    nuevoNodo->siguiente = tad.cabeza;

    tad.cabeza = nuevoNodo;
    tad.longitud++;
}



int HallarNivel(NodoArbol *&raiz,int dato,int nivel){
    if(raiz==nullptr){
        return 0;
    }
    if(raiz->elemento.id==dato){
        return nivel;
    }else if(dato>raiz->elemento.id){
        HallarNivel(raiz->derecha,dato,nivel+1);
    }else{
        HallarNivel(raiz->izquierda,dato,nivel+1);
    }
}
int HallarNivel(NodoArbol *&raiz,int dato,int nivel){
    if(raiz==nullptr){
        return 0;
    }
    if(raiz->elemento.id==dato){
        return nivel;
    }else if(dato>raiz->elemento.id){
        HallarNivel(raiz->derecha,dato,nivel+1);
    }else{
        HallarNivel(raiz->izquierda,dato,nivel+1);
    }
}