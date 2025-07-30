#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstdlib>
#define ITERACIONES 1000000
#define ALFA 0.30


using namespace std;

struct tobjeto{
    int id;
    int rendimiento;
};
struct tresultado{
    int disco;
    int tabla;
};

bool compara(tobjeto a,tobjeto b){
    return a.rendimiento>b.rendimiento;
}

int buscaind(vector<tobjeto>ptabla,int rcl){
    int cont=0;
    
    for(int i=0;i<ptabla.size();i++){
        if(rcl<=ptabla[i].rendimiento)
            cont++;
    }
    return cont;
}

void cargadiscos(tobjeto *tabla,tobjeto *disco,int n,int m){
    vector<tresultado> vfinal;
    int mejor=0;
    
    for(int i=0;i<ITERACIONES;i++){
        srand(time(NULL));
        int residual;
        vector<tobjeto> pdisco;
        vector<tobjeto> ptabla;
        vector<tresultado> pfinal;
        
        ptabla.insert(ptabla.begin(),tabla,tabla+n);
        pdisco.insert(pdisco.begin(),disco,disco+m);
        sort(ptabla.begin(),ptabla.begin()+n,compara);

        while(!ptabla.empty()){
            
            int betat=ptabla[0].rendimiento; //Beta
            int taut=ptabla[ptabla.size()-1].rendimiento; //Tau
            int rclt=round(betat-ALFA*(betat-taut));  //Hallamos el umbral
            vector<int> LRCT_indices;
            for (int i = 0; i < ptabla.size(); i++) {
                if (ptabla[i].rendimiento >= rclt)
                    LRCT_indices.push_back(i);
            }
            if (LRCT_indices.empty()) break;
            int elegidoIndex = rand() % LRCT_indices.size();
            int indat = LRCT_indices[elegidoIndex]; //Escogemos al azar dentro del LRC 
            
            
            // ahora le toca al disco
            sort(pdisco.begin(),pdisco.end(),compara);
            int betad=pdisco[0].rendimiento;
            int taud=pdisco[pdisco.size()-1].rendimiento;
            int rcld=betad-ALFA*(betad-taud);
            vector<int> LRCD_indices;
            for (int i = 0; i < pdisco.size(); i++) {
                if (pdisco[i].rendimiento >= rcld)
                    LRCD_indices.push_back(i);
            }
            if (LRCD_indices.empty()) break;
            elegidoIndex = rand() % LRCD_indices.size();
            int indad = LRCD_indices[elegidoIndex];
            
            if(pdisco[indad].rendimiento>=ptabla[indat].rendimiento){
                pdisco[indad].rendimiento-=ptabla[indat].rendimiento;
                pfinal.push_back({pdisco[indad].id,ptabla[indat].id});               
            }
            ptabla.erase(ptabla.begin()+indat);
        }
        
        
        
        
        sort(pdisco.begin(),pdisco.end(),compara);
        residual= pdisco[pdisco.size()-1].rendimiento;
        if(residual>mejor){
            mejor=residual;
            vfinal.clear();
            vfinal.insert(vfinal.begin(),pfinal.begin(),pfinal.end());
        }     
    }
    cout << "Mejor velocidad es:" <<mejor <<endl;
    for(int i=0;i<vfinal.size();i++)
        cout << vfinal[i].disco <<" "<<vfinal[i].tabla <<endl; 
    
}



int main(int argc, char** argv) {
    tobjeto tabla[]={{1,150},{2,100},{3,80},{4,50},{5,120},{6,10}};
    tobjeto disco[]={{1,250},{2,200},{3,200}};
    
    int n=sizeof(tabla)/sizeof(tabla[0]);
    int m=sizeof(disco)/sizeof(disco[0]);
    
    cargadiscos(tabla,disco,n,m);
    
    return 0;
}