#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

#define N 15

void MergeSort(int *num,int inicio,int fin);
void Merge(int *num,int inicio,int med,int fin);
int BuscarRepetido(int *bitacora,int inicio,int fin);

int main(int argc, char** argv){
    int bitacora[9]={3,3,1,1,5,5,8,8,8};
    MergeSort(bitacora,0,9-1);
    for(int i=0;i<9;i++)cout<<bitacora[i]<<' ';
    cout<<endl;
    cout<<"El que entro y no salio fue el:  "<<BuscarRepetido(bitacora,0,9-1);

}

void MergeSort(int *num,int inicio,int fin){
    int med=(fin+inicio)/2;
    if(inicio==fin)return ;
    MergeSort(num,inicio,med);
    MergeSort(num,med+1,fin);
    Merge(num,inicio,med,fin);
}

void Merge(int *num,int inicio,int med,int fin){
    int i=inicio,j=med+1;
    int aux[fin-inicio+1];
    int k=0;
    while(i<=med and j<=fin){
        if(num[i]<num[j]){
            aux[k]=num[i];
            i++;
        }else{
            aux[k]=num[j];
            j++;
        }
        k++;
    }
    while(i<=med){
        aux[k]=num[i];
        i++;
        k++;
    }
    
    while(j<=fin){
        aux[k]=num[j];
        j++;
        k++;
    }
    for(int p=0;p<k;p++){
        num[inicio+p]=aux[p];
    }
}

int BuscarRepetido(int *bitacora,int inicio,int fin){
    int med=(fin + inicio)/2;
    if(inicio>fin)return -1;
    if(inicio==fin){
        if(bitacora[med]==bitacora[med-1] and bitacora[med]==bitacora[med-2]){
            return bitacora[med];
        }else{
            return -1;
        }
    }
    if(med%2==0){
        if(bitacora[med]==bitacora[med+1]){
            BuscarRepetido(bitacora,med+1,fin);
        }else{
            BuscarRepetido(bitacora,inicio,med);
        }
    }else{
        if(bitacora[med]==bitacora[med-1]){
            BuscarRepetido(bitacora,med+1,fin);
        }else{
            BuscarRepetido(bitacora,inicio,med);
        }
    }
}
