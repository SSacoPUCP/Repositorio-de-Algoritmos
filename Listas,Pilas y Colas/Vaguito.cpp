#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;

struct Nodo{
    int calorias;
    Nodo *siguiente;
};

struct Lista{
    int longitud;
    char categoria;
    Nodo *cabeza;
};

void ConstruirLista(Lista &lista,char tipo);
void ImprimirLista(Lista &lista);
void IngresarOrdenado(Lista &lista,int calorias);
Nodo *BuscarAnterior(Lista &lista,int calorias);
void CrearCromosoma(int *cromosoma,int n,int tamCrom);
void BorrarLista(Lista &lista);
void CopiarLista(Lista &lista,Lista &aux);
void CombinarListas(Lista &listaCombinada,Lista &lista1,Lista &lista2);
void QuitarElemento(Lista &lista);
int VerNodo(Lista &lista);
bool esListaVacia(Lista &lista);

int main(int argc, char** argv){
    Lista arrListas[6];
    int cantTipos,calorias;
    char tipo;
    cout<<"Ingrese cuantos tipos de producto hay: "<<endl;
    cin>>cantTipos;
    if(cantTipos>6)exit(1);
    for(int i=0;i<cantTipos;i++){
        cout<<"Ingrese el tipo de producto: ";
        cin >>tipo;
        cout<<endl;
        ConstruirLista(arrListas[i],tipo);
        int validar=1;
        
        while(validar==1){
            
            if(arrListas[i].longitud>0){
                cout<<"Calorias de los productos "<<tipo<<':';
                ImprimirLista(arrListas[i]);
            }
               
            cout<<"Ingrese la caloria del producto"<<endl;
            cin>>calorias;
            IngresarOrdenado(arrListas[i],calorias);
            cout<<"Desea agregar otra caloria de producto de tipo "<<arrListas[i].categoria<<" si(1),no(0)"<<endl;
            cin>>validar;
            system("cls");
        }
    }
    
    
    
    cout<<"---------FORMULA---------"<<endl;
    
    int cantCombinaciones;
    int cantProd,totalCalProd;
    bool cumpleReq[6]{false};
    Lista listaformula[6];
    
    for(int i=0;i<cantTipos;i++){
        ConstruirLista(listaformula[i],arrListas[i].categoria);
        
        int cantCal=arrListas[i].longitud;
        cantCombinaciones=pow(2,cantCal);
        cout<<cantCombinaciones<<endl;
        int cromosoma[cantCal];
        cout<<"Tipo de producto: "<<arrListas[i].categoria<<endl;
        cout<<"Cantidad de productos del tipo  "<<arrListas[i].categoria<<':';
        cin>>cantProd;
        cout<<endl;
        cout<<"Total de calorias maximo de todos los productos "<<arrListas[i].categoria<<':';
        cin>>totalCalProd;
        cout<<endl;
        
        for(int j=0;j<cantCombinaciones;j++){
            CrearCromosoma(cromosoma,j,cantCal);
            Nodo *recorrido=arrListas[i].cabeza;
            int totalCal=0;
            for(int k=0;k<cantCal;k++){
                if(cromosoma[k]){
                    int calorias=recorrido->calorias;
                    IngresarOrdenado(listaformula[i],calorias);
                    totalCal=totalCal+calorias;
                }
                recorrido=recorrido->siguiente;
            }
            if(totalCalProd>totalCal and cantProd==listaformula[i].longitud){
                cumpleReq[i]=true;
                break;
            }else{
                BorrarLista(listaformula[i]);
            }
        }
        if(cumpleReq[i]==false){
            cout<<"No hay posibles combinaciones para el tipo de producto"<<arrListas[i].categoria<<endl;
            listaformula[i].cabeza=nullptr;
        } //No hay ninguna combinacion de ese tipo que cumpla
        else{
            cout<<"Tras aplicar la formula en "<<arrListas[i].categoria<<" tenemos : ";
            ImprimirLista(listaformula[i]);
        }
    }
    //Toca combinar las listas
    Lista listaCombinada;
    Lista aux;
    ConstruirLista(listaCombinada,'A');
    ConstruirLista(aux,'A');
    for(int i=0;i<cantTipos;i++){
        if(i==0){
            CombinarListas(listaCombinada,listaformula[i],listaformula[i+1]);
        }else{
            CopiarLista(listaCombinada,aux);
            BorrarLista(listaCombinada);
            CombinarListas(listaCombinada,aux,listaformula[i+1]);
            BorrarLista(aux);
        }
    }
    cout<<"Calorias de productos a brindar: ";
    ImprimirLista(listaCombinada);
}

