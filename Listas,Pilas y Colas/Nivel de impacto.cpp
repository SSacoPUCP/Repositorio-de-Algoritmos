#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <cinttypes>

using namespace std;

struct Nodo{
    int impacto;
    int categoria; 
    Nodo *siguiente;
};
struct Lista{
    int longitud;
    Nodo *cabeza;
};

void CrearLista(Lista &lista);
void IngresarDatos(Lista &lista,int categoria);
void IngresarNodoOrdenado(Lista &lista,int nivImpacto,int categoria);
Nodo *BuscarNodoAnterior(Lista &lista,int nivImpacto);
void ImprimirLista(Lista &lista);
void FusionarListas(Lista &listaA,Lista &listaB,Lista &listaC,Lista &listaD,Lista &listaE);
Nodo *ObtenerUltimoNodo(Lista &lista);
void AgregarInicioLista(Lista &lista,int elemento);
void OrdenarLista(Lista &lista);
void ImprimirFinal(Lista &listaA);

int main(int argc, char** argv) {
    
    //Primero nos dicen que ingresemos los datos
    
    Lista listaA;
    Lista listaB;
    Lista listaC;
    Lista listaD;
    Lista listaE;
    CrearLista(listaA);
    CrearLista(listaB);
    CrearLista(listaC);
    CrearLista(listaD);
    CrearLista(listaE);
      IngresarDatos(listaA,1);
      cout<<"La lista final de accesos no autorizados es: ";
      ImprimirLista(listaA);
      IngresarDatos(listaB,2);
      cout<<"La lista final de malware es: ";
      ImprimirLista(listaB);
      IngresarDatos(listaC,3);
      cout<<"La lista final de filtracion de datos es: ";
      ImprimirLista(listaC);
      IngresarDatos(listaD,4);
      cout<<"La lista final de denegacion de servicios es: ";
      ImprimirLista(listaD);
       IngresarDatos(listaE,5);
      cout<<"La lista final de incumplimientos de politica de seguridad es: ";
      ImprimirLista(listaE);
    //Vamos a unir las listas
      FusionarListas(listaA,listaB,listaC,listaD,listaE);
      ImprimirLista(listaA);
      OrdenarLista(listaA);      //Ordenamos las listas
      cout<<"La lista ordenada es: ";
      ImprimirFinal(listaA);
    return 0;
}

void CrearLista(Lista &lista){
    lista.cabeza=nullptr;
    lista.longitud=0;
}

void IngresarDatos(Lista &lista,int categoria){
    int validacion=1;
    int nivImpacto;
    while(validacion==1){
        ImprimirLista(lista);
        cout<<"Ingrese un nivel de impacto para la lista "<<categoria<<" (1-20): ";
        cin>>nivImpacto;
        system("cls");
        if(nivImpacto>0 and nivImpacto<=20){
            IngresarNodoOrdenado(lista,nivImpacto,categoria);
        }else{
            cout<<"No se ingreso un dato valido"<<endl;
            system("pause");
            system("cls");
        }
        cout<<"Quiere ingresar otro dato si(1), no(0)"<<endl;
        
        cin>>validacion;
        system("cls");
        
    }
    system("cls");
}

void IngresarNodoOrdenado(Lista &lista,int nivImpacto,int categoria){
    Nodo *nodoAnterior=BuscarNodoAnterior(lista,nivImpacto);
    Nodo *nuevoNodo= new Nodo;
    nuevoNodo->categoria=categoria;
    nuevoNodo->impacto=nivImpacto;
    nuevoNodo->siguiente=nullptr;
    if(nodoAnterior==nullptr){ //La lista esta vacia
        nuevoNodo->siguiente=lista.cabeza;
        lista.cabeza=nuevoNodo;
        
    }else{
        nuevoNodo->siguiente=nodoAnterior->siguiente;
        nodoAnterior->siguiente=nuevoNodo;
        
    }
    lista.longitud++;
}

Nodo *BuscarNodoAnterior(Lista &lista,int nivImpacto){
    Nodo *ultimo=nullptr;
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr and recorrido->impacto<nivImpacto){
        ultimo=recorrido;
        recorrido=recorrido->siguiente;
    }
    return ultimo;
}

void ImprimirLista(Lista &lista){
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        cout<<recorrido->impacto;
        recorrido=recorrido->siguiente;
        (recorrido==nullptr)? cout<<".":cout<<",";
    }
    cout<<endl;
}

void FusionarListas(Lista &listaA,Lista &listaB,Lista &listaC,Lista &listaD,Lista &listaE){
    Nodo *ultimoA=ObtenerUltimoNodo(listaA); 
    ultimoA->siguiente=listaB.cabeza;
    Nodo *ultimoB=ObtenerUltimoNodo(listaA); 
    ultimoB->siguiente=listaC.cabeza;
    Nodo *ultimoC=ObtenerUltimoNodo(listaA); 
    ultimoC->siguiente=listaD.cabeza;
     Nodo *ultimoD=ObtenerUltimoNodo(listaA); 
    ultimoD->siguiente=listaE.cabeza;
    listaA.longitud=listaA.longitud=listaB.longitud+listaC.longitud+listaD.longitud+listaE.longitud;
}


Nodo *ObtenerUltimoNodo(Lista &lista){
    Nodo *ultimo=nullptr;
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        ultimo=recorrido;
        recorrido=recorrido->siguiente;
    }
    return ultimo;
}

void AgregarInicioLista(Lista &lista,int elemento){
    Nodo *nuevoNodo=new Nodo;
    nuevoNodo->categoria=elemento;
    nuevoNodo->impacto=elemento;
    nuevoNodo->siguiente=lista.cabeza;
    lista.cabeza=nuevoNodo;
}

void OrdenarLista(Lista &lista){
    Nodo *recorrido=lista.cabeza;
   while(recorrido->siguiente!=nullptr){
        Nodo *recorridoAux=recorrido->siguiente;
        while(recorridoAux!=nullptr){
            
            if(recorrido->impacto<recorridoAux->impacto){
                int impacto=recorrido->impacto;
                int categoria=recorrido->categoria;
                recorrido->impacto=recorridoAux->impacto;
                recorrido->categoria=recorridoAux->categoria;
                recorridoAux->impacto=impacto;
                recorridoAux->categoria=categoria;
            }else if(recorrido->impacto==recorridoAux->impacto){
                if(recorrido->categoria>recorridoAux->categoria){
                    int impacto=recorrido->impacto;
                    int categoria=recorrido->categoria;
                    recorrido->impacto=recorridoAux->impacto;
                    recorrido->categoria=recorridoAux->categoria;
                    recorridoAux->impacto=impacto;
                    recorridoAux->categoria=categoria;
                }
             }
             
            recorridoAux=recorridoAux->siguiente;
        }
        recorrido=recorrido->siguiente;
        
    }
    
}

void ImprimirFinal(Lista &listaA){
    Nodo *recorrido=listaA.cabeza;
    cout<<"RESULTADO FINAL: "<<endl;
    while(recorrido!=nullptr){
        cout<<recorrido->impacto<<' ';
        switch(recorrido->categoria){
            case 1:
                cout<<'A';
                break;
            case 2: 
                cout<<'B';
                break;
            case 3: 
                cout<<'C';
                break;
            case 4: 
                cout<<'D';
                break;
            case 5:
                cout<<'E';
                break;
        }
        cout <<endl;
        recorrido=recorrido->siguiente;
    }
}




