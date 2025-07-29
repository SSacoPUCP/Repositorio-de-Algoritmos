#include <string>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <iterator>

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
    int elemento; /*Dato que cambia por double, char, struct */
    struct Nodo * siguiente; /*puntero a una variable de tipo struct Nodo*/
};


struct Lista {
    struct Nodo * cabeza; /*apunta al inicio de la lista*/
    int longitud; /*guarda la longitud de la lista*/
};

struct Pila{
    struct Lista lista;
};

void construir(struct ArbolBinarioBusqueda & arbol);
void construir(struct ArbolBinario & arbol) ;
bool esNodoVacio(struct NodoArbol * raiz) ;
bool esArbolVacio(const struct ArbolBinario & arbol);
void insertar(struct ArbolBinarioBusqueda & arbol, int elemento);
void insertarRecursivo(struct NodoArbol *& raiz, int elemento);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, int elemento, 
                    struct NodoArbol * derecha);
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, int elemento,
        struct NodoArbol * derecha);
int altura(const struct ArbolBinario & arbol);
int alturaRecursivo(struct NodoArbol * nodo);
int BuscarCombinaciones(ArbolBinarioBusqueda &arbolBB,int nivel,int combinaciones[3][3],int pesos[9][3]);
int BuscarCombinacionesRec(NodoArbol *nodo,int nivel,int numClaveComb,int indiceNivel,int combinaciones[3][3],int pesos[9][3]);
int ContadorCombinaciones(NodoArbol *nodo,int *combinaciones,int pesos[9][3],int nroEmocion);
int maximo(int a, int b);
void construir(struct Lista & tad);
void construir(struct Pila & pila);
bool esPilaVacia(const struct Pila & pila);
const bool esListaVacia(const struct Lista & tad);
void apilar(struct Pila & pila, int elemento);
void insertarAlInicio(struct Lista & tad, int elemento) ;
int desapilar(struct Pila & pila);
void eliminaCabeza(struct Lista & tad) ;
int cima(const struct Pila & pila);
int retornaCabeza(const struct Lista & tad);

