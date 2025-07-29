#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstddef>

using namespace std;

/*
 * 
 */

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
void insertar(struct ArbolBinarioBusqueda & arbol, int elemento);
void insertarRecursivo(struct NodoArbol *& raiz, int elemento);
bool esNodoVacio(struct NodoArbol * raiz) ;
void plantarArbolBinario(struct ArbolBinario & arbol, struct NodoArbol * izquierda, 
                         int elemento, struct NodoArbol * derecha);
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, int elemento,
        struct NodoArbol * derecha);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, int elemento, 
                    struct NodoArbol * derecha);
struct NodoArbol * maximoArbol(struct NodoArbol * nodo);
NodoArbol *BalancearArbol(NodoArbol *raiz);
NodoArbol *BalanceoNodo(NodoArbol *nodo);
int alturaRecursivo(struct NodoArbol * nodo);
int maximo(int a, int b);
NodoArbol *RotarDerecha(NodoArbol *nodo);
NodoArbol *RotarIzquierda(NodoArbol *nodo);
int EncontrarAncestro(NodoArbol *nodo,int ancestro,int a,int b);
void recorrerEnOrden(const struct ArbolBinario & arbol);
void recorrerEnOrdenRecursivo(struct NodoArbol * nodo);
void imprimirNodo(struct NodoArbol * raiz);
void recorrerPostOrdenRecursivo(struct NodoArbol * nodo);
void recorrerPostOrden(const struct ArbolBinario & arbol);
bool SumaParcialArboles(ArbolBinario &arbol,ArbolBinario &arbol2,int ancestro);
NodoArbol *SumaParcialArbolesRecursivo(NodoArbol *raiz);
void RecorrerValidar(NodoArbol *raiz,NodoArbol *parbol,int ancestro);
void RealizarSuma(NodoArbol *raiz,NodoArbol *parbol);
bool VerificarABB(NodoArbol *raiz);

