#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>


using namespace std;


#define M 6
#define N 8

int BuscarMenor(int *num,int inicio,int fin);
int Menor(int a,int b);
int ContadorMenor(int *num,int inicio,int fin,int numMenor,int *dias,int &dia);
int ContarMezcla(int *num,int inicio,int med,int fin,int numMenor);
int MaximoTres(int a,int b,int c);
int Maximo(int a,int b);

int main(int argc, char** argv){
    int num[30]={98, 95, 92, 89, 91, 92, 89, 89, 92, 93, 94, 92, 91, 
            90, 88, 88, 88, 88, 90, 91, 88, 88, 90, 90, 92, 89, 90, 88, 90, 91};
    int numMenor=BuscarMenor(num,0,29);
    cout<<"El menor peso del mes fue "<<numMenor<<endl;
    int dias[30];
    int dia;
    for(int i=0;i<30;i++)dias[i]=i+1;
    int maxDias=ContadorMenor(num,0,29,numMenor,dias,dia);
    cout<<"El maximo de dias que se tuvo ese peso fue "<<maxDias<<endl;
    cout<<"En los dias: ";
    dia--;
    for(int i=0;i<maxDias;i++){
        cout<<dias[dia]<<' ';
        dia++;
    }
}

int BuscarMenor(int *num,int inicio,int fin){
    int med=(fin + inicio)/2;
    if(inicio==fin)return num[med];
    int menorIzq=BuscarMenor(num,inicio,med);
    int menorDer=BuscarMenor(num,med+1,fin);
    Menor(menorDer,menorIzq);
}

int Menor(int a,int b){
    if(a<b)return a;
    else return b;
}

int ContadorMenor(int *num,int inicio,int fin,int numMenor,int *dias,int &dia){
    int med=(inicio+fin)/2;
    if(inicio==fin){
        if(num[med]==numMenor){
            
            return 1;
        }else{
            return 0;
        }
    }
    int contIzq=ContadorMenor(num,inicio,med,numMenor,dias,dia);
    int contDer=ContadorMenor(num,inicio,med,numMenor,dias,dia);
    int contMezcla=ContarMezcla(num,inicio,med,fin,numMenor);
    dia=dias[med];
    return MaximoTres(contIzq,contDer,contMezcla);
}

int ContarMezcla(int *num,int inicio,int med,int fin,int numMenor){
    int contIzq=0;
    for(int i=med;i>inicio;i--){
        if(num[i]==numMenor){
            contIzq++;
        }else{
            break;
        }
    }
    int contDer=0;
    for(int i=med+1;i<fin;i++){
        if(num[i]==numMenor){
            contDer++;
        }else{
            break;
        }
    }
    int total=0;
    if(num[med]==numMenor and num[med]==num[med+1]){
        total=contDer+contIzq;
    }
    MaximoTres(total,contDer,contIzq);
}

int MaximoTres(int a,int b,int c){
    Maximo(Maximo(a,b),c);
}

int Maximo(int a,int b){
    if(a<b)return b;
    return a;
}