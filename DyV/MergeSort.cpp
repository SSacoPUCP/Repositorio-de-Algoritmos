#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define N 15


void MergeSort(int *num,int inicio,int fin);
void Merge(int *num,int inicio,int med,int fin);


int main(int argc, char** argv){
    
    int num[9]={3,5,1,7,3,9,10,2,1};
    MergeSort(num,0,8);
    for(int i=0;i<9;i++)cout<<num[i]<<endl;
    
}

void MergeSort(int *num,int inicio,int fin){
    if(fin==inicio) return;
    int med= (inicio+fin)/2;
    MergeSort(num,inicio,med);
    MergeSort(num,med+1,fin);
    Merge(num,inicio,med,fin);
}

void Merge(int *num,int inicio,int med,int fin){
    int i=inicio,j=med+1;
    int aux[fin-inicio+1];
    int k=0;
    while(i<=med and j<=fin){
        if(num[i]>num[j]){
            aux[k]=num[j];
            j++;
        }else{
            aux[k]=num[i];
            i++;
        }
        k++;
    }
    while(j<=fin){
        aux[k]=num[j];
        j++;
        k++;
    }
    while(i<=med){
        aux[k]=num[i];
        i++;
        k++;
    }
    for(int p=0;p<k;p++){
        num[inicio+p]=aux[p];
    }
}
