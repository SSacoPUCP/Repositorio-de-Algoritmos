#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstddef>

using namespace std;

struct Elemento{
    int pos;
    char car;
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
void construir(struct ArbolBinario & arbol) ;
bool esNodoVacio(struct NodoArbol * raiz);
void insertar(struct ArbolBinarioBusqueda & arbol, Elemento elemento);
void insertarRecursivo(struct NodoArbol *& raiz, Elemento elemento);
void plantarArbolBinario(struct NodoArbol *& raiz, 
                    struct NodoArbol * izquierda, Elemento elemento, 
                    struct NodoArbol * derecha);
struct NodoArbol * crearNuevoNodo(struct NodoArbol * izquierda, Elemento elemento,
        struct NodoArbol * derecha);
int BuscarEnArbol(NodoArbol *raiz,char car,int pos);

int main(int argc, char** argv) {
    char palabra[12]="LOBO";
    
    int longitud=strlen(palabra);
    cout<<"BIENVENIDO AL JUEGO DE BALWORD"<<endl;
    cout<<"Descubre la palabra de "<<longitud<< " letras. tienes maximo 5 intentos."<<endl<<endl;
    
    ArbolBinarioBusqueda arbolBB;
    construir(arbolBB);
    Elemento elemento;
    for(int k=0; k<longitud;k++){
        elemento.car=palabra[k];
        elemento.pos=k+1;
        insertar(arbolBB,elemento); //Pide con txt pero asi esta bien, igual solo es un arbol hacia la derecha :v
    }
    
    for(int j=0;j<longitud;j++)cout<<"  __  ";
    cout<<endl;
    bool validez;
    char palUsuario[12];
    bool seEncuentra;
    for(int i=1;i<=5;i++){
        seEncuentra=true;
        cout<<"Intento "<<i<<": ";
        cin>>palUsuario;
        int tam=strlen(palUsuario);
        if(tam==longitud){
            for(int j=0;j<tam;j++){
                int tipo=BuscarEnArbol(arbolBB.arbolBinario.raiz,palUsuario[j],j+1);
                if(tipo==1){
                    cout<<"__  ";
                    seEncuentra=false;
                }else if(tipo==2){
                    cout<<palUsuario[j]<<"(x) "; 
                    seEncuentra=false;
                }else{
                    cout<<' '<<palUsuario[j]<<' ';
                    
                }
            }
        }else{
            cout<<"La longitud de la palabra no es la correcta. Intenta de nuevo"<<endl;
            seEncuentra=false;
        }
        cout<<endl;
        if(seEncuentra){
            cout<<"Felicitaciones por haber resuelto el reto"<<endl;
            exit(1);
        }
    }
    cout<<"Lo siento, se agotaron los intentos"<<endl;
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

void insertar(struct ArbolBinarioBusqueda & arbol, Elemento elemento){
    insertarRecursivo(arbol.arbolBinario.raiz, elemento);
}

void insertarRecursivo(struct NodoArbol *& raiz, Elemento elemento){
    if(esNodoVacio(raiz))
        plantarArbolBinario(raiz, nullptr, elemento, nullptr);
    else
        if(raiz->elemento.car > elemento.car)
            insertarRecursivo(raiz->izquierda, elemento);
        else
            if(raiz->elemento.car <= elemento.car)
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
    nuevo->elemento.car = elemento.car;
    nuevo->elemento.pos = elemento.pos;
    return nuevo;
}

int BuscarEnArbol(NodoArbol *raiz,char car,int pos){
    //1 no esta la letra 2 esta pero mal ubicada 3 esta y bien ubicada
    if(raiz==nullptr)return 1;
    if(raiz->elemento.car>car){
        BuscarEnArbol(raiz->izquierda,car,pos);
    }else if(car>raiz->elemento.car){
        BuscarEnArbol(raiz->derecha,car,pos);
    }else{
        //Se encontro la letra
        if(pos==raiz->elemento.pos){
            return 3;
        }else{
            if(BuscarEnArbol(raiz->derecha,car,pos)==3)return 3; //Por si las letras en la palabra se repiten EJ: LOBO (2 'O')
            return 2;
        }
    }
}