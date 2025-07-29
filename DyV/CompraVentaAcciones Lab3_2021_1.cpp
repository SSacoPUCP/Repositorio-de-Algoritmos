#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

#define C 7
#define T 6

void MergeSort(int *acciones,char *empresas,int inicio,int fin);
void Merge(int *acciones,char *empresas,int inicio,int med,int fin);
int BusquedaBinariaMenor(int *acciones,int inicio,int fin,double ibd);
int main(int argc, char** argv){
    int acciones[T][C]={{8,4,5,6,7,1,2},
                                 {3,4,5,7,1,2,6},
                                 {5,6,5,2,1,6,8},
                                 {3,4,5,6,2,1,9},
                                 {3,4,5,4,5,3,2},
                                 {3,4,4,8,9,7,6}};
    
    
    double ibm=4.2;
    double ibd;
    for(int i=0;i<T;i++){
        char empresas[C]={'A','B','C','D','E','F','G'};
        int suma=0;
        for(int j=0;j<C;j++){
            suma=acciones[i][j]+suma;
        }
        ibd=(double)suma/C;
        MergeSort(acciones[i],empresas,0,C-1);
        cout<<"DIA "<<i+1<<"    "<<ibd<<setw(10);
        int sumaAcciones=0;
        if(ibd<=ibm){
            //Se compran acciones
            cout<<"Compra"<<setw(10);
            //Se deben comprar las acciones de las empresas que este <ibd
            int pos=BusquedaBinariaMenor(acciones[i],0,C-1,ibd); //Buscamos en que posicion quedaria el ibd
            //Regresa la posicion en la que el numero es mayor o igual que ibd y el anterior es menor
            for(int k=0;k<pos;k++){
                sumaAcciones+=acciones[i][k];
                cout<<empresas[k]<<' ';
            }
            cout<<sumaAcciones<<' ';
        }else{
            //Se venden acciones
            cout<<"Vende"<<setw(10);
            //Se deben vender las acciones de las empresas que este >ibd
            int pos=BusquedaBinariaMenor(acciones[i],0,C-1,ibd); //Buscamos en que posicion quedaria el ibd
            //Regresa la posicion en la que el numero es mayor o igual que ibd y el anterior es menor
            for(int k=pos;k<C;k++){
                sumaAcciones+=acciones[i][k];
                cout<<empresas[k]<<' ';
            }
            cout<<sumaAcciones<<' ';
        }
        cout<<endl;
    }
    
    
}

void MergeSort(int *acciones,char *empresas,int inicio,int fin){
    if(inicio==fin)return ;
    int med=(fin+inicio)/2;
    MergeSort(acciones,empresas,inicio,med);
    MergeSort(acciones,empresas,med+1,fin);
    Merge(acciones,empresas,inicio,med,fin);
}

void Merge(int *acciones,char *empresas,int inicio,int med,int fin){
    int i=inicio,j=med+1;
    int k=0;
    int auxA[fin-inicio+1];
    int auxE[fin-inicio+1];
    while(i<=med and j<=fin){
        if(acciones[i]<=acciones[j]){
            auxA[k]=acciones[i];
            auxE[k]=empresas[i];
            i++;
        }else{
            auxA[k]=acciones[j];
            auxE[k]=empresas[j];
            j++;
        }
        k++;
    }
    while(i<=med){
        auxA[k]=acciones[i];
        auxE[k]=empresas[i];
        i++;
        k++;
    }
    
    while(j<=fin){
        auxA[k]=acciones[j];
        auxE[k]=empresas[j];
        j++;
        k++;
    }
    for(int p=0;p<k;p++){
        acciones[inicio+p]=auxA[p];
        empresas[inicio+p]=auxE[p];
    }
}


int BusquedaBinariaMenor(int *acciones,int inicio,int fin,double ibd){
    if(inicio>fin)return -1;
    int med=(inicio+fin)/2;
    if(acciones[med]>ibd and acciones[med-1]<=ibd)return med;
    if(acciones[med]>ibd){
        BusquedaBinariaMenor( acciones, inicio, med, ibd);
    }else{
        BusquedaBinariaMenor( acciones, med+1, fin, ibd);
    }
}
