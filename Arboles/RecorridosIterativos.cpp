#include <cstdlib>
#include <iostream>
#include <functional>
#include "ArbolBB.h"
#include "Pila.h"
#include "funcionesABB.h"
#include "funcionesAB.h"
#include "funcionesPila.h"
#include "funcionesLista.h"

using namespace std;

/*
 * 
 */

NodoArbol * buscarNodo(NodoArbol *raiz,int elemento){
    if (raiz->elemento==elemento){
        return raiz;
    }
    if (raiz->elemento<elemento){
        return buscarNodo(raiz->derecha,elemento);
    }
    else{
        return buscarNodo(raiz->izquierda,elemento);
    }
}

void recorrerPostOrdenIterativo(ArbolBinarioBusqueda arbol){
    int valor=0;
    Pila pila;
    NodoArbol * raiz;
    construir(pila);
    
    if (esArbolVacio(arbol.arbolBinario))
        return ;
    raiz = arbol.arbolBinario.raiz;
    while (1){
       /*Aqui estamos apilando todos los nodos izquierdos*/
       while (raiz){
           apilar(pila,raiz->elemento);
           raiz = raiz->izquierda;
       }
       int superior = cima(pila);
       raiz = buscarNodo(arbol.arbolBinario.raiz,superior);
       if (raiz->derecha && raiz->derecha->elemento != valor){
           raiz = raiz->derecha;
       }
       else{
           valor = desapilar(pila);
           cout << valor << " ";
           raiz = nullptr; /*Para no entrar al while de izquierda al regresar*/
       }
       if (esPilaVacia(pila)){
           break;
       }
    }
}


void recorreOrdenIterativo(ArbolBinarioBusqueda arbol){
    Pila pila;
    construir(pila);
    int fin=0;
    NodoArbol * raiz;
    int valor=0;
    raiz = arbol.arbolBinario.raiz;
    
    if (esArbolVacio(arbol.arbolBinario))
        return ;
    
    while(fin==0){
        while(raiz){
            apilar(pila,raiz->elemento);
            raiz = raiz->izquierda;
        }
        
        if(esPilaVacia(pila)){
            fin=1;
        }else{
            valor = desapilar(pila);
            cout << valor << " ";
            raiz= buscarNodo(arbol.arbolBinario.raiz,valor);
            raiz=raiz->derecha;
        }
    }
    destruirPila(pila);
    cout<<endl;
}



void recorrePreOrdenIterativo(ArbolBinarioBusqueda arbol){
    Pila pila;
    construir(pila);
    if (esArbolVacio(arbol.arbolBinario))
        return ;
    
    NodoArbol *raiz;
    raiz= arbol.arbolBinario.raiz;
    int valor=0;
    apilar(pila,raiz->elemento);
    
    while(!esPilaVacia(pila)){
        valor=desapilar(pila);
        cout<<valor<<" ";
        
        raiz = buscarNodo(arbol.arbolBinario.raiz,valor);
        if(raiz->derecha){
            apilar(pila,raiz->derecha->elemento);
        }
        if(raiz->izquierda){
            apilar(pila,raiz->izquierda->elemento);
        }
        
    }
    
}


int main(int argc, char** argv) {
    ArbolBinarioBusqueda arbol;
    construir(arbol);
    insertar(arbol,12);
    insertar(arbol,7);
    insertar(arbol,20);
    insertar(arbol,3);
    insertar(arbol,8);
    insertar(arbol,2);
    insertar(arbol,4);
    insertar(arbol,1);
    insertar(arbol,15);
    insertar(arbol,13);
    insertar(arbol,30);
    insertar(arbol,35);
    
    
    cout << "Recorrido postOrden De forma Recursiva: " << endl;
    recorrerPostOrden(arbol.arbolBinario);
    cout << endl;
    cout << "De forma Iterativa: " << endl;
    recorrerPostOrdenIterativo(arbol);
    cout<<endl<<endl;
    
    
    cout << "Recorrido orden De forma Recursiva: " << endl;
    recorrerEnOrden(arbol.arbolBinario);
    cout << endl;
    cout << "De forma Iterativa: " << endl;
    recorreOrdenIterativo(arbol);
    cout<<endl<<endl;
    
    
    cout << "Recorrido preOrden De forma Recursiva: " << endl;
    recorrerPreOrden(arbol.arbolBinario);
    cout << endl;
    cout << "De forma Iterativa: " << endl;
    recorrePreOrdenIterativo(arbol);
    cout<<endl<<endl;
    
    return 0;
}

