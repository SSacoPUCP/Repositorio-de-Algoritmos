#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

struct Elemento{
    int cantidad;
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

void insertar(struct ArbolBinarioBusqueda & arbol, Elemento& elemento);
void insertarRecursivo(struct NodoArbol *& raiz, Elemento& elemento);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, Elemento& elemento, 
                    struct NodoArbol * derecha);
bool esNodoVacio(struct NodoArbol * raiz) ;
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, Elemento& elemento,
        struct NodoArbol * derecha);
void construir(struct ArbolBinarioBusqueda & arbol);
void construir(struct ArbolBinario & arbol);
void enOrden(const struct ArbolBinarioBusqueda & arbol);
void recorrerEnOrden(const struct ArbolBinario & arbol);
void recorrerEnOrdenRecursivo(struct NodoArbol * nodo);
void imprimirNodo(struct NodoArbol * raiz);
void Despachar(ArbolBinario &arbol,int despachar);
void AgregarProductos(ArbolBinario &arbol,int lote,int cantAgregar);
struct NodoArbol * minimoArbol(struct NodoArbol * nodo);
NodoArbol *EliminarNodo(NodoArbol *raiz, int cantidad,int id) ;
bool BuscarProducto(NodoArbol *raiz,int lote,int cantAgregar,ArbolBinario &arbol);

int main(int argc, char** argv) {
    ifstream archProd("Productos.csv",ios::in);
    int id,cantidad;
    ArbolBinarioBusqueda arbolBB;
    construir(arbolBB);
    Elemento elemento;
    while(1){
        archProd>>cantidad;
        if(archProd.eof())break;
        archProd.get();
        archProd>>id;
        elemento.id=id;
        elemento.cantidad=cantidad;
        insertar(arbolBB,elemento);
    }
    enOrden(arbolBB);
    Despachar(arbolBB.arbolBinario,10);
    cout<<"SE DESPACHARON 10 PRODUCTOS"<<endl;
    enOrden(arbolBB);
    cout<<endl;
    cout<<endl;
    int lote,cantAgregar;
    cout<<"Selecciones un lote: "<<endl;
    cin>>lote;
    cout<<"Selecciones una cantidad: "<<endl;
    cin>>cantAgregar;
    AgregarProductos(arbolBB.arbolBinario,lote,cantAgregar);
    enOrden(arbolBB);
    return 0;
}

void construir(struct ArbolBinarioBusqueda & arbol){
    construir(arbol.arbolBinario);
}

void construir(struct ArbolBinario & arbol) {
    arbol.raiz = nullptr;
}
void insertar(struct ArbolBinarioBusqueda & arbol, Elemento &elemento){
    insertarRecursivo(arbol.arbolBinario.raiz, elemento);
}

void insertarRecursivo(struct NodoArbol *& raiz, Elemento &elemento){
    if(esNodoVacio(raiz))
        plantarArbolBinario(raiz, nullptr, elemento, nullptr);
    else
        if(raiz->elemento.cantidad > elemento.cantidad)
            insertarRecursivo(raiz->izquierda, elemento);
        else
            if(raiz->elemento.cantidad <= elemento.cantidad)
                insertarRecursivo(raiz->derecha, elemento);
}

void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, Elemento &elemento, 
                    struct NodoArbol * derecha){
    
    struct NodoArbol * nuevoNodo = crearNuevoNodo(izquierda, elemento, derecha);
    raiz = nuevoNodo;
}

bool esNodoVacio(struct NodoArbol * raiz) {
    return raiz == nullptr;
}

struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, Elemento &elemento,
        struct NodoArbol * derecha) {

    struct NodoArbol * nuevo = new struct NodoArbol;
    nuevo->derecha = derecha;
    nuevo->izquierda = izquierda;
    nuevo->elemento.cantidad = elemento.cantidad;
    nuevo->elemento.id = elemento.id;
    return nuevo;
}

void enOrden(const struct ArbolBinarioBusqueda & arbol){
    recorrerEnOrden(arbol.arbolBinario);
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
    cout<<setw(5)<<raiz->elemento.cantidad<<'-'<<raiz->elemento.id<<' ';
}

void Despachar(ArbolBinario &arbol,int despachar){
    while(despachar>0){
        NodoArbol *minimo=minimoArbol(arbol.raiz);
        if(minimo->elemento.cantidad>despachar){
            minimo->elemento.cantidad-=despachar;
            despachar=0;
        }else{
            despachar-=minimo->elemento.cantidad;
            NodoArbol *nodoEliminado=EliminarNodo(arbol.raiz,minimo->elemento.cantidad,minimo->elemento.id);
        }
    }
}

struct NodoArbol * minimoArbol(struct NodoArbol * nodo){
    if(esNodoVacio(nodo))
        return nodo;
    if(esNodoVacio(nodo->izquierda))
        return nodo;
    return minimoArbol(nodo->izquierda);
}

NodoArbol *EliminarNodo(NodoArbol *raiz, int cantidad,int id) {
    if (esNodoVacio(raiz)) {
        return raiz;
    }
    if (raiz->elemento.cantidad <= cantidad and raiz->elemento.id!=id) {
        raiz->derecha=EliminarNodo(raiz->derecha, cantidad,id);
    } else {
        if (raiz->elemento.cantidad > cantidad and raiz->elemento.id!=id) {
            raiz->izquierda=EliminarNodo(raiz->izquierda, cantidad,id);
        } else {
            //Se encontro el elemento
            if (esNodoVacio(raiz->derecha)) {
                NodoArbol *hijo = raiz->izquierda;
                delete raiz;
                return hijo;
            } else {
                if (esNodoVacio(raiz->izquierda)) {
                    NodoArbol *hijo = raiz->derecha;
                    delete raiz;
                    return hijo;
                }else{
                    //Tiene ambos hijos
                    NodoArbol *nodoMinimo=minimoArbol(raiz->derecha);
                    raiz->elemento.cantidad=nodoMinimo->elemento.cantidad;
                    raiz->elemento.id=nodoMinimo->elemento.id;
                    raiz->derecha=EliminarNodo(raiz->derecha,nodoMinimo->elemento.cantidad,nodoMinimo->elemento.id);
                }
            }
        }
    }
    return raiz;
}

void AgregarProductos(ArbolBinario &arbol,int lote,int cantAgregar){
    bool seEncontro=BuscarProducto(arbol.raiz,lote,cantAgregar,arbol);
    if(!seEncontro){
        Elemento elemento;
        elemento.cantidad=cantAgregar;
        elemento.id=lote;
        insertarRecursivo(arbol.raiz,elemento);
    }
}

bool BuscarProducto(NodoArbol *raiz,int lote,int cantAgregar,ArbolBinario &arbol){
    if(raiz==nullptr){
        return false;
    }
    if(raiz->elemento.id==lote){
        
        raiz->elemento.cantidad+=cantAgregar;
        NodoArbol *nodoReemplazo=EliminarNodo(arbol.raiz,cantAgregar,lote);
        Elemento elemento;
        elemento.cantidad=cantAgregar;
        elemento.id=lote;
        insertarRecursivo(arbol.raiz,elemento);
        return true;
    }
    bool izq=BuscarProducto(raiz->izquierda,lote,cantAgregar,arbol);
    bool der=BuscarProducto(raiz->derecha,lote,cantAgregar,arbol);
    if(izq or der){
        return true;
    }else{
        return false;
    }
}