int main(int argc, char** argv) {
    int numero;
    ArbolBinarioBusqueda arbol; 
    construir(arbol);
    int arrNum[8];
    for(int i=0;i<8;i++){
        cout<<"Escriba el numero "<<i+1<<": ";
        cin>>numero;
        cout<<endl;
        arrNum[i]=numero;
        for(int j=0;j<i;j++){
            if(arrNum[j]==numero){
                NodoArbol *nodo=maximoArbol(arbol.arbolBinario.raiz);
                numero=numero+nodo->elemento;
                arrNum[i]=numero;
            }
        }
        insertar(arbol,numero);
    }
    recorrerPostOrden(arbol.arbolBinario);
    cout<<endl;
    arbol.arbolBinario.raiz=BalancearArbol(arbol.arbolBinario.raiz);
    cout<<"Despues del balanceo"<<endl;
    recorrerPostOrden(arbol.arbolBinario);
    cout<<endl;
    int ancestro=EncontrarAncestro(arbol.arbolBinario.raiz,ancestro,1,4);
    cout<<"El ancestro es : "<<ancestro<<endl;
    
    ArbolBinario arbol2;
    construir(arbol2);
    //Caso1
    plantarArbolBinario(arbol2.raiz,nullptr,3,nullptr);
    plantarArbolBinario(arbol2.raiz->izquierda,nullptr,1,nullptr);
    plantarArbolBinario(arbol2.raiz->izquierda->derecha,nullptr,2,nullptr);
    plantarArbolBinario(arbol2.raiz->derecha,nullptr,5,nullptr);
    plantarArbolBinario(arbol2.raiz->derecha->izquierda,nullptr,4,nullptr);
    plantarArbolBinario(arbol2.raiz->derecha->derecha,nullptr,6,nullptr);
    plantarArbolBinario(arbol2.raiz->derecha->derecha->derecha,nullptr,7,nullptr);
    //Caso2
//    plantarArbolBinario(arbol2.raiz,nullptr,4,nullptr);
//    plantarArbolBinario(arbol2.raiz->izquierda,nullptr,-2,nullptr);
//    plantarArbolBinario(arbol2.raiz->izquierda->izquierda,nullptr,-3,nullptr);
//    plantarArbolBinario(arbol2.raiz->izquierda->derecha,nullptr,-1,nullptr);
//    plantarArbolBinario(arbol2.raiz->izquierda->derecha->derecha,nullptr,0,nullptr);
//    plantarArbolBinario(arbol2.raiz->derecha,nullptr,6,nullptr);
//    plantarArbolBinario(arbol2.raiz->derecha->izquierda,nullptr,5,nullptr);
//    plantarArbolBinario(arbol2.raiz->derecha->derecha,nullptr,7,nullptr);
    
    bool busqueda=SumaParcialArboles(arbol.arbolBinario,arbol2,ancestro);
    if(busqueda)cout<<"El arbol creado es de busqueda"<<endl;
    else cout<<"El arbol creado no es de busqueda"<<endl;
    
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

void plantarArbolBinario(struct ArbolBinario & arbol, struct NodoArbol * izquierda, 
                         int elemento, struct NodoArbol * derecha) {
    
    struct NodoArbol * nuevoNodo = crearNuevoNodo(izquierda, elemento, derecha);
    arbol.raiz = nuevoNodo;

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

struct NodoArbol * maximoArbol(struct NodoArbol * nodo){
    if(esNodoVacio(nodo))
        return nodo;
    if(esNodoVacio(nodo->derecha))
        return nodo;
    return maximoArbol(nodo->derecha);
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

void recorrerPostOrden(const struct ArbolBinario & arbol){
    recorrerPostOrdenRecursivo(arbol.raiz);
}
void recorrerPostOrdenRecursivo(struct NodoArbol * nodo){
    if(not esNodoVacio(nodo)){
        recorrerPostOrdenRecursivo(nodo->izquierda);
        recorrerPostOrdenRecursivo(nodo->derecha);
        imprimirNodo(nodo);
    }
}

void imprimirNodo(struct NodoArbol * raiz){
    cout<<setw(5)<<raiz->elemento;
}

NodoArbol *BalancearArbol(NodoArbol *raiz){
    if(esNodoVacio(raiz))return nullptr;
    raiz->izquierda=BalancearArbol(raiz->izquierda);
    raiz->derecha=BalancearArbol(raiz->derecha);
    raiz=BalanceoNodo(raiz);
    return raiz;
}

NodoArbol *BalanceoNodo(NodoArbol *nodo){
    int factorBalanceo=alturaRecursivo(nodo->izquierda)-alturaRecursivo(nodo->derecha);
    if(factorBalanceo>1){//El subarbol izquierdo es mas alto
        if(alturaRecursivo(nodo->izquierda->izquierda)>=alturaRecursivo(nodo->izquierda->derecha)){
            nodo=RotarDerecha(nodo); //Rotacion simple derecha
        }else{
            nodo->izquierda=RotarIzquierda(nodo->izquierda);//Rotacion doble derecha
            nodo=RotarDerecha(nodo);
        }
    }else if(factorBalanceo<-1){//El subarbol derecho es mas alto
        if(alturaRecursivo(nodo->derecha->derecha)>=alturaRecursivo(nodo->derecha->izquierda)){
            nodo=RotarIzquierda(nodo); //Rotacion simple izquierda
        }else{
            nodo->derecha=RotarDerecha(nodo->derecha); //Rotacion doble izquierda
            nodo=RotarIzquierda(nodo);
        }
        
    }
    return nodo;
}

int alturaRecursivo(struct NodoArbol * nodo){
    if(esNodoVacio(nodo))
        return 0;
    else if(esNodoVacio(nodo->izquierda) and esNodoVacio(nodo->derecha))
        return 0;
    else
        return 1 + maximo(alturaRecursivo(nodo->izquierda), alturaRecursivo(nodo->derecha));
}

int maximo(int a, int b){
    return a >= b ? a : b;
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

int EncontrarAncestro(NodoArbol *nodo,int ancestro,int a,int b){
    if(nodo!=nullptr){
        if(a>nodo->elemento and b>nodo->elemento){
            return EncontrarAncestro(nodo->derecha,ancestro,a,b);
        }else if(a<nodo->elemento and b<nodo->elemento){
            return EncontrarAncestro(nodo->izquierda,ancestro,a,b);
        }else{
            return nodo->elemento;;
        }
    }
    return -1;
}

bool SumaParcialArboles(ArbolBinario &arbol,ArbolBinario &arbol2,int ancestro){
    ArbolBinario arbolR;
    NodoArbol *parbol=SumaParcialArbolesRecursivo(arbol.raiz);
    arbolR.raiz=parbol;
    NodoArbol *parbol2=arbol2.raiz;
    RecorrerValidar(arbolR.raiz,parbol2,ancestro);
    //Debemos verificar que arbolR sea un ABB
    cout<<"El arbol obtenido es "<<endl;
    recorrerEnOrdenRecursivo(arbolR.raiz);
    cout<<endl;
    return VerificarABB(arbolR.raiz);
}

NodoArbol *SumaParcialArbolesRecursivo(NodoArbol *raiz){
    if(raiz==nullptr)return raiz;
    NodoArbol *izq,*der,*parbol;
    izq=SumaParcialArbolesRecursivo(raiz->izquierda);
    der=SumaParcialArbolesRecursivo(raiz->derecha);
    parbol=crearNuevoNodo(izq,raiz->elemento,der);
    return parbol;
}

void RecorrerValidar(NodoArbol *raiz,NodoArbol *parbol,int ancestro){
    
    if(ancestro>raiz->elemento){
        RecorrerValidar(raiz->derecha,parbol->derecha,ancestro);
    }else if(ancestro<raiz->elemento){
        RecorrerValidar(raiz->izquierda,parbol->izquierda,ancestro);
    }
    if(ancestro==raiz->elemento){
        RealizarSuma(raiz,parbol);
    }
}

void RealizarSuma(NodoArbol *raiz,NodoArbol *parbol){
    if(esNodoVacio(raiz)) return ;
    if(not esNodoVacio(parbol)){
        raiz->elemento+=parbol->elemento;
        RealizarSuma(raiz->izquierda,parbol->izquierda);
        RealizarSuma(raiz->derecha,parbol->derecha);
    }
}

bool VerificarABB(NodoArbol *raiz){
    if(esNodoVacio(raiz))return true;
    bool verIzq=false,verDer=false;
    bool der=false,izq=false;
    if(esNodoVacio(raiz->izquierda)){
        verIzq=true;
    }else{
        if(raiz->elemento>raiz->izquierda->elemento){
            verIzq=true;
        }
    }
    
    if(esNodoVacio(raiz->derecha)){
        verDer=true;
    }else{
        if(raiz->elemento<raiz->derecha->elemento){
            verDer=true;
         }
    }
    
    if(verIzq and verDer){
         izq=VerificarABB(raiz->izquierda);
         der=VerificarABB(raiz->derecha);
    }else{
        return false;
    }
    if(izq and der)return true;
    else return false;
}