int main(int argc, char** argv) {

    int pesos[9][3]={{180,200,0},
                                {140,230,80},
                                {240,100,0},
                                {280,0,0},
                                {250,0,0},
                                {260,120,0},
                                {160,240,0},
                                {120,80,0},
                                {150,230,90}};
    
    int combinaciones[3][3]={{5,8,1},
                                                {4,1,2},
                                                {2,7,8}};
    
    ArbolBinarioBusqueda arbolBB;
    construir(arbolBB);
    insertar(arbolBB,180);
    insertar(arbolBB,120);
    insertar(arbolBB,100);
    insertar(arbolBB,80);
    insertar(arbolBB,90);
    insertar(arbolBB,150);
    insertar(arbolBB,140);
    insertar(arbolBB,160);
    insertar(arbolBB,250);
    insertar(arbolBB,230);
    insertar(arbolBB,200);
    insertar(arbolBB,240);
    insertar(arbolBB,280);
    insertar(arbolBB,260);
    
    int niveles=altura(arbolBB.arbolBinario);
    
    for(int i=0;i<3;i++){
        cout<<"El nivel "<<i+1<<" tiene "<<BuscarCombinaciones(arbolBB,i,combinaciones,pesos)<<" combinaciones"<<endl;
    }
    
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

bool esArbolVacio(const struct ArbolBinario & arbol) {
    return esNodoVacio(arbol.raiz);
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

int altura(const struct ArbolBinario & arbol){
    return alturaRecursivo(arbol.raiz);
}

int alturaRecursivo(struct NodoArbol * nodo){
    if(esNodoVacio(nodo))
        return 0;
    else if(esNodoVacio(nodo->izquierda) and esNodoVacio(nodo->derecha))
        return 0;
    else
        return 1 + maximo(alturaRecursivo(nodo->izquierda), alturaRecursivo(nodo->derecha));
}

int BuscarCombinaciones(ArbolBinarioBusqueda &arbolBB,int nivel,int combinaciones[3][3],int pesos[9][3]){
    return BuscarCombinacionesRec(arbolBB.arbolBinario.raiz,nivel,0,0,combinaciones,pesos);
}

int BuscarCombinacionesRec(NodoArbol *nodo,int nivel,int numClaveComb,int indiceNivel,int combinaciones[3][3],int pesos[9][3]){
    if(esNodoVacio(nodo))return 0;
    
    
    if(numClaveComb==0 and nivel==indiceNivel){
        Pila pila;
        construir(pila);
        for(int i=0;i<9;i++){
            for(int j=0;j<3;j++){
                if(pesos[i][j]==nodo->elemento){
                    apilar(pila,i);
                }
            }
        }
        int combinacionesEnNivel=0;
        while(!esPilaVacia(pila)){
            int emocion=desapilar(pila);
            int numComb=-1,nroEmocion=0;
            for(int i=0;i<3;i++){
                if(combinaciones[i][0]==emocion){
                    numComb=i;
                }
            }
            
            if(numComb!=-1){
                combinacionesEnNivel+=ContadorCombinaciones(nodo->izquierda,combinaciones[numComb],pesos,nroEmocion+1)+ContadorCombinaciones(nodo->derecha,combinaciones[numComb],pesos,nroEmocion+1);
            }
        }
        
        return combinacionesEnNivel;
    }
    return BuscarCombinacionesRec(nodo->izquierda,nivel,numClaveComb,indiceNivel+1,combinaciones,pesos)+BuscarCombinacionesRec(nodo->derecha,nivel,numClaveComb,indiceNivel+1,combinaciones,pesos);
}

int ContadorCombinaciones(NodoArbol *nodo,int *combinaciones,int pesos[9][3],int nroEmocion){
    if(esNodoVacio(nodo))return 0;
    
    Pila pila;
    construir(pila);
    for(int i=0;i<9;i++){
        for(int j=0;j<3;j++){
            if(nodo->elemento==pesos[i][j]){
                apilar(pila,i);
            }
        }
    }
    
    while(!esPilaVacia(pila)){
        int emocion=desapilar(pila);
        if(emocion==combinaciones[nroEmocion]){
            if(nroEmocion==2){
                return 1;
            }else{
                return ContadorCombinaciones(nodo->izquierda,combinaciones,pesos,nroEmocion+1)+ContadorCombinaciones(nodo->derecha,combinaciones,pesos,nroEmocion+1);
            }
        }
    }
    return 0;
}
void construir(struct Lista & tad) {
    tad.cabeza = nullptr;
    tad.longitud = 0;
}

void construir(struct Pila & pila){
    construir(pila.lista);
}

/*Determina si la pila está vacía*/
bool esPilaVacia(const struct Pila & pila){
    return esListaVacia(pila.lista);
}

/*devuelve si la lista esta vacia 1, caso contrario 0 */
const bool esListaVacia(const struct Lista & tad) {
    return tad.cabeza == nullptr;
}

void apilar(struct Pila & pila, int elemento){
    insertarAlInicio(pila.lista, elemento);
}

void insertarAlInicio(struct Lista & tad, int elemento) {

    /*Se va cambiar por la función crear nodo*/
    struct Nodo * nuevoNodo = new struct Nodo;
    nuevoNodo->elemento = elemento;
    nuevoNodo->siguiente = tad.cabeza;

    tad.cabeza = nuevoNodo;
    tad.longitud++;
}

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

void eliminaCabeza(struct Lista & tad) {
    struct Nodo * nodoAEliminar = tad.cabeza;
    if (nodoAEliminar != nullptr) {
        tad.cabeza = tad.cabeza->siguiente;
        delete nodoAEliminar;
        tad.longitud--;
    }
}

int cima(const struct Pila & pila){
    
    if (esPilaVacia(pila)){
	cout<<"La pila está vacía por lo tanto no posee cima"<<endl;
        return -1; //O cualquier otro valor que no se encuentre en la pila
    }		
    return retornaCabeza(pila.lista);
}

int retornaCabeza(const struct Lista & tad){
    return tad.cabeza->elemento;
}

int maximo(int a, int b){
    return a >= b ? a : b;
}