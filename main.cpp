#include <iostream>
#include "ClaseEstado.h"
#include "ClaseTransicion.h"
#include "ClaseAFN.h"
#include "ClaseAFD.h"
#include <vector>

using namespace std;
Estado Edo_byID (vector<Estado> Edo,int EdoID);
void Ver_Alfabeto (vector<char> Alf);
void Ver_ConjAcept (vector<Estado> Conj);

int main(){

AFN automata = AFN();
AFN a1;
a1 = automata.AFN_Basico('a','c',0);

AFN automata2 = AFN();
AFN a2;
a2 = automata2.AFN_Basico('d','f',a1.get_Contador());

a1 = a1.AFN_Union(a2);
a1 = a1.AFN_CerrKleene();


AFN automata3 = AFN();
AFN a3;
a3 = automata3.AFN_Basico('g','i',a1.get_Contador());

a3 = a3.AFN_CerrPOS();

AFN automata4 = AFN();
AFN a4;
a4 = automata4.AFN_Basico('w','y',a3.get_Contador());




AFN e =AFN();
e.AFN_UnionEspecial(a1,10,a4.Contador);
e.AFN_UnionEspecial(a3,20,a4.Contador);
e.AFN_UnionEspecial(a4,30,a4.Contador);
//automata.Mx_Adyacencia(e);

//Ver_Alfabeto(e.Alfabeto);
//Ver_ConjAcept(e.EdoAcept);

AFD nuevo = AFD();
nuevo = nuevo.Conv_AFNaAFD(e);

/*Ver_Alfabeto(nuevo.Alfabeto);//quitar epsilon

int t = (int) e.EdoAcept.size();
for(int i=0;i<t;i++){
    cout<<"------>"<<e.EdoAcept.at(i).get_IdEstado()<<"Token: "<<e.EdoAcept.at(i).get_Token()<<endl;
}

t = (int) nuevo.get_EdoAcept().size();
for(int i=0;i<t;i++){
    cout<<"<>"<<nuevo.get_EdoAcept().at(i).get_ConIj_ID()<<"Token: "<<nuevo.get_EdoAcept().at(i).Token<<endl;
}*/
vector<ConIj> temp;
temp = nuevo.get_EdoAFN();
/*int tam = (int) temp.size(),tam_;
for(int i=0; i<tam ; i++){
    cout<<temp.at(i).get_ConIj_ID()<<"Aceptacion:"<<temp.at(i).Acept<<endl;
    cout<<"Token: "<<temp.at(i).Token<<endl;
    cout<<"ESTADOS"<<endl;
    tam_ = (int) temp.at(i).get_ConIj_Edos().size();
    for(int j=0;j<tam_;j++){
        cout<<temp.at(i).get_ConIj_Edos().at(j).get_IdEstado()<<",";
    }
    cout<<endl;
    tam_ = (int) temp.at(i).Trans1.size();
    for(int j=0;j<tam_;j++){
        cout<<"Transicon"<<temp.at(i).Trans1.at(j).get_EdoOrigen();
        cout<<temp.at(i).Trans1.at(j).get_EdoDestino();
        cout<<temp.at(i).Trans1.at(j).get_SimbInf()<<endl;
    }
}*/

nuevo.Crea_TablaAFD();
int m = (int) nuevo.get_EdoAFN().size();
 for(int i=0; i<m;i++){
        for(int j=0; j<257; j++){
            if(j%5 == 0){
                cout<<endl;
            }
            cout<<"["<<i<<"]["<<j<<"] -->"<<nuevo.Mx_adyacencia[i][j]<<endl;
        }//for
        cout<<"\n----------------------------------------------------------"<<endl;
    }//for

/*int p =(int) nuevo.flag.size();
for(int i=0;i<p;i++){
    cout<<"->"<<nuevo.flag.at(i)<<endl;
}*/



    exit(0);
}


Estado Edo_byID (vector<Estado> Edo,int EdoID){
    int tam = (int) Edo.size();
    for(int i=0; i<tam;i++){
        if(Edo.at(i).get_IdEstado() == EdoID){
            return Edo.at(i);
        }//if
    }//for
    Estado e = Estado();
    e = e.Estado_null();
    return e;
}

void Ver_Alfabeto (vector<char> Alf){
    int tam = (int) Alf.size();
    cout<<"Alfabeto={";
    for(int i=0;i<tam;i++){
        cout<<Alf.at(i)<<", ";
    }//for
    cout<<"}"<<endl;
    return;
}

void Ver_ConjAcept (vector<Estado> Conj){
    int tam = (int) Conj.size();
    cout<<"Estados de Aceptacion ={";
    for(int i=0;i<tam;i++){
        cout<<Conj.at(i).get_IdEstado()<<"("<<Conj.at(i).get_Token()<<"), ";
    }//for
    cout<<"}"<<endl;
    return;
}
