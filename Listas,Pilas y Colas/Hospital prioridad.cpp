#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;

struct Nodo{
    int fecha;
    char *cod;
    Nodo *siguiente;
};

struct Lista{
    int longitud;
    Nodo *cabeza;
    Nodo *maxima;
    Nodo *media;
    Nodo *minima; //cola
};

struct Cola{
    Lista lista;
};

void ConstruirCola(Cola &cola);
void ConstruirLista(Lista &lista);
void LeerDatos(Cola &cola,const char *nomb);
char *LeerCadenaExacta(ifstream &archDatos,char delim);
void AperturaDeArchivosLeer(ifstream &archDatos,const char *nomb);
int ConvertirFecha(int dd,int mm,int aa);
void EncolarPrioridad(int fecha,char *cod,Cola &cola);
int HallarPrioridad(int fecha);
Nodo *Desencolar(Cola &cola);
Nodo *RetornarCabeza(Lista &lista);
void Encolar(Cola &cola,Nodo *nuevoNodo);
void InsertarFinalLista(Lista &lista,Nodo *nuevoNodo);
Nodo *ObtenerUltimoNodo(Lista &lista);
void ImprimirLista(Cola &cola);

int main(int argc, char** argv){
    Cola cola;
    ConstruirCola(cola);
    LeerDatos(cola,"datos1.csv");
    Nodo *recorrido=cola.lista.cabeza;
    while(recorrido!=nullptr){
        int aa=recorrido->fecha/10000;
        int mm=(recorrido->fecha%10000)/100;
        int dd=recorrido->fecha%100;
        cout<<dd<<'/'<<mm<<'/'<<aa<<' '<<recorrido->cod<<endl;
        recorrido=recorrido->siguiente;
    }
    //ImprimirLista(cola);
}

void ConstruirCola(Cola &cola){
    ConstruirLista(cola.lista);
}

void ConstruirLista(Lista &lista){
    lista.longitud=0;
    lista.cabeza=nullptr;
    lista.maxima=nullptr;
    lista.media=nullptr;
    lista.minima=nullptr;
}

void LeerDatos(Cola &cola,const char *nomb){
    ifstream archDatos;
    AperturaDeArchivosLeer(archDatos,nomb);
    int dd,mm,aa,fecha;
    char c,*cod;
    while(1){
        archDatos>>dd;
        if(archDatos.eof())break;
        archDatos>>c>>mm>>c>>aa>>c;
        cod=LeerCadenaExacta(archDatos,'\n');
        fecha=ConvertirFecha(dd,mm,aa);
        EncolarPrioridad(fecha,cod,cola);
    }
}

char *LeerCadenaExacta(ifstream &archDatos,char delim){
    char *cad,buff[100];
    archDatos.getline(buff,100,delim);
    if(archDatos.eof())return nullptr;
    cad=new char[strlen(buff)+1];
    strcpy(cad,buff);
    return cad;
}

void AperturaDeArchivosLeer(ifstream &archDatos,const char *nomb){
    archDatos.open(nomb,ios::in);
    if(!archDatos){
        cout<<"Error el archivo no se pudo abrir"<<endl;
        exit(1);
    }
}

int ConvertirFecha(int dd,int mm,int aa){
    return aa*10000+mm*100+dd;
}