void ImprimirLista(Lista &lista){
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        cout<<recorrido->calorias<<' ';
        recorrido=recorrido->siguiente;
    }
    cout<<endl;
}
void IngresarOrdenado(Lista &lista,int calorias){
    Nodo *anterior=BuscarAnterior(lista,calorias);
    Nodo *nuevoNodo=new Nodo;
    nuevoNodo->calorias=calorias;
    nuevoNodo->siguiente=nullptr;
    if(anterior==nullptr){
        nuevoNodo->siguiente=lista.cabeza;
        lista.cabeza=nuevoNodo;
        
    }else{
        nuevoNodo->siguiente=anterior->siguiente;
        anterior->siguiente=nuevoNodo;
        
    }
    lista.longitud++;
    
}

void ConstruirLista(Lista &lista,char tipo){
    lista.cabeza=nullptr;
    lista.categoria=tipo;
    lista.longitud=0;
    
}

Nodo *BuscarAnterior(Lista &lista,int calorias){
    Nodo *anterior=nullptr;
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr and calorias>recorrido->calorias){
        anterior=recorrido;
        recorrido=recorrido->siguiente;
    }
    return anterior;
}

void CrearCromosoma(int *cromosoma,int n,int tamCrom){
    for(int i=0;i<tamCrom;i++){
        cromosoma[i]=0;
    }
    int i=0;
    while(n>0){
        cromosoma[i]=n%2;
        n=n/2;
        i++;
    }
}

void BorrarLista(Lista &lista){
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        Nodo *nodoEliminar=recorrido;
        recorrido=recorrido->siguiente;
        delete nodoEliminar;
    }
    lista.cabeza=nullptr;
    lista.longitud=0;
}

void CombinarListas(Lista &listaCombinada,Lista &lista1,Lista &lista2){
   
        while(!esListaVacia(lista1) and !esListaVacia(lista2)){
            int elemento1=VerNodo(lista1);
            int elemento2=VerNodo(lista2);
            if(elemento1<elemento2){
                QuitarElemento(lista1);
                IngresarOrdenado(listaCombinada,elemento1);
            }else{
                QuitarElemento(lista2);
                IngresarOrdenado(listaCombinada,elemento2);
            }
        }
        while(!esListaVacia(lista1)){
                int elemento1=VerNodo(lista1);   
                QuitarElemento(lista1);
                IngresarOrdenado(listaCombinada,elemento1);
        }
        while(!esListaVacia(lista2)){
                int elemento2=VerNodo(lista2);   
                QuitarElemento(lista2);
                IngresarOrdenado(listaCombinada,elemento2);
        }
        
}

bool esListaVacia(Lista &lista){
    return lista.cabeza==nullptr;
}

int VerNodo(Lista &lista){
    return lista.cabeza->calorias;
}

void QuitarElemento(Lista &lista){
    Nodo *nodoEliminar=lista.cabeza;
    if(lista.cabeza!=nullptr){
        lista.cabeza=lista.cabeza->siguiente;
        delete nodoEliminar;
        lista.longitud--;
    }else{
        cout<<"La lista esta vacia"<<endl;
        
    }
}
void CopiarLista(Lista &lista,Lista &aux){
    Nodo *recorrido=lista.cabeza;
    while(recorrido!=nullptr){
        int elemento=recorrido->calorias;
        IngresarOrdenado(aux,elemento);
        recorrido=recorrido->siguiente;
    }
}