void EncolarPrioridad(int fecha,char *cod,Cola &cola){
    
    int prioridad=HallarPrioridad(fecha);
    Nodo *nuevoNodo=new Nodo;
    nuevoNodo->cod=cod;
    nuevoNodo->fecha=fecha;
    nuevoNodo->siguiente=nullptr;
    if(prioridad==1){
        if(cola.lista.cabeza==nullptr){
            cola.lista.cabeza=nuevoNodo;
            cola.lista.maxima=nuevoNodo;
        }else{
            if(cola.lista.maxima==nullptr){
                nuevoNodo->siguiente=cola.lista.cabeza;
                cola.lista.cabeza=nuevoNodo;
                cola.lista.maxima=nuevoNodo;
            }else{
                nuevoNodo->siguiente=cola.lista.maxima->siguiente;
                cola.lista.maxima->siguiente=nuevoNodo;
                cola.lista.maxima=nuevoNodo;
            }
        }
        cola.lista.longitud++;
    }else if(prioridad==2){
        if(cola.lista.media==nullptr){
            if(cola.lista.maxima==nullptr){
                cola.lista.cabeza=nuevoNodo;
                cola.lista.media=nuevoNodo;
            }else{
                nuevoNodo->siguiente=cola.lista.maxima->siguiente;
                cola.lista.maxima->siguiente=nuevoNodo;
                cola.lista.media=nuevoNodo;
            }
        }else{
            nuevoNodo->siguiente=cola.lista.media->siguiente;
            cola.lista.media->siguiente=nuevoNodo;
            cola.lista.media=nuevoNodo;
        }
        cola.lista.longitud++;
    }else if(prioridad==3){
        if(cola.lista.minima==nullptr){
            if(cola.lista.media==nullptr){
                if(cola.lista.maxima==nullptr){
                    cola.lista.cabeza=nuevoNodo;
                    cola.lista.minima=nuevoNodo;
                }else{
                    nuevoNodo->siguiente=cola.lista.maxima->siguiente;
                    cola.lista.maxima->siguiente=nuevoNodo;
                    cola.lista.minima=nuevoNodo;
                }
            }else{
                nuevoNodo->siguiente=cola.lista.media->siguiente;
                cola.lista.media->siguiente=nuevoNodo;
                cola.lista.minima=nuevoNodo;
                
            }
        }else{
            nuevoNodo->siguiente=cola.lista.minima->siguiente;
            cola.lista.minima->siguiente=nuevoNodo;
            cola.lista.minima=nuevoNodo;
        }
        cola.lista.longitud++;
    }
}


int HallarPrioridad(int fecha){
    int fechaActual=20241018;
    int anhos=(fechaActual-fecha)/10000;
    if(anhos>80){
        return 1;
    }else if(anhos<10){
        return 2;
    }else{
        return 3;
    }
}

void ImprimirLista(Cola &cola){
    //Siguiendo las leyes de colas
    
    Nodo *nuevoNodo=new Nodo;
    int cantCod=cola.lista.longitud;
    int dd,mm,aa;
    for(int i=0;i<cantCod;i++){
        nuevoNodo=Desencolar(cola);
        aa=nuevoNodo->fecha/10000;
        mm=(nuevoNodo->fecha%10000)/100;
        dd=nuevoNodo->fecha%100;
        cout<<"Hola"<<endl;
        cout<<dd<<'/'<<mm<<'/'<<aa<<' '<<nuevoNodo->cod<<endl;
        Encolar(cola,nuevoNodo);
    }
    
}


Nodo *Desencolar(Cola &cola){
    
    Nodo *nodoDesencolar=RetornarCabeza(cola.lista);
    if(nodoDesencolar==nullptr){
        cout<<"La cola esta vacia"<<endl;
        return nullptr;
    }
    cola.lista.cabeza=cola.lista.cabeza->siguiente;
    nodoDesencolar->siguiente=nullptr;
    cola.lista.longitud--;
    return nodoDesencolar;
}

Nodo *RetornarCabeza(Lista &lista){
    return lista.cabeza;
}

void Encolar(Cola &cola,Nodo *nuevoNodo){
    InsertarFinalLista(cola.lista,nuevoNodo);
}

void InsertarFinalLista(Lista &lista,Nodo *nuevoNodo){
    Nodo *ultimoNodo = ObtenerUltimoNodo(lista);
    if(ultimoNodo!=nullptr){
        ultimoNodo->siguiente=nuevoNodo;
    }else{
        nuevoNodo->siguiente=lista.cabeza;
        lista.cabeza=nuevoNodo;
    }
    lista.longitud++;
}

Nodo *ObtenerUltimoNodo(Lista &lista){
    Nodo *recorrido = lista.cabeza;
    Nodo *ultimo = nullptr;
    while(recorrido!=nullptr){
        ultimo=recorrido;
        recorrido=recorrido->siguiente;
    }
    return ultimo;